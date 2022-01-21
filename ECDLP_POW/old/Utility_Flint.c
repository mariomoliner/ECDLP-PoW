#include "Utility_Flint.h"


int division_polynomial(fmpz_t l, fq_nmod_t A, fq_nmod_t B,fq_nmod_mpoly_t elliptic_poly,fq_nmod_mpoly_t ret, fq_nmod_mpoly_ctx_t ctx){


    fq_nmod_mpoly_t poly;

    fmpz_t aux;

    char ** variables; 

    variables = (char **)malloc(4*sizeof(char * ));
    variables[0] = "x";
    variables[1] = "y";
    variables[2] = "A";
    variables[3] = "B";

    fq_nmod_mpoly_init(poly, ctx);
    fmpz_init(aux);



    if(fmpz_equal_ui(l,0)){
	    int error = fq_nmod_mpoly_set_str_pretty(poly,"0", variables, ctx);
        

        fq_nmod_mpoly_set(ret, poly, ctx);
        return 0;
    }
    if(fmpz_equal_ui(l,1)){
	    int error = fq_nmod_mpoly_set_str_pretty(poly,"1", variables, ctx);
        fq_nmod_mpoly_set(ret, poly, ctx);
        return 0;
    }
    if(fmpz_equal_ui(l,2)){
	    int error = fq_nmod_mpoly_set_str_pretty(poly,"2*y", variables, ctx);

        fq_nmod_mpoly_set(ret, poly, ctx);
        return 0;
    }
    if(fmpz_equal_ui(l,3)){
	    int error = fq_nmod_mpoly_set_str_pretty(poly,"3*x^4 + 6*A*x^2 + 12*B*x - A^2", variables, ctx);

        fq_nmod_mpoly_evaluate_one_fq_nmod(poly, poly, 2, A, ctx);
        fq_nmod_mpoly_evaluate_one_fq_nmod(poly, poly, 3, B, ctx);

        fq_nmod_mpoly_set(ret, poly, ctx);
        return 0;
    }
    if(fmpz_equal_ui(l,4)){
	    int error = fq_nmod_mpoly_set_str_pretty(poly,"4*y* ( x^6 + 5*A*x^4 + 20*B*x^3 - 5*A^2*x^2 - 4*A*B*x - 8*B^2 - A^3 )", variables, ctx);

        fq_nmod_mpoly_evaluate_one_fq_nmod(poly, poly, 2, A, ctx);
        fq_nmod_mpoly_evaluate_one_fq_nmod(poly, poly, 3, B, ctx);
        fq_nmod_mpoly_set(ret, poly, ctx);
        return 0;
    }

    if(fmpz_is_even(l)){
        fmpz_cdiv_q_si(aux, l, 2);
    }else{
        fmpz_sub_ui(aux, l, 1);
        fmpz_cdiv_q_si(aux, aux, 2);
    }

    fq_nmod_mpoly_t fmpz_poly_aux1;
    fq_nmod_mpoly_t fmpz_poly_aux2;
    fq_nmod_mpoly_t fmpz_poly_aux3;
    fq_nmod_mpoly_t fmpz_poly_y_pow_4;

    fq_nmod_mpoly_t poly_m;
    fq_nmod_mpoly_t poly_m_minus_one; 
    fq_nmod_mpoly_t poly_m_plus_one;
    fq_nmod_mpoly_t poly_m_plus_two;
    fq_nmod_mpoly_t poly_m_minus_two;

    fq_nmod_mpoly_init(poly_m, ctx);
    fq_nmod_mpoly_init(poly_m_minus_one, ctx);
    fq_nmod_mpoly_init(poly_m_plus_one, ctx);
    fq_nmod_mpoly_init(poly_m_plus_two, ctx);
    fq_nmod_mpoly_init(poly_m_minus_two, ctx);
    fq_nmod_mpoly_init(fmpz_poly_aux1, ctx);
    fq_nmod_mpoly_init(fmpz_poly_aux2, ctx);
    fq_nmod_mpoly_init(fmpz_poly_aux3, ctx);
    fq_nmod_mpoly_init(fmpz_poly_y_pow_4, ctx);

    fq_nmod_mpoly_set_str_pretty(fmpz_poly_y_pow_4, "1*y^4", variables, ctx);
    division_polynomial(aux, A, B , elliptic_poly ,poly_m, ctx);
    fmpz_sub_ui(aux, aux, 1);
    division_polynomial(aux, A, B, elliptic_poly, poly_m_minus_one, ctx);
    fmpz_add_ui(aux, aux, 2);
    division_polynomial(aux, A, B , elliptic_poly, poly_m_plus_one, ctx);
    fmpz_add_ui(aux, aux, 1);
    division_polynomial(aux, A, B, elliptic_poly,poly_m_plus_two, ctx);
    fmpz_sub_ui(aux, aux, 4);
    division_polynomial(aux, A, B , elliptic_poly,poly_m_minus_two, ctx);



    if(fmpz_is_even(l)){
        fq_nmod_mpoly_pow_ui(fmpz_poly_aux1, poly_m_minus_one, 2, ctx);
        fq_nmod_mpoly_mul(fmpz_poly_aux1, poly_m_plus_two, fmpz_poly_aux1, ctx);

        fq_nmod_mpoly_pow_ui(fmpz_poly_aux2, poly_m_plus_one, 2, ctx);
        fq_nmod_mpoly_mul(fmpz_poly_aux2, poly_m_minus_two, fmpz_poly_aux2, ctx);

        fq_nmod_mpoly_sub(fmpz_poly_aux1,fmpz_poly_aux1, fmpz_poly_aux2, ctx);

        fq_nmod_mpoly_set_str_pretty(fmpz_poly_aux3,"2*y", variables, ctx);
        fq_nmod_mpoly_mul(fmpz_poly_aux1, fmpz_poly_aux1, poly_m, ctx);

        int err = fq_nmod_mpoly_divides(fmpz_poly_aux1, fmpz_poly_aux1, fmpz_poly_aux3, ctx);

        if(err == 0){
            printf("wasnt divisible!\n");

        }

        fq_nmod_mpoly_evaluate_one_fq_nmod(fmpz_poly_aux1, fmpz_poly_aux1, 2, A, ctx);
        fq_nmod_mpoly_evaluate_one_fq_nmod(fmpz_poly_aux1, fmpz_poly_aux1, 3, B, ctx);

        fq_nmod_mpoly_set(ret, fmpz_poly_aux1, ctx);

        
    }else{
        //fq_nmod_mpoly_print_pretty(poly_m, variables, ctx);
	    //flint_printf("\n");

        fq_nmod_mpoly_pow_ui(fmpz_poly_aux1, poly_m, 3, ctx);
        fq_nmod_mpoly_mul(fmpz_poly_aux1, poly_m_plus_two, fmpz_poly_aux1, ctx);

        //print_nmod_mpoly(fmpz_poly_aux1, "red: ", variables, ctx);

        fq_nmod_mpoly_pow_ui(fmpz_poly_aux2, poly_m_plus_one, 3, ctx);
        fq_nmod_mpoly_mul(fmpz_poly_aux2, poly_m_minus_one, fmpz_poly_aux2, ctx);

        //print_nmod_mpoly(fmpz_poly_aux2, "red: ", variables, ctx);



        if(fmpz_is_even(aux)){
            fq_nmod_mpoly_div(fmpz_poly_aux1, fmpz_poly_aux1, fmpz_poly_y_pow_4, ctx);
            //print_nmod_mpoly(fmpz_poly_aux1, "red: ", variables, ctx);

            fq_nmod_mpoly_mul(fmpz_poly_aux1, fmpz_poly_aux1, elliptic_poly, ctx);
            fq_nmod_mpoly_mul(fmpz_poly_aux1, fmpz_poly_aux1, elliptic_poly, ctx);
            //print_nmod_mpoly(fmpz_poly_aux1, "red: ", variables, ctx);

        }else{
            fq_nmod_mpoly_div(fmpz_poly_aux2, fmpz_poly_aux2, fmpz_poly_y_pow_4, ctx);
            fq_nmod_mpoly_mul(fmpz_poly_aux2, fmpz_poly_aux2, elliptic_poly, ctx);
            fq_nmod_mpoly_mul(fmpz_poly_aux2, fmpz_poly_aux2, elliptic_poly, ctx);
        }

        fq_nmod_mpoly_sub(fmpz_poly_aux1,fmpz_poly_aux1, fmpz_poly_aux2, ctx);

        fq_nmod_mpoly_evaluate_one_fq_nmod(fmpz_poly_aux1, fmpz_poly_aux1, 2, A, ctx);
        fq_nmod_mpoly_evaluate_one_fq_nmod(fmpz_poly_aux1, fmpz_poly_aux1, 3, B, ctx);

        fq_nmod_mpoly_set(ret, fmpz_poly_aux1, ctx);

        


    }

    fq_nmod_mpoly_clear(poly_m, ctx);
    fq_nmod_mpoly_clear(poly_m_minus_one, ctx);
    fq_nmod_mpoly_clear(poly_m_minus_two, ctx);
    fq_nmod_mpoly_clear(poly_m_plus_one, ctx);
    fq_nmod_mpoly_clear(poly_m_plus_two, ctx);
    fq_nmod_mpoly_clear(fmpz_poly_aux1, ctx);
    fq_nmod_mpoly_clear(fmpz_poly_aux2, ctx);
    fq_nmod_mpoly_clear(fmpz_poly_aux3, ctx);
    fq_nmod_mpoly_clear(fmpz_poly_y_pow_4, ctx);
    
    return 0;
}

void Schoofs(fq_nmod_t A, fq_nmod_t B, fmpz_t q, fmpz_t cardinal, fq_nmod_ctx_t nmod_ctx){
    fmpz_t * primes;
    fmpz_t * t_l;
    fmpz_t hasse_bound;
    fmpz_t current_prime;
    fmpz_t mult;
    fmpz_t aux;
    fmpz_t q_red;
    fmpz_t l;
    fq_nmod_mpoly_ctx_t ctx;
    fq_nmod_mpoly_ctx_t ctx_4_vars;
    fq_nmod_mpoly_t ret1;
    fmpz_t rho;
    int found_lambda = 0;
    
    

    char ** variables; 
    variables = (char **)malloc(4*sizeof(char * ));
    variables[0] = "x";
    variables[1] = "y";
    variables[2] = "A";
    variables[3] = "B";

    int num_of = 1;
    int it;

    fq_nmod_mpoly_ctx_init(ctx, 4, ORD_LEX, nmod_ctx);
    fq_nmod_mpoly_ctx_init(ctx_4_vars, 4, ORD_LEX, nmod_ctx);
    fq_nmod_mpoly_init(ret1, ctx);
    
    fmpz_init(hasse_bound);
    fmpz_init(mult);
    fmpz_init(aux);
    fmpz_init_set_ui(current_prime,2);
    fmpz_init(q_red);
    fmpz_init(rho);
    fmpz_init(l);


    primes = (fmpz_t *)malloc(sizeof(fmpz_t)*1);
    t_l = (fmpz_t *)malloc(sizeof(fmpz_t)*1);

    fmpz_init_set(primes[num_of-1], current_prime);
    fmpz_init(t_l[num_of-1]);

    fmpz_sqrt(hasse_bound, q);
    fmpz_mul_ui(hasse_bound, hasse_bound, 4);

    fmpz_set(mult, current_prime);
    while(fmpz_cmp(mult, hasse_bound) <= 0){
        fmpz_add_ui(aux,current_prime,1);
        if(!fmpz_is_prime(aux)){
            fmpz_nextprime(current_prime, aux,1);
        }else{
            fmpz_set(current_prime, aux);
        }
        if(!fmpz_equal(q,current_prime) && !fmpz_equal_ui(current_prime, 3)){
            fmpz_mul(mult, mult, current_prime);

            num_of++;
            primes = realloc(primes, sizeof(fmpz_t)*num_of);
            fmpz_init_set(primes[num_of-1], current_prime);
            t_l = realloc(t_l, sizeof(fmpz_t)*num_of);
            fmpz_init(t_l[num_of-1]);

        }
    }

    printf("numof %d\n", num_of);
    fmpz_print(primes[0]);

    flint_printf("\n");

    fq_nmod_mpoly_t poly_l;
    fq_nmod_mpoly_t poly_elliptic;
    fq_nmod_mpoly_t poly_elliptic_ohne_y;
    fq_nmod_mpoly_t gcd;
    fq_nmod_mpoly_t alpha;
    fq_nmod_mpoly_t beta;
    

    fq_nmod_mpoly_init(alpha, ctx);
    fq_nmod_mpoly_init(beta, ctx);
    fq_nmod_mpoly_fit_length(alpha, 300, ctx);
    fq_nmod_mpoly_fit_length(beta, 300, ctx);
    fq_nmod_mpoly_init(poly_l, ctx);
    fq_nmod_mpoly_init(poly_elliptic, ctx);
    fq_nmod_mpoly_init(poly_elliptic_ohne_y, ctx);
    fq_nmod_mpoly_init(gcd, ctx);


    fq_nmod_mpoly_set_str_pretty(poly_elliptic,"y^2 - x^3 - A*x - B", variables, ctx);
    fq_nmod_mpoly_set_str_pretty(poly_elliptic_ohne_y,"x^3 + A*x + B", variables, ctx);


    // SETTING THE CONTEXT OF THE ELLIPTIC CURVE A,B
    fq_nmod_mpoly_evaluate_one_fq_nmod(poly_elliptic, poly_elliptic, 2, A, ctx);
    fq_nmod_mpoly_evaluate_one_fq_nmod(poly_elliptic, poly_elliptic, 3, B, ctx);
    
    fq_nmod_mpoly_evaluate_one_fq_nmod(poly_elliptic_ohne_y, poly_elliptic_ohne_y, 2, A, ctx);
    fq_nmod_mpoly_evaluate_one_fq_nmod(poly_elliptic_ohne_y, poly_elliptic_ohne_y, 3, B, ctx);




    flint_printf("q_red: ");
    fmpz_print(q_red);
    flint_printf("\n");
    fmpz_set(aux, l);
    fmpz_add_ui(aux, aux, 2);
    fmpz_print(aux);
    flint_printf("\n");

    fmpz_set(aux, primes[num_of-1]);
    fmpz_add_ui(aux, aux, 3);
    division_polynomials div_polys =  init_division_polynomials(aux,A,B,poly_elliptic_ohne_y,NULL, ctx);
    

    for(int i = 0; i<num_of; i++){
        fmpz_set(l, primes[i]);
        fmpz_mod(q_red, q, l);
        division_polynomial(l, A, B,poly_elliptic_ohne_y, poly_l, ctx);

        print_nmod_mpoly(poly_l, "poly_l: ", variables, ctx);
        fmpz_print(l);
        flint_printf("\n");
        fmpz_print(q_red);
        flint_printf("\n");

        if(fmpz_equal_ui(l, 2)){
            check_2(q, poly_elliptic_ohne_y, variables ,ctx, ret1);
            if(fq_nmod_mpoly_is_one(ret1, ctx)){
                fmpz_set_ui(t_l[i],1);
            }else{
                fmpz_set_ui(t_l[i],0);
            }
        }else{
            p_16(l, q, q_red, A, B ,poly_elliptic_ohne_y, poly_l, &div_polys, variables, ctx, ret1);
            fq_nmod_mpoly_gcd(gcd, ret1, poly_l, ctx);
            print_nmod_mpoly(gcd, "gcd: ", variables, ctx);
            if(!fq_nmod_mpoly_is_one(gcd, ctx)){//case 1
                fmpz_t w;
                int theres_squareroot = fmpz_sqrtmod(w, q,l);
                if(theres_squareroot == 0){
                    fmpz_set_ui(t_l[i],0);
                }else{

                    p_17(l, q, w, A, B, poly_elliptic_ohne_y, poly_l, &div_polys, variables, ctx, ret1);
                    fq_nmod_mpoly_gcd(gcd, ret1, poly_l, ctx);
                    print_nmod_mpoly(gcd, "gcd: ", variables, ctx);
                    if(fq_nmod_mpoly_is_one(gcd, ctx)){
                        fmpz_set_ui(t_l[i],0);
                    }else{
                        p_18(l, q, w, A, B, poly_elliptic_ohne_y, poly_l, &div_polys, variables, ctx, ret1);
                        fq_nmod_mpoly_gcd(gcd, ret1, poly_l, ctx);
                        print_nmod_mpoly(gcd, "gcd: ", variables, ctx);
                        if(fq_nmod_mpoly_is_one(gcd, ctx)){
                            fmpz_mod(w, w, l);
                            fmpz_set(t_l[i],w);
                            fmpz_mul_si(t_l[i], t_l[i], -2);
                        }else{
                            fmpz_mod(w, w, l);
                            fmpz_set(t_l[i],w);
                            fmpz_mul_si(t_l[i], t_l[i], 2);
                        }
                    }
                }

            }else{//case 2
                alpha_k(l,q, q_red, poly_elliptic_ohne_y, &div_polys, variables, ctx, alpha);
                beta_k(l,q, q_red, poly_elliptic_ohne_y, &div_polys, variables, ctx, beta);

                fmpz_set_ui(rho, 1);
                fmpz_set(aux, l);
                fmpz_add_ui(aux, aux, 1);
                fmpz_divexact_ui(aux, aux, 2);
                while(fmpz_cmp(rho, aux)<=0 ){
                    p_19x(l, rho, q, q_red, A, B, poly_elliptic_ohne_y, &div_polys, alpha, beta, variables, ctx, ret1);
                    fq_nmod_mpoly_divrem(gcd , ret1, ret1, poly_l, ctx);
                    if(fq_nmod_mpoly_is_zero(ret1, ctx)){
                        p_19y(l, rho, q, q_red, A, B, poly_elliptic_ohne_y, &div_polys, alpha, beta, variables, ctx, ret1);
                        fq_nmod_mpoly_divrem(gcd , ret1, ret1, poly_l, ctx);
                        if(fq_nmod_mpoly_is_zero(ret1, ctx)){
                            fmpz_mul_si(t_l[i], rho, 1);
                            break;
                        }else{
                            fmpz_mul_si(t_l[i], rho, -1);
                            break;
                        }
                    }
                    fmpz_add_ui(rho, rho, 1);
                }


            }
        }

    }

    flint_printf("l  and t_l \n");

    for(int i = 0; i<num_of; i++){
        fmpz_print(primes[i]);
        flint_printf(" | ");
        fmpz_print(t_l[i]);
        flint_printf("\n");
    }
    fmpz_t l_final;
    fmpz_init(l_final);
    fmpz_sqrt(hasse_bound, q);
    fmpz_mul_ui(hasse_bound, hasse_bound, 2);

    get_final_l(num_of, primes, t_l, hasse_bound, l_final);

    fmpz_set(cardinal, q);
    fmpz_add_ui(cardinal, cardinal, 1);
    fmpz_sub(cardinal, cardinal, l_final);


}


void check_2(fmpz_t q, fq_nmod_mpoly_t elliptic_poly,char ** vars,fq_nmod_mpoly_ctx_t ctx ,fq_nmod_mpoly_t * ret){
    fq_nmod_mpoly_t poly_x;
    fq_nmod_mpoly_t poly_aux;
    fq_nmod_mpoly_t gcd;
    fq_nmod_mpoly_init(poly_x, ctx);
    fq_nmod_mpoly_init(poly_aux, ctx);
    fq_nmod_mpoly_init(gcd, ctx);
    fq_nmod_mpoly_set_str_pretty(poly_x,"1*x", vars, ctx);

    fq_nmod_mpoly_pow_fmpz(poly_aux, poly_x, q, ctx);
    fq_nmod_mpoly_sub(poly_aux, poly_aux, poly_x, ctx);

    fq_nmod_mpoly_gcd(gcd, poly_aux, elliptic_poly, ctx);
    fq_nmod_mpoly_set(ret, gcd, ctx);

    fq_nmod_mpoly_clear(poly_x, ctx);
    fq_nmod_mpoly_clear(poly_aux, ctx);
    fq_nmod_mpoly_clear(gcd, ctx);


}
void simplify_if_possible(fq_nmod_mpoly_t poly, fq_nmod_mpoly_t poly_ret, fq_nmod_mpoly_t poly_elliptic, char ** vars ,fq_nmod_mpoly_ctx_t ctx){
    fq_nmod_mpoly_t gcd;
    fq_nmod_mpoly_t poly_y;
    fq_nmod_mpoly_t poly_aux;
    fq_nmod_mpoly_init(poly_y, ctx);
    fq_nmod_mpoly_init(poly_aux, ctx);


    fq_nmod_mpoly_set_str_pretty(poly_y,"y^2", vars, ctx);

    if(fq_nmod_mpoly_divides(poly_aux,poly, poly_y, ctx) == 1){
        fq_nmod_mpoly_mul(poly_aux, poly_aux, poly_elliptic, ctx);
        fq_nmod_mpoly_set(poly_ret, poly_aux, ctx);
    }else{
        fq_nmod_mpoly_set(poly_ret, poly, ctx);
    }

    fq_nmod_mpoly_clear(poly_y, ctx);    
    fq_nmod_mpoly_clear(poly_aux, ctx);    

}


void p_16(fmpz_t l, fmpz_t q, fmpz_t q_red, fq_nmod_t A, fq_nmod_t B, fq_nmod_mpoly_t elliptic_poly, fq_nmod_mpoly_t poly_l, division_polynomials * polinomials_division ,char ** vars ,fq_nmod_mpoly_ctx_t ctx,fq_nmod_mpoly_t * ret){
    fq_nmod_mpoly_t poly_x;
    fq_nmod_mpoly_t poly_y;
    fq_nmod_mpoly_t poly_x_q_2;
    fq_nmod_mpoly_t poly_aux;
    fq_nmod_mpoly_t poly_aux2;
    fq_nmod_mpoly_t poly_aux3;
    fmpz_t aux;
    ulong k_long;

    fmpz_init(aux);
    fmpz_set(aux, q);
    fmpz_pow_ui(aux,aux, 2);
    fq_nmod_mpoly_init(poly_x_q_2, ctx);
    fq_nmod_mpoly_init(poly_aux, ctx);
    fq_nmod_mpoly_init(poly_aux2, ctx);
    fq_nmod_mpoly_init(poly_aux3, ctx);
    fq_nmod_mpoly_init(poly_x, ctx);
    fq_nmod_mpoly_init(poly_y, ctx);
    fq_nmod_mpoly_init(poly_x_q_2, ctx);
    fq_nmod_mpoly_set_str_pretty(poly_x,"1*x", vars, ctx);
    fq_nmod_mpoly_set_str_pretty(poly_y,"1*y", vars, ctx);
    fq_nmod_mpoly_set(poly_x_q_2, poly_x, ctx);
    fq_nmod_mpoly_pow_fmpz(poly_x_q_2, poly_x_q_2, aux, ctx);


    //fq_nmod_mpoly_evaluate_one_fq_nmod(poly_q, poly_q, 2, A,ctx);
    //fq_nmod_mpoly_evaluate_one_fq_nmod(poly_q, poly_q, 3, B,ctx);

    k_long = fmpz_get_ui(q_red);


    // poly_aux <-- leftpart
    fq_nmod_mpoly_sub(poly_aux, poly_x_q_2, poly_x, ctx);
    if(fmpz_is_even(q_red)){
        //print_nmod_mpoly(&polinomials_division->polynomial[k_long], "k_long: ", vars ,ctx);

        fq_nmod_mpoly_div(poly_aux2, &polinomials_division->polynomial[k_long], poly_y, ctx);
        fq_nmod_mpoly_mul(poly_aux, poly_aux, elliptic_poly, ctx);
    }else{
        fq_nmod_mpoly_set(poly_aux2, &polinomials_division->polynomial[k_long], ctx);
    }

    fq_nmod_mpoly_pow_ui(poly_aux2, poly_aux2, 2, ctx);

    fq_nmod_mpoly_mul(poly_aux, poly_aux, poly_aux2, ctx);


    //print_nmod_mpoly(poly_aux, "left: ", vars ,ctx);



    //poly_aux2 <-- righthand
    
    if(fmpz_is_odd(q_red)){
        /*fq_nmod_mpoly_div(poly_k_plus_one, poly_k_plus_one, poly_y, ctx);
        fq_nmod_mpoly_div(poly_k_minus_one, poly_k_minus_one, poly_y, ctx);
        fq_nmod_mpoly_mul(poly_aux2, poly_k_minus_one, poly_k_plus_one, ctx);
            
        print_nmod_mpoly(poly_k_minus_one, "right: ", vars ,ctx);
        print_nmod_mpoly(poly_k_plus_one, "right: ", vars ,ctx);*/

        fq_nmod_mpoly_div(poly_aux2, &polinomials_division->polynomial[k_long-1], poly_y, ctx);
        fq_nmod_mpoly_div(poly_aux3, &polinomials_division->polynomial[k_long+1], poly_y, ctx);
        fq_nmod_mpoly_mul(poly_aux2, poly_aux2, poly_aux3, ctx);


        fq_nmod_mpoly_mul(poly_aux2, poly_aux2, elliptic_poly, ctx);

    }else{
        //fq_nmod_mpoly_mul(poly_aux2, poly_k_minus_one, poly_k_plus_one, ctx);
        fq_nmod_mpoly_mul(poly_aux2, &polinomials_division->polynomial[k_long-1], &polinomials_division->polynomial[k_long+1], ctx);
    }

    //print_nmod_mpoly(poly_aux2, "right: ", vars ,ctx);

    fq_nmod_mpoly_add(poly_aux, poly_aux, poly_aux2, ctx);
    fq_nmod_mpoly_set(ret, poly_aux, ctx);

    //print_nmod_mpoly(ret, "ret: ", vars ,ctx);

    fq_nmod_mpoly_clear(poly_x, ctx);
    fq_nmod_mpoly_clear(poly_x_q_2, ctx);
    fq_nmod_mpoly_clear(poly_y, ctx);
    fq_nmod_mpoly_clear(poly_aux, ctx);
    fq_nmod_mpoly_clear(poly_aux2, ctx);
    fq_nmod_mpoly_clear(poly_aux3, ctx);
    fmpz_clear(aux);


}

void p_19x(fmpz_t l, fmpz_t rho, fmpz_t q, fmpz_t q_red, fq_nmod_t A, fq_nmod_t B, fq_nmod_mpoly_t elliptic_poly, division_polynomials * polinomials_division,fq_nmod_mpoly_t alpha,  fq_nmod_mpoly_t beta,char ** vars ,fq_nmod_mpoly_ctx_t ctx ,fq_nmod_mpoly_t * ret){
    fq_nmod_mpoly_t poly_x;
    fq_nmod_mpoly_t poly_y;
    fq_nmod_mpoly_t poly_aux;
    fq_nmod_mpoly_t poly_aux2;
    fq_nmod_mpoly_t poly_aux3;
    fq_nmod_mpoly_t poly_aux4;
    fq_nmod_mpoly_t poly_aux5;
    fq_nmod_mpoly_t poly_aux6;

    ulong rho_u;
    ulong k_u;
    ulong l_long;
    fmpz_t aux;

    if(fmpz_is_one(q_red)){
        fmpz_set(q_red, l);
        fmpz_add_ui(q_red, q_red, 1);
    }

    

    rho_u = fmpz_get_ui(rho);
    k_u = fmpz_get_ui(q_red);
    l_long = fmpz_get_ui(l);
    fmpz_init(aux);


    fq_nmod_mpoly_init(poly_x, ctx);
    fq_nmod_mpoly_init(poly_y, ctx);
    fq_nmod_mpoly_init(poly_aux, ctx);
    fq_nmod_mpoly_init(poly_aux2, ctx);
    fq_nmod_mpoly_init(poly_aux3, ctx);
    fq_nmod_mpoly_init(poly_aux4, ctx);
    fq_nmod_mpoly_init(poly_aux5, ctx);
    fq_nmod_mpoly_init(poly_aux6, ctx);
    fq_nmod_mpoly_set_str_pretty(poly_x,"1*x", vars, ctx);
    fq_nmod_mpoly_set_str_pretty(poly_y,"1*y", vars, ctx);


    //alpha_k(l,q, q_red, elliptic_poly, polinomials_division, vars, ctx, alpha);
    //beta_k(l,q, q_red, elliptic_poly, polinomials_division, vars, ctx, beta);

    //print_nmod_mpoly(alpha, "alpha: ", vars, ctx);
    //print_nmod_mpoly(beta, "beta: ", vars, ctx);

    

    //parte de mas a la izquierda

    fq_nmod_mpoly_mul(poly_aux5, &polinomials_division->polynomial[rho_u-1], &polinomials_division->polynomial[rho_u+1], ctx);
    simplify_if_possible(poly_aux5, poly_aux5, elliptic_poly, vars, ctx);
    //print_nmod_mpoly(poly_aux5, "debug: ", vars, ctx);
    reduce_poly_l(poly_aux5, &polinomials_division->polynomial[l_long], ctx, poly_aux5);

    //print_nmod_mpoly(poly_aux5, "debug: ", vars, ctx);

    fq_nmod_mpoly_pow_fmpz(poly_aux5, poly_aux5, q, ctx);

    reduce_poly_l(poly_aux5, &polinomials_division->polynomial[l_long], ctx, poly_aux5);
    //print_nmod_mpoly(poly_aux5, "debug: ", vars, ctx);


    fq_nmod_mpoly_mul(poly_aux4, beta, &polinomials_division->polynomial[k_u], ctx);
    //print_nmod_mpoly(poly_aux4, "debug: ", vars, ctx);

    fq_nmod_mpoly_pow_ui(poly_aux4, poly_aux4, 2, ctx);
    //print_nmod_mpoly(poly_aux4, "debug: ", vars, ctx);

    simplify_if_possible(poly_aux4, poly_aux4, elliptic_poly, vars, ctx);
    //print_nmod_mpoly(poly_aux4, "debug: ", vars, ctx);
    simplify_if_possible(poly_aux4, poly_aux4, elliptic_poly, vars, ctx);
    //print_nmod_mpoly(poly_aux4, "debug: ", vars, ctx);

    reduce_poly_l(poly_aux4, &polinomials_division->polynomial[l_long], ctx, poly_aux4);



    //print_nmod_mpoly(poly_aux4, "debug: ", vars, ctx);

    fq_nmod_mpoly_mul(poly_aux5, poly_aux5, poly_aux4, ctx);
    reduce_poly_l(poly_aux5, &polinomials_division->polynomial[l_long], ctx, poly_aux5);


    //print_nmod_mpoly(poly_aux5, "debug: ", vars, ctx);


    // inner part , staring from left

    fq_nmod_mpoly_pow_ui(poly_aux4, &polinomials_division->polynomial[k_u], 2, ctx);
    //print_nmod_mpoly(poly_aux4, "debug: ", vars, ctx);

    fq_nmod_mpoly_mul(poly_aux4, alpha, poly_aux4, ctx);
    fq_nmod_mpoly_mul(poly_aux4, alpha, poly_aux4, ctx);
    simplify_if_possible(poly_aux4, poly_aux4, elliptic_poly, vars, ctx);
    simplify_if_possible(poly_aux4, poly_aux4, elliptic_poly, vars, ctx);

    reduce_poly_l(poly_aux4, &polinomials_division->polynomial[l_long], ctx, poly_aux4);



    //print_nmod_mpoly(poly_aux4, "debug: ", vars, ctx);


    fmpz_set(aux, q);
    fmpz_pow_ui(aux, aux, 2);
    //fmpz_print(aux);
    //flint_printf("\n");
    fq_nmod_mpoly_pow_fmpz(poly_aux3, poly_x, aux, ctx);
    //print_nmod_mpoly(poly_aux3, "debug: ", vars, ctx);
    fq_nmod_mpoly_pow_fmpz(poly_aux2, poly_x, q, ctx);
    //print_nmod_mpoly(poly_aux2, "debug: ", vars, ctx);
    fq_nmod_mpoly_add(poly_aux3, poly_aux3, poly_aux2, ctx);
    //print_nmod_mpoly(poly_aux3, "debug: ", vars, ctx);

    fq_nmod_mpoly_add(poly_aux3, poly_aux3, poly_x, ctx);
    fq_nmod_mpoly_mul(poly_aux3, &polinomials_division->polynomial[k_u], poly_aux3, ctx);
    fq_nmod_mpoly_mul(poly_aux3, &polinomials_division->polynomial[k_u], poly_aux3, ctx);
    
    simplify_if_possible(poly_aux3, poly_aux3, elliptic_poly, vars, ctx);
    reduce_poly_l(poly_aux3, &polinomials_division->polynomial[l_long], ctx, poly_aux3);



    //print_nmod_mpoly(poly_aux3, "debug: ", vars, ctx);


    fq_nmod_mpoly_mul(poly_aux2, &polinomials_division->polynomial[k_u-1], &polinomials_division->polynomial[k_u+1], ctx);
    //print_nmod_mpoly(poly_aux2, "debug: ", vars, ctx);
    simplify_if_possible(poly_aux2, poly_aux2, elliptic_poly, vars, ctx);
    reduce_poly_l(poly_aux2, &polinomials_division->polynomial[l_long], ctx, poly_aux2);




    //we sum the inner terms
    fq_nmod_mpoly_sub(poly_aux2, poly_aux2, poly_aux3, ctx);
    
    //print_nmod_mpoly(poly_aux2, "debug: ", vars, ctx);


    fq_nmod_mpoly_mul(poly_aux2, beta, poly_aux2, ctx);
    fq_nmod_mpoly_mul(poly_aux2, beta, poly_aux2, ctx);
    simplify_if_possible(poly_aux2, poly_aux2, elliptic_poly, vars, ctx);
    reduce_poly_l(poly_aux2, &polinomials_division->polynomial[l_long], ctx, poly_aux2);


    fq_nmod_mpoly_add(poly_aux2, poly_aux2, poly_aux4, ctx);

    //print_nmod_mpoly(poly_aux2, "debug: ", vars, ctx);


    fmpz_mul_ui(aux, q, 2);
    if(fmpz_is_even(rho)){
        fq_nmod_mpoly_div(poly_aux, &polinomials_division->polynomial[rho_u], poly_y, ctx);
        fq_nmod_mpoly_pow_fmpz(poly_aux,  poly_aux, aux, ctx);
        fq_nmod_mpoly_pow_fmpz(poly_aux6, elliptic_poly, q, ctx);
        fq_nmod_mpoly_mul(poly_aux, poly_aux, poly_aux6, ctx);
        reduce_poly_l(poly_aux, &polinomials_division->polynomial[l_long], ctx, poly_aux);


    }else{
        fq_nmod_mpoly_pow_fmpz(poly_aux,  &polinomials_division->polynomial[rho_u], aux, ctx);
        reduce_poly_l(poly_aux, &polinomials_division->polynomial[l_long], ctx, poly_aux);

    }
    //fq_nmod_mpoly_pow_fmpz(poly_aux,  &polinomials_division->polynomial[rho_u], aux, ctx);
    fq_nmod_mpoly_mul(poly_aux2, poly_aux, poly_aux2, ctx);
    simplify_if_possible(poly_aux2, poly_aux2, elliptic_poly, vars, ctx);

    reduce_poly_l(poly_aux2, &polinomials_division->polynomial[l_long], ctx, poly_aux2);


    //print_nmod_mpoly(poly_aux2, "debug: ", vars, ctx);
    //print_nmod_mpoly(poly_aux5, "debug: ", vars, ctx);

    fq_nmod_mpoly_add(poly_aux, poly_aux2, poly_aux5, ctx);

    //print_nmod_mpoly(poly_aux, "debug: ", vars, ctx);

    fq_nmod_mpoly_set(ret, poly_aux, ctx);

    fq_nmod_mpoly_clear(poly_aux, ctx);
    fq_nmod_mpoly_clear(poly_aux2, ctx);
    fq_nmod_mpoly_clear(poly_aux3, ctx);
    fq_nmod_mpoly_clear(poly_aux4, ctx);
    fq_nmod_mpoly_clear(poly_aux5, ctx);
    fq_nmod_mpoly_clear(poly_aux6, ctx);
    fq_nmod_mpoly_clear(poly_x, ctx);
    fmpz_clear(aux);

}



void p_19y(fmpz_t l, fmpz_t rho, fmpz_t q, fmpz_t q_red, fq_nmod_t A, fq_nmod_t B, fq_nmod_mpoly_t elliptic_poly, division_polynomials * polinomials_division, fq_nmod_mpoly_t alpha,  fq_nmod_mpoly_t beta,char ** vars ,fq_nmod_mpoly_ctx_t ctx ,fq_nmod_mpoly_t * ret){
    fq_nmod_mpoly_t poly_x;
    fq_nmod_mpoly_t poly_y;
    fq_nmod_mpoly_t poly_aux;
    fq_nmod_mpoly_t poly_aux2;
    fq_nmod_mpoly_t poly_aux3;
    fq_nmod_mpoly_t poly_aux4;
    fq_nmod_mpoly_t poly_aux5;
    fq_nmod_mpoly_t poly_aux6;
    fq_nmod_mpoly_t poly_aux7;
    fq_nmod_mpoly_t poly_aux8;
    fq_nmod_mpoly_t poly_aux9;


    ulong rho_u;
    ulong k_u;
    ulong l_long;
    fmpz_t aux;

    if(fmpz_is_one(q_red)){
        fmpz_set(q_red, l);
        fmpz_add_ui(q_red, q_red, 1);
    }

    rho_u = fmpz_get_ui(rho);
    k_u = fmpz_get_ui(q_red);
    l_long = fmpz_get_ui(l);
    fmpz_init(aux);


    fq_nmod_mpoly_init(poly_x, ctx);
    fq_nmod_mpoly_init(poly_y, ctx);
    fq_nmod_mpoly_init(poly_aux, ctx);
    fq_nmod_mpoly_init(poly_aux2, ctx);
    fq_nmod_mpoly_init(poly_aux3, ctx);
    fq_nmod_mpoly_init(poly_aux4, ctx);
    fq_nmod_mpoly_init(poly_aux5, ctx);
    fq_nmod_mpoly_init(poly_aux6, ctx);
    fq_nmod_mpoly_init(poly_aux7, ctx);
    fq_nmod_mpoly_init(poly_aux8, ctx);
    fq_nmod_mpoly_init(poly_aux9, ctx);
    fq_nmod_mpoly_set_str_pretty(poly_x,"1*x", vars, ctx);
    fq_nmod_mpoly_set_str_pretty(poly_y,"1*y", vars, ctx);

    fq_nmod_mpoly_mul(poly_aux5, &polinomials_division->polynomial[rho_u-1], &polinomials_division->polynomial[rho_u-1], ctx);
    fq_nmod_mpoly_mul(poly_aux5, &polinomials_division->polynomial[rho_u+2], poly_aux5, ctx);

    fq_nmod_mpoly_mul(poly_aux6, &polinomials_division->polynomial[rho_u+1], &polinomials_division->polynomial[rho_u+1], ctx);
    fq_nmod_mpoly_mul(poly_aux6, &polinomials_division->polynomial[rho_u-2], poly_aux5, ctx);

    fq_nmod_mpoly_sub(poly_aux6, poly_aux5, poly_aux6, ctx);
    simplify_if_possible(poly_aux6, poly_aux6, elliptic_poly, vars, ctx);
    //simplify_if_possible(poly_aux6, poly_aux6, elliptic_poly, vars, ctx);
    reduce_poly_l(poly_aux6, &polinomials_division->polynomial[l_long], ctx, poly_aux6);

    //fq_nmod_mpoly_pow_fmpz(poly_aux6, poly_aux6, q, ctx);
    poly_exp_mod(elliptic_poly, q, &polinomials_division->polynomial[l_long], vars, ctx, poly_aux6);


    if(fmpz_is_even(rho)){
        fmpz_set(aux, q);
        fmpz_sub_ui(aux, aux, 1);
        fmpz_divexact_ui(aux, aux, 2);

        fq_nmod_mpoly_pow_fmpz(poly_aux5, poly_y, q, ctx);
        fq_nmod_mpoly_divides(poly_aux6, poly_aux6, poly_aux5, ctx);
        //fq_nmod_mpoly_pow_fmpz(poly_aux5, elliptic_poly, aux, ctx);
        poly_exp_mod(elliptic_poly, aux, &polinomials_division->polynomial[l_long], vars, ctx, poly_aux5);

        fq_nmod_mpoly_mul(poly_aux6, poly_aux5, poly_aux6, ctx);
        fq_nmod_mpoly_mul(poly_aux6, poly_y, poly_aux6, ctx);
    }else{

    }

    fq_nmod_mpoly_mul(poly_aux5, &polinomials_division->polynomial[k_u], beta, ctx);
    fq_nmod_mpoly_pow_ui(poly_aux5, poly_aux5, 2, ctx);
    simplify_if_possible(poly_aux5, poly_aux5, elliptic_poly, vars, ctx);
    simplify_if_possible(poly_aux5, poly_aux5, elliptic_poly, vars, ctx);
    fq_nmod_mpoly_mul(poly_aux5, poly_aux5, beta, ctx);

    fq_nmod_mpoly_mul(poly_aux6, poly_aux5, poly_aux6, ctx);
    simplify_if_possible(poly_aux6, poly_aux6, elliptic_poly, vars, ctx);
    simplify_if_possible(poly_aux6, poly_aux6, elliptic_poly, vars, ctx);

    reduce_poly_l(poly_aux6, &polinomials_division->polynomial[l_long], ctx, poly_aux6);

    //Right part done

    fq_nmod_mpoly_mul(poly_aux5, &polinomials_division->polynomial[k_u], beta, ctx);
    fq_nmod_mpoly_pow_ui(poly_aux5, poly_aux5, 2, ctx);
    simplify_if_possible(poly_aux5, poly_aux5, elliptic_poly, vars, ctx);
    simplify_if_possible(poly_aux5, poly_aux5, elliptic_poly, vars, ctx);
    fq_nmod_mpoly_mul(poly_aux5, poly_aux5, beta, ctx);

    fmpz_set(aux, q);
    fmpz_pow_ui(aux, aux, 2);
    fmpz_sub_ui(aux, aux, 1);
    fmpz_divexact_ui(aux, aux, 2);

    //fq_nmod_mpoly_pow_fmpz(poly_aux4, elliptic_poly, aux, ctx);
    poly_exp_mod(elliptic_poly, aux, &polinomials_division->polynomial[l_long], vars, ctx, poly_aux4);

    fq_nmod_mpoly_mul(poly_aux4, poly_aux4, poly_y, ctx);
    fq_nmod_mpoly_mul(poly_aux5, poly_aux4, poly_aux5, ctx);
    simplify_if_possible(poly_aux5, poly_aux5, elliptic_poly, vars, ctx);
    simplify_if_possible(poly_aux5, poly_aux5, elliptic_poly, vars, ctx);
    reduce_poly_l(poly_aux5, &polinomials_division->polynomial[l_long], ctx, poly_aux5);


    fq_nmod_mpoly_mul(poly_aux4, &polinomials_division->polynomial[k_u], alpha, ctx);
    fq_nmod_mpoly_pow_ui(poly_aux4, poly_aux4, 2, ctx);
    simplify_if_possible(poly_aux4, poly_aux4, elliptic_poly, vars, ctx);
    simplify_if_possible(poly_aux4, poly_aux4, elliptic_poly, vars, ctx);
    reduce_poly_l(poly_aux4, &polinomials_division->polynomial[l_long], ctx, poly_aux4);

    fq_nmod_mpoly_mul(poly_aux3, &polinomials_division->polynomial[k_u+1], beta, ctx);
    fq_nmod_mpoly_mul(poly_aux3, &polinomials_division->polynomial[k_u-1], poly_aux3, ctx);
    fq_nmod_mpoly_mul(poly_aux3, poly_aux3, beta, ctx);
    simplify_if_possible(poly_aux3, poly_aux3, elliptic_poly, vars, ctx);
    simplify_if_possible(poly_aux3, poly_aux3, elliptic_poly, vars, ctx);
    reduce_poly_l(poly_aux3, &polinomials_division->polynomial[l_long], ctx, poly_aux3);


    fq_nmod_mpoly_mul(poly_aux2, &polinomials_division->polynomial[k_u], beta, ctx);
    fq_nmod_mpoly_pow_ui(poly_aux2, poly_aux2, 2, ctx);
    fmpz_set(aux, q);
    fmpz_pow_ui(aux, aux, 2);
    fq_nmod_mpoly_set_str_pretty(poly_aux7,"1*2", vars, ctx);
    //fq_nmod_mpoly_pow_fmpz(poly_aux, poly_aux, aux, ctx);
    poly_exp_mod(elliptic_poly, aux, &polinomials_division->polynomial[l_long], vars, ctx, poly_aux);

    fq_nmod_mpoly_mul(poly_aux, poly_aux7, poly_aux, ctx);
    fq_nmod_mpoly_add(poly_aux, poly_aux, poly_x, ctx);
    fq_nmod_mpoly_mul(poly_aux2, poly_aux, poly_aux2, ctx);

    simplify_if_possible(poly_aux2, poly_aux2, elliptic_poly, vars, ctx);
    simplify_if_possible(poly_aux2, poly_aux2, elliptic_poly, vars, ctx);
    reduce_poly_l(poly_aux2, &polinomials_division->polynomial[l_long], ctx, poly_aux2);

    //we add the three inner terms

    fq_nmod_mpoly_add(poly_aux2, poly_aux3, poly_aux2,ctx);
    fq_nmod_mpoly_add(poly_aux2, poly_aux4, poly_aux2,ctx);
    
    //poly_aux2 has the inner we have left multiply with alpha

    // most outer part..

    fq_nmod_mpoly_set_str_pretty(poly_aux7,"1*4", vars, ctx);
    fmpz_set(aux,q);
    fmpz_mul_ui(aux, aux, 3);

    if(fmpz_is_even(rho)){
        fq_nmod_mpoly_div(poly_aux8,&polinomials_division->polynomial[rho_u], poly_y, ctx);
        fq_nmod_mpoly_pow_fmpz(poly_aux8, poly_aux8, aux,ctx);

        fmpz_sub_ui(aux, aux, 1);
        fmpz_divexact_ui(aux, aux, 2);
        fq_nmod_mpoly_pow_fmpz(poly_aux9, elliptic_poly, aux, ctx);
        fq_nmod_mpoly_mul(poly_aux8, poly_aux9, poly_aux8, ctx);
        fq_nmod_mpoly_mul(poly_aux8, poly_y, poly_aux8, ctx);
        

    }else{
        fq_nmod_mpoly_pow_fmpz(poly_aux8, &polinomials_division->polynomial[rho_u], aux,ctx);
    }
    
    fmpz_set(aux,q);
    fmpz_sub_ui(aux, aux, 1);
    fmpz_divexact_ui(aux, aux, 2);

    //fq_nmod_mpoly_pow_fmpz(poly_aux9, elliptic_poly, aux, ctx);
    poly_exp_mod(elliptic_poly, aux, &polinomials_division->polynomial[l_long], vars, ctx, poly_aux9);

    fq_nmod_mpoly_mul(poly_aux9, poly_y, poly_aux9, ctx);

    fq_nmod_mpoly_mul(poly_aux8, poly_aux9, poly_aux8, ctx);
    simplify_if_possible(poly_aux8, poly_aux8, elliptic_poly, vars, ctx);
    simplify_if_possible(poly_aux8, poly_aux8, elliptic_poly, vars, ctx);
    reduce_poly_l(poly_aux8, &polinomials_division->polynomial[l_long], ctx, poly_aux8);

    fq_nmod_mpoly_mul(poly_aux9, poly_aux8, alpha, ctx);
    simplify_if_possible(poly_aux9, poly_aux9, elliptic_poly, vars, ctx);
    simplify_if_possible(poly_aux9, poly_aux9, elliptic_poly, vars, ctx);

    //the big left part
    fq_nmod_mpoly_mul(poly_aux9, poly_aux2, poly_aux9, ctx);
    //the midlle part
    fq_nmod_mpoly_mul(poly_aux8, poly_aux5, poly_aux8, ctx);

    fq_nmod_mpoly_sub(poly_aux, poly_aux9, poly_aux8, ctx);
    fq_nmod_mpoly_add(poly_aux, poly_aux, poly_aux6, ctx);

    simplify_if_possible(poly_aux, poly_aux, elliptic_poly, vars, ctx);
    reduce_poly_l(poly_aux, &polinomials_division->polynomial[l_long], ctx, poly_aux);

    fq_nmod_mpoly_set(ret, poly_aux, ctx);

    fq_nmod_mpoly_clear(poly_aux, ctx);
    fq_nmod_mpoly_clear(poly_aux2, ctx);
    fq_nmod_mpoly_clear(poly_aux3, ctx);
    fq_nmod_mpoly_clear(poly_aux4, ctx);
    fq_nmod_mpoly_clear(poly_aux5, ctx);
    fq_nmod_mpoly_clear(poly_aux6, ctx);
    fq_nmod_mpoly_clear(poly_aux7, ctx);
    fq_nmod_mpoly_clear(poly_aux8, ctx);
    fq_nmod_mpoly_clear(poly_aux9, ctx);
    fq_nmod_mpoly_clear(poly_x, ctx);
    fq_nmod_mpoly_clear(alpha, ctx);
    fq_nmod_mpoly_clear(beta, ctx);
    fmpz_clear(aux);
}

void p_17(fmpz_t l, fmpz_t q, fmpz_t q_red, fq_nmod_t A, fq_nmod_t B, fq_nmod_mpoly_t elliptic_poly, fq_nmod_mpoly_t poly_l,division_polynomials * polinomials_division,char ** vars ,fq_nmod_mpoly_ctx_t ctx ,fq_nmod_mpoly_t * ret){
    fq_nmod_mpoly_t poly_x;
    fq_nmod_mpoly_t poly_y;
    fq_nmod_mpoly_t poly_x_q;
    fq_nmod_mpoly_t poly_aux;
    fq_nmod_mpoly_t poly_aux2;
    fq_nmod_mpoly_t poly_aux3;

    fmpz_t aux;
    ulong k_long;
    ulong l_long;

    fmpz_init(aux);
    fmpz_set(aux, q);
    fq_nmod_mpoly_init(poly_x_q, ctx);
    fq_nmod_mpoly_init(poly_aux, ctx);
    fq_nmod_mpoly_init(poly_aux2, ctx);
    fq_nmod_mpoly_init(poly_aux3, ctx);
    fq_nmod_mpoly_init(poly_x, ctx);
    fq_nmod_mpoly_init(poly_y, ctx);
    fq_nmod_mpoly_init(poly_x_q, ctx);
    fq_nmod_mpoly_set_str_pretty(poly_x,"1*x", vars, ctx);
    fq_nmod_mpoly_set_str_pretty(poly_y,"1*y", vars, ctx);
    fq_nmod_mpoly_set(poly_x_q, poly_x, ctx);
    fq_nmod_mpoly_pow_fmpz(poly_x_q, poly_x_q, aux, ctx);

    k_long = fmpz_get_ui(q_red);
    l_long = fmpz_get_ui(l);
    
    if(fmpz_is_odd(q_red)){
        fq_nmod_mpoly_set(poly_aux, &polinomials_division->polynomial[k_long], ctx);
        fq_nmod_mpoly_mul(poly_aux, poly_aux, poly_aux, ctx);

        reduce_poly_l(poly_aux, &polinomials_division->polynomial[l_long], ctx, poly_aux);
    }else{
        fq_nmod_mpoly_set(poly_aux, &polinomials_division->polynomial[k_long], ctx);
        fq_nmod_mpoly_div(poly_aux, poly_aux, poly_y, ctx);
        fq_nmod_mpoly_mul(poly_aux, poly_aux, poly_aux, ctx);
        fq_nmod_mpoly_mul(poly_aux, poly_aux, elliptic_poly, ctx);

        reduce_poly_l(poly_aux, &polinomials_division->polynomial[l_long], ctx, poly_aux);

    }
    fq_nmod_mpoly_sub(poly_aux2, poly_x_q, poly_x, ctx);
    //poly_aux has the left part
    fq_nmod_mpoly_mul(poly_aux, poly_aux2, poly_aux, ctx);

    reduce_poly_l(poly_aux, &polinomials_division->polynomial[l_long], ctx, poly_aux);



    if(fmpz_is_even(q_red)){
        fq_nmod_mpoly_mul(poly_aux2, &polinomials_division->polynomial[k_long-1], &polinomials_division->polynomial[k_long+1], ctx);
    }else{
        fq_nmod_mpoly_mul(poly_aux2, &polinomials_division->polynomial[k_long-1], &polinomials_division->polynomial[k_long+1], ctx);
        fq_nmod_mpoly_div(poly_aux2, poly_aux2, poly_y, ctx);
        fq_nmod_mpoly_div(poly_aux2, poly_aux2, poly_y, ctx);
        fq_nmod_mpoly_mul(poly_aux2, elliptic_poly, poly_aux2, ctx);
    }

    reduce_poly_l(poly_aux2, &polinomials_division->polynomial[l_long], ctx, poly_aux2);


    //we add the two
    fq_nmod_mpoly_add(poly_aux, poly_aux, poly_aux2, ctx);
    fq_nmod_mpoly_set(ret,poly_aux,ctx);

    fq_nmod_mpoly_clear(poly_x, ctx);
    fq_nmod_mpoly_clear(poly_x_q, ctx);
    fq_nmod_mpoly_clear(poly_y, ctx);
    fq_nmod_mpoly_clear(poly_aux, ctx);
    fq_nmod_mpoly_clear(poly_aux2, ctx);
    fq_nmod_mpoly_clear(poly_aux3, ctx);

}

void p_18(fmpz_t l, fmpz_t q, fmpz_t q_red, fq_nmod_t A, fq_nmod_t B, fq_nmod_mpoly_t elliptic_poly, fq_nmod_mpoly_t poly_l,division_polynomials * polinomials_division,char ** vars ,fq_nmod_mpoly_ctx_t ctx ,fq_nmod_mpoly_t * ret){
    fq_nmod_mpoly_t poly_x;
    fq_nmod_mpoly_t poly_y;
    fq_nmod_mpoly_t poly_x_q;
    fq_nmod_mpoly_t poly_aux;
    fq_nmod_mpoly_t poly_aux2;
    fq_nmod_mpoly_t poly_aux3;
    fq_nmod_mpoly_t poly_literal;

    fmpz_t aux;
    ulong k_long;
    ulong l_long;



    fmpz_init(aux);
    fmpz_set(aux, q);
    fq_nmod_mpoly_init(poly_x_q, ctx);
    fq_nmod_mpoly_init(poly_aux, ctx);
    fq_nmod_mpoly_init(poly_aux2, ctx);
    fq_nmod_mpoly_init(poly_literal, ctx);
    fq_nmod_mpoly_init(poly_aux3, ctx);
    fq_nmod_mpoly_init(poly_x, ctx);
    fq_nmod_mpoly_init(poly_y, ctx);
    fq_nmod_mpoly_init(poly_x_q, ctx);
    fq_nmod_mpoly_set_str_pretty(poly_x,"1*x", vars, ctx);
    fq_nmod_mpoly_set_str_pretty(poly_y,"1*y", vars, ctx);
    fq_nmod_mpoly_set_str_pretty(poly_literal,"1*4", vars, ctx);
    fq_nmod_mpoly_set(poly_x_q, poly_x, ctx);
    fq_nmod_mpoly_pow_fmpz(poly_x_q, poly_x_q, aux, ctx);



    if(fmpz_is_one(q_red)){
        fmpz_set(q_red, l);
        fmpz_add_ui(q_red, q_red, 1);
    }

    k_long = fmpz_get_ui(q_red);
    l_long = fmpz_get_ui(l);
    
    if(fmpz_is_odd(q_red)){
        fmpz_sub_ui(aux, aux, 1);
        fmpz_divexact_ui(aux, aux, 2);

        fq_nmod_mpoly_pow_fmpz(poly_aux, elliptic_poly, aux, ctx);
        fq_nmod_mpoly_mul(poly_aux, poly_aux, poly_literal, ctx);

        fq_nmod_mpoly_pow_ui(poly_aux2, &polinomials_division->polynomial[k_long], 3, ctx);
        fq_nmod_mpoly_mul(poly_aux, poly_aux2, poly_aux, ctx);

        fq_nmod_mpoly_div(poly_aux2, &polinomials_division->polynomial[k_long-1], poly_y, ctx); 
        fq_nmod_mpoly_mul(poly_aux2, poly_aux2, poly_aux2, ctx);
        fq_nmod_mpoly_mul(poly_aux2, &polinomials_division->polynomial[k_long+2], poly_aux2, ctx); 

        fq_nmod_mpoly_div(poly_aux3, &polinomials_division->polynomial[k_long+1], poly_y, ctx); 
        fq_nmod_mpoly_mul(poly_aux3, poly_aux3, poly_aux3, ctx);
        fq_nmod_mpoly_mul(poly_aux3, &polinomials_division->polynomial[k_long-2], poly_aux3, ctx); 

        reduce_poly_l(poly_aux, &polinomials_division->polynomial[l_long], ctx, poly_aux);
        reduce_poly_l(poly_aux2, &polinomials_division->polynomial[l_long], ctx, poly_aux2);
        reduce_poly_l(poly_aux3, &polinomials_division->polynomial[l_long], ctx, poly_aux3);


    }

    if(fmpz_is_even(q_red)){
        fmpz_add_ui(aux, aux, 3);
        fmpz_divexact_ui(aux, aux, 2);

        fq_nmod_mpoly_pow_fmpz(poly_aux, elliptic_poly, aux, ctx);
        fq_nmod_mpoly_mul(poly_aux, poly_aux, poly_literal, ctx);

        fq_nmod_mpoly_div(poly_aux2, &polinomials_division->polynomial[k_long], poly_y, ctx); 
        fq_nmod_mpoly_pow_ui(poly_aux2, poly_aux2, 3, ctx);
        fq_nmod_mpoly_mul(poly_aux, poly_aux2, poly_aux, ctx);


        fq_nmod_mpoly_div(poly_aux2, &polinomials_division->polynomial[k_long+2], poly_y, ctx); 
        fq_nmod_mpoly_mul(poly_aux2, poly_aux2, &polinomials_division->polynomial[k_long-1], ctx);
        fq_nmod_mpoly_mul(poly_aux2, poly_aux2, &polinomials_division->polynomial[k_long-1], ctx);

        fq_nmod_mpoly_div(poly_aux3, &polinomials_division->polynomial[k_long-2], poly_y, ctx); 
        fq_nmod_mpoly_mul(poly_aux3, &polinomials_division->polynomial[k_long+1], poly_aux3, ctx); 
        fq_nmod_mpoly_mul(poly_aux3, &polinomials_division->polynomial[k_long+1], poly_aux3, ctx); 
        
        reduce_poly_l(poly_aux, &polinomials_division->polynomial[l_long], ctx, poly_aux);
        reduce_poly_l(poly_aux2, &polinomials_division->polynomial[l_long], ctx, poly_aux2);
        reduce_poly_l(poly_aux3, &polinomials_division->polynomial[l_long], ctx, poly_aux3);
    }
    //we add the two
    fq_nmod_mpoly_sub(poly_aux, poly_aux, poly_aux2, ctx);
    fq_nmod_mpoly_add(poly_aux, poly_aux, poly_aux3, ctx);

    fq_nmod_mpoly_set(ret,poly_aux,ctx);

    fq_nmod_mpoly_clear(poly_x, ctx);
    fq_nmod_mpoly_clear(poly_x_q, ctx);
    fq_nmod_mpoly_clear(poly_y, ctx);
    fq_nmod_mpoly_clear(poly_aux, ctx);
    fq_nmod_mpoly_clear(poly_aux2, ctx);
    fq_nmod_mpoly_clear(poly_aux3, ctx);
    fq_nmod_mpoly_clear(poly_literal, ctx);
}

void print_nmod_mpoly(fq_nmod_mpoly_t poly, char *s, char ** vars ,fq_nmod_mpoly_ctx_t ctx){
    flint_printf(s);
    fq_nmod_mpoly_print_pretty(poly, vars, ctx);
    flint_printf("\n");
}

void alpha_k(fmpz_t l, fmpz_t q, fmpz_t k, fq_nmod_mpoly_t elliptic_poly, division_polynomials * polinomials_division,char ** vars ,fq_nmod_mpoly_ctx_t ctx ,fq_nmod_mpoly_t * ret){
    fq_nmod_mpoly_t poly_y;
    fq_nmod_mpoly_t poly_aux;
    fq_nmod_mpoly_t poly_aux2;
    fq_nmod_mpoly_t poly_aux3;
    fq_nmod_mpoly_t poly_aux4;
    fmpz_t aux;


    ulong k_long;
    ulong l_long;
    k_long = fmpz_get_ui(k);
    l_long = fmpz_get_ui(l);


    fmpz_init(aux);
    fq_nmod_mpoly_init(poly_y, ctx);
    fq_nmod_mpoly_init(poly_aux, ctx);
    fq_nmod_mpoly_init(poly_aux2, ctx);
    fq_nmod_mpoly_init(poly_aux3, ctx);
    fq_nmod_mpoly_init(poly_aux4, ctx);
    fq_nmod_mpoly_set_str_pretty(poly_y,"1*y", vars, ctx);


    if(fmpz_is_even(k)){
        fq_nmod_mpoly_div(poly_aux, &polinomials_division->polynomial[k_long+2], poly_y, ctx);
        fq_nmod_mpoly_mul(poly_aux, &polinomials_division->polynomial[k_long-1], poly_aux, ctx);
        fq_nmod_mpoly_mul(poly_aux, &polinomials_division->polynomial[k_long-1], poly_aux, ctx);

        reduce_poly_l(poly_aux, &polinomials_division->polynomial[l_long], ctx, poly_aux);
        

        fq_nmod_mpoly_div(poly_aux2, &polinomials_division->polynomial[k_long-2], poly_y, ctx);
        fq_nmod_mpoly_mul(poly_aux2, &polinomials_division->polynomial[k_long+1], poly_aux2, ctx);
        fq_nmod_mpoly_mul(poly_aux2, &polinomials_division->polynomial[k_long+1], poly_aux2, ctx);

        reduce_poly_l(poly_aux2, &polinomials_division->polynomial[l_long], ctx, poly_aux2);


        fq_nmod_mpoly_div(poly_aux3, &polinomials_division->polynomial[k_long], poly_y, ctx);
        fq_nmod_mpoly_pow_ui(poly_aux3, poly_aux3, 3, ctx);

        reduce_poly_l(poly_aux3, &polinomials_division->polynomial[l_long], ctx, poly_aux3);

        fmpz_set(aux,q);
        fmpz_pow_ui(aux,aux,2);
        fmpz_add_ui(aux, aux, 3);
        //punto clave a mirar
        fmpz_divexact_ui(aux, aux, 2);
        fmpz_print(aux);
        flint_printf("\n");
        //
        //fq_nmod_mpoly_pow_fmpz(poly_aux4, elliptic_poly, aux, ctx);
        poly_exp_mod(elliptic_poly, aux, &polinomials_division->polynomial[l_long], vars, ctx, poly_aux4);
        reduce_poly_l(poly_aux4, &polinomials_division->polynomial[l_long], ctx, poly_aux4);

        fq_nmod_mpoly_mul(poly_aux3, poly_aux4, poly_aux3, ctx);

        reduce_poly_l(poly_aux3, &polinomials_division->polynomial[l_long], ctx, poly_aux3);

        //linea añadida que parece que falta, abajo
        /*fq_nmod_mpoly_mul(poly_aux3, poly_y, poly_aux3, ctx);*/

        fq_nmod_mpoly_set_str_pretty(poly_aux4, "4*1", vars, ctx);
        fq_nmod_mpoly_mul(poly_aux3, poly_aux3, poly_aux4, ctx);

        fq_nmod_mpoly_sub(poly_aux, poly_aux, poly_aux2, ctx);
        fq_nmod_mpoly_sub(poly_aux, poly_aux, poly_aux3, ctx);

        reduce_poly_l(poly_aux, &polinomials_division->polynomial[l_long], ctx, poly_aux);

        fq_nmod_mpoly_mul(poly_aux, poly_aux, poly_y, ctx);

    }

    if(fmpz_is_odd(k)){
        fq_nmod_mpoly_div(poly_aux, &polinomials_division->polynomial[k_long-1], poly_y, ctx);
        fq_nmod_mpoly_mul(poly_aux, poly_aux, poly_aux, ctx);
        reduce_poly_l(poly_aux, &polinomials_division->polynomial[l_long], ctx, poly_aux);

        fq_nmod_mpoly_mul(poly_aux, &polinomials_division->polynomial[k_long+2], poly_aux, ctx);
        
        reduce_poly_l(poly_aux, &polinomials_division->polynomial[l_long], ctx, poly_aux);

        print_nmod_mpoly(poly_aux, "poly_aux: ", vars, ctx);

        fq_nmod_mpoly_div(poly_aux2, &polinomials_division->polynomial[k_long+1], poly_y, ctx);
        fq_nmod_mpoly_mul(poly_aux2, poly_aux2, poly_aux2, ctx);
        fq_nmod_mpoly_mul(poly_aux2, &polinomials_division->polynomial[k_long-2], poly_aux2, ctx);

        reduce_poly_l(poly_aux2, &polinomials_division->polynomial[l_long], ctx, poly_aux2);

        print_nmod_mpoly(poly_aux2, "poly_aux: ", vars, ctx);

        fq_nmod_mpoly_pow_ui(poly_aux3,&polinomials_division->polynomial[k_long], 3, ctx);
        //fq_nmod_mpoly_div(poly_aux3, &polinomials_division->polynomial[k_long], poly_y, ctx);
        //fq_nmod_mpoly_pow_ui(poly_aux3, poly_aux3, 3, ctx);
        fmpz_set(aux,q);
        fmpz_pow_ui(aux,aux,2);
        fmpz_add_ui(aux, aux, 1);
        //
        fmpz_divexact_ui(aux, aux, 2);
        fmpz_print(aux);
        flint_printf("\n");
        //
        //fq_nmod_mpoly_pow_fmpz(poly_aux4, elliptic_poly, aux, ctx);
        poly_exp_mod(elliptic_poly, aux, &polinomials_division->polynomial[l_long], vars, ctx, poly_aux4);

        reduce_poly_l(poly_aux4, &polinomials_division->polynomial[l_long], ctx, poly_aux4);

        //print_nmod_mpoly(poly_aux4, "poly_aux: ", vars, ctx);

        
        fq_nmod_mpoly_mul(poly_aux3, poly_aux4, poly_aux3, ctx);
        reduce_poly_l(poly_aux3, &polinomials_division->polynomial[l_long], ctx, poly_aux3);

        fq_nmod_mpoly_set_str_pretty(poly_aux4, "4", vars, ctx);
        fq_nmod_mpoly_mul(poly_aux3, poly_aux3, poly_aux4, ctx);

        //print_nmod_mpoly(poly_aux3, "poly_aux: ", vars, ctx);

        fq_nmod_mpoly_sub(poly_aux, poly_aux, poly_aux2, ctx);
        //fq_nmod_mpoly_pow_ui(poly_aux2, poly_y, 2, ctx);
        fq_nmod_mpoly_mul(poly_aux, elliptic_poly, poly_aux, ctx);
        //print_nmod_mpoly(poly_aux, "poly_aux: ", vars, ctx);
        reduce_poly_l(poly_aux, &polinomials_division->polynomial[l_long], ctx, poly_aux);

        fq_nmod_mpoly_sub(poly_aux, poly_aux, poly_aux3, ctx);
        //print_nmod_mpoly(poly_aux, "poly_aux: ", vars, ctx);
    }
    reduce_poly_l(poly_aux, &polinomials_division->polynomial[l_long], ctx, poly_aux);
    fq_nmod_mpoly_set(ret, poly_aux, ctx);
    //print_nmod_mpoly(ret, "ret: ", vars, ctx);

    fq_nmod_mpoly_clear(poly_aux, ctx);
    fq_nmod_mpoly_clear(poly_aux2, ctx);
    fq_nmod_mpoly_clear(poly_aux3, ctx);
    fq_nmod_mpoly_clear(poly_aux4, ctx);
    fmpz_clear(aux);

}

void beta_k(fmpz_t l, fmpz_t q, fmpz_t k, fq_nmod_mpoly_t elliptic_poly, division_polynomials * polinomials_division,char ** vars ,fq_nmod_mpoly_ctx_t ctx ,fq_nmod_mpoly_t * ret){
    fq_nmod_mpoly_t poly_y;
    fq_nmod_mpoly_t poly_x;
    fq_nmod_mpoly_t poly_aux;
    fq_nmod_mpoly_t poly_aux2;
    fq_nmod_mpoly_t poly_aux3;
    fq_nmod_mpoly_t poly_aux4;
    fmpz_t aux;


    ulong k_long;
    ulong l_long;

    k_long = fmpz_get_ui(k);
    l_long = fmpz_get_ui(l);

    fmpz_init(aux);
    fq_nmod_mpoly_init(poly_y, ctx);
    fq_nmod_mpoly_init(poly_x, ctx);
    fq_nmod_mpoly_init(poly_aux, ctx);
    fq_nmod_mpoly_init(poly_aux2, ctx);
    fq_nmod_mpoly_init(poly_aux3, ctx);
    fq_nmod_mpoly_init(poly_aux4, ctx);
    fq_nmod_mpoly_set_str_pretty(poly_y,"1*y", vars, ctx);
    fq_nmod_mpoly_set_str_pretty(poly_x,"1*x", vars, ctx);



    if(fmpz_is_even(k)){
        fq_nmod_mpoly_div(poly_aux4, &polinomials_division->polynomial[k_long], poly_y, ctx);
        fmpz_set(aux, q);
        fmpz_pow_ui(aux, aux, 2);
        fq_nmod_mpoly_set(poly_aux2, poly_x, ctx);
        fq_nmod_mpoly_pow_fmpz(poly_aux2, poly_aux2, aux, ctx);
        fq_nmod_mpoly_sub(poly_aux, poly_x, poly_aux2, ctx);
        fq_nmod_mpoly_mul(poly_aux, poly_aux4, poly_aux, ctx);
        reduce_poly_l(poly_aux, &polinomials_division->polynomial[l_long], ctx, poly_aux);

        fq_nmod_mpoly_mul(poly_aux, poly_aux4, poly_aux, ctx);
        //fq_nmod_mpoly_mul(poly_aux, poly_y, poly_aux, ctx);
        //fq_nmod_mpoly_mul(poly_aux, poly_y, poly_aux, ctx);
        fq_nmod_mpoly_mul(poly_aux, elliptic_poly, poly_aux, ctx);
        reduce_poly_l(poly_aux, &polinomials_division->polynomial[l_long], ctx, poly_aux);



        fq_nmod_mpoly_mul(poly_aux3, &polinomials_division->polynomial[k_long-1],&polinomials_division->polynomial[k_long+1], ctx);
        reduce_poly_l(poly_aux3, &polinomials_division->polynomial[l_long], ctx, poly_aux3);


        fq_nmod_mpoly_sub(poly_aux, poly_aux, poly_aux3, ctx);

        fq_nmod_mpoly_mul(poly_aux, poly_aux4, poly_aux, ctx);
        //fq_nmod_mpoly_mul(poly_aux, poly_y, poly_aux, ctx);
        //fq_nmod_mpoly_mul(poly_aux, poly_y, poly_aux, ctx);
        fq_nmod_mpoly_mul(poly_aux, elliptic_poly, poly_aux, ctx);
        reduce_poly_l(poly_aux, &polinomials_division->polynomial[l_long], ctx, poly_aux);


        fq_nmod_mpoly_set_str_pretty(poly_aux2, "4*1", vars, ctx);
        fq_nmod_mpoly_mul(poly_aux, poly_aux2, poly_aux, ctx);

        //fq_nmod_mpoly_mul(poly_aux, poly_aux4, poly_aux, ctx);





        
    }

    if(fmpz_is_odd(k)){
        fq_nmod_mpoly_div(poly_aux4, &polinomials_division->polynomial[k_long-1], poly_y, ctx);
        fq_nmod_mpoly_div(poly_aux3, &polinomials_division->polynomial[k_long+1], poly_y, ctx);


        fq_nmod_mpoly_mul(poly_aux4, poly_aux3, poly_aux4, ctx);
        reduce_poly_l(poly_aux4, &polinomials_division->polynomial[l_long], ctx, poly_aux4);

        print_nmod_mpoly(poly_aux4, "poly_aux: ", vars, ctx);

        fq_nmod_mpoly_mul(poly_aux4, elliptic_poly, poly_aux4, ctx);
        //fq_nmod_mpoly_mul(poly_aux4, poly_y, poly_aux4, ctx);
        //fq_nmod_mpoly_mul(poly_aux4, poly_y, poly_aux4, ctx);
        reduce_poly_l(poly_aux4, &polinomials_division->polynomial[l_long], ctx, poly_aux4);


        fmpz_set(aux, q);
        fmpz_pow_ui(aux, aux, 2);
        fq_nmod_mpoly_pow_fmpz(poly_aux2, poly_x, aux, ctx);
        fq_nmod_mpoly_sub(poly_aux, poly_x, poly_aux2, ctx);

        print_nmod_mpoly(poly_aux, "poly_aux: ", vars, ctx);


        fq_nmod_mpoly_mul(poly_aux,  &polinomials_division->polynomial[k_long], poly_aux, ctx);
        fq_nmod_mpoly_mul(poly_aux,  &polinomials_division->polynomial[k_long], poly_aux, ctx);
        reduce_poly_l(poly_aux, &polinomials_division->polynomial[l_long], ctx, poly_aux);


        print_nmod_mpoly(poly_aux, "poly_aux: ", vars, ctx);


        fq_nmod_mpoly_sub(poly_aux, poly_aux, poly_aux4, ctx);
        fq_nmod_mpoly_mul(poly_aux, poly_aux, &polinomials_division->polynomial[k_long], ctx);
        fq_nmod_mpoly_mul(poly_aux, poly_aux, poly_y, ctx);

        fq_nmod_mpoly_set_str_pretty(poly_aux2, "4", vars, ctx);
        fq_nmod_mpoly_mul(poly_aux, poly_aux2, poly_aux, ctx);

        reduce_poly_l(poly_aux, &polinomials_division->polynomial[l_long], ctx, poly_aux);


        print_nmod_mpoly(poly_aux, "poly_aux: ", vars, ctx);

    }


    fq_nmod_mpoly_set(ret, poly_aux, ctx);

    fq_nmod_mpoly_clear(poly_aux, ctx);
    fq_nmod_mpoly_clear(poly_aux2, ctx);
    fq_nmod_mpoly_clear(poly_aux3, ctx);
    fq_nmod_mpoly_clear(poly_aux4, ctx);
    fq_nmod_mpoly_clear(poly_x, ctx);
    fq_nmod_mpoly_clear(poly_y, ctx);
    fmpz_clear(aux);
}


division_polynomials init_division_polynomials(fmpz_t n, fq_nmod_t A, fq_nmod_t B,fq_nmod_mpoly_t elliptic_poly,fq_nmod_mpoly_t ret, fq_nmod_mpoly_ctx_t ctx){
    
    fmpz_t it;
    int it_int;
    ulong number_of_polys;
    division_polynomials div_polys;
    number_of_polys = fmpz_get_ui(n);
    number_of_polys = number_of_polys +1; //we put the 0 division polynomial
    fmpz_init_set_ui(it, 0);


    div_polys.polynomial = malloc(sizeof(fq_nmod_mpoly_struct)*number_of_polys);
    
    while(fmpz_cmp(n, it)>=0){
        it_int = fmpz_get_ui(it);
        fq_nmod_mpoly_init(&div_polys.polynomial[it_int], ctx);
        division_polynomial(it, A, B, elliptic_poly, &div_polys.polynomial[it_int], ctx);
        fmpz_add_ui(it, it, 1);
    }

    return div_polys;

}


void get_final_l(int num_of, fmpz_t * primes, fmpz_t * t_l, fmpz_t hasse_bound, fmpz_t ret_l){
    fmpz_t mult;
    fmpz_t mod_partial;
    fmpz_init(mult);
    fmpz_init(mod_partial);

    fmpz_CRT(mod_partial, t_l[0], primes[0], t_l[1], primes[1], 0);
    fmpz_mul(mult, primes[0], primes[1]);
    for(int i = 2 ; i<num_of; i++){
        fmpz_CRT(mod_partial, mod_partial, mult, t_l[i], primes[i], 0);
        fmpz_mul(mult, mult, primes[i]);
    }

    fmpz_print(mod_partial);
    flint_printf("\n");

    if(fmpz_cmp(mod_partial, hasse_bound)>=0){
        fmpz_negmod(mod_partial, mod_partial, mult);
        fmpz_mul_si(mod_partial, mod_partial, -1);
    }


    fmpz_print(mod_partial);
    flint_printf("\n");
    fmpz_print(mult);
    flint_printf("\n");

    fmpz_set(ret_l, mod_partial);
}

void reduce_poly_l(fq_nmod_mpoly_t poly,fq_nmod_mpoly_t poly_l,fq_nmod_mpoly_ctx_t ctx ,fq_nmod_mpoly_t * ret){
    fq_nmod_mpoly_t poly_aux;
    fq_nmod_mpoly_t poly_aux2;
    fq_nmod_mpoly_init(poly_aux, ctx);
    fq_nmod_mpoly_init(poly_aux2, ctx);
    fq_nmod_mpoly_divrem(poly_aux, poly_aux2, poly, poly_l, ctx);
    fq_nmod_mpoly_set(ret, poly_aux2, ctx);

    fq_nmod_mpoly_clear(poly_aux, ctx);
    fq_nmod_mpoly_clear(poly_aux2, ctx);
}

void poly_exp_mod(fq_nmod_mpoly_t poly, fmpz_t exp, fq_nmod_mpoly_t mod, char ** vars  ,fq_nmod_mpoly_ctx_t ctx, fq_nmod_mpoly_t ret){
    fq_nmod_mpoly_t poly_aux;
    fq_nmod_mpoly_t poly_aux2;
    fq_nmod_mpoly_t poly_aux3; //the block
    fq_nmod_mpoly_t mult_final;
    fq_nmod_mpoly_init(poly_aux, ctx);
    fq_nmod_mpoly_init(poly_aux2, ctx);
    fq_nmod_mpoly_init(poly_aux3, ctx);
    fq_nmod_mpoly_init(mult_final, ctx);

    fq_nmod_mpoly_one(mult_final, ctx);

    fmpz_t counter;
    fmpz_t counter_possible;
    fmpz_t num_blocks;
    int enters = 0;
    fmpz_t remaining;
    fmpz_t remaining_exp;
    fmpz_init_set_ui(counter, 1);
    fmpz_init(counter_possible);
    fmpz_init(remaining);
    fmpz_set(counter_possible, exp);
    fmpz_init(num_blocks);
    fmpz_set_ui(num_blocks,1);

    fmpz_set(remaining_exp, exp);

    
    while(!fmpz_is_zero(remaining_exp)){
        
        fmpz_set_ui(counter, 1);
        fmpz_set(counter_possible, remaining_exp);
        fq_nmod_mpoly_set(poly_aux, poly, ctx);
        fq_nmod_mpoly_set(poly_aux3, poly, ctx);
        fmpz_set_ui(num_blocks,1);

        enters = 0;

        while(fmpz_cmp(counter, counter_possible)<0){

            enters = 1;
            //print_nmod_mpoly(poly_aux3, "f: ", vars, ctx);

            
            fq_nmod_mpoly_mul(poly_aux, poly_aux3, poly_aux, ctx);
            reduce_poly_l(poly_aux, mod, ctx, poly_aux2);
            print_nmod_mpoly(poly_aux, "f: ", vars, ctx);
            print_nmod_mpoly(mod, "f: ", vars, ctx);

            fmpz_add_ui(counter, counter, 1);
            if(!fq_nmod_mpoly_equal(poly_aux, poly_aux2, ctx)){//reduces

                fq_nmod_mpoly_set(poly_aux, poly_aux2, ctx);
                fq_nmod_mpoly_set(poly_aux3, poly_aux2, ctx);

                fmpz_mul(num_blocks, counter, num_blocks);
                fmpz_fdiv_qr(counter_possible, remaining, remaining_exp, num_blocks);
                fmpz_set_ui(counter, 1);
                //fmpz_cdiv_qr(counter_possible, remaining, exp, counter);
            }else{
                //fmpz_add_ui(counter, counter, 1);
            }
        }
        if(enters == 0){
            fmpz_set_ui(remaining_exp, 0);
        }else{
            fmpz_set(remaining_exp, remaining);
        }
        //print_nmod_mpoly(poly_aux, "f: ", vars, ctx);
        fq_nmod_mpoly_mul(mult_final, poly_aux, mult_final, ctx);
        //print_nmod_mpoly(mult_final, "f: ", vars, ctx);

        //fmpz_set(remaining_exp, remaining);
    }


    reduce_poly_l(mult_final, mod, ctx, mult_final);
    fq_nmod_mpoly_set(ret, mult_final, ctx);


}
