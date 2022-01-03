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
        fq_nmod_mpoly_print_pretty(poly_m, variables, ctx);
	    flint_printf("\n");

        fq_nmod_mpoly_pow_ui(fmpz_poly_aux1, poly_m, 3, ctx);
        fq_nmod_mpoly_mul(fmpz_poly_aux1, poly_m_plus_two, fmpz_poly_aux1, ctx);

        print_nmod_mpoly(fmpz_poly_aux1, "red: ", variables, ctx);

        fq_nmod_mpoly_pow_ui(fmpz_poly_aux2, poly_m_plus_one, 3, ctx);
        fq_nmod_mpoly_mul(fmpz_poly_aux2, poly_m_minus_one, fmpz_poly_aux2, ctx);

        print_nmod_mpoly(fmpz_poly_aux2, "red: ", variables, ctx);



        if(fmpz_is_even(aux)){
            fq_nmod_mpoly_div(fmpz_poly_aux1, fmpz_poly_aux1, fmpz_poly_y_pow_4, ctx);
            print_nmod_mpoly(fmpz_poly_aux1, "red: ", variables, ctx);

            fq_nmod_mpoly_mul(fmpz_poly_aux1, fmpz_poly_aux1, elliptic_poly, ctx);
            fq_nmod_mpoly_mul(fmpz_poly_aux1, fmpz_poly_aux1, elliptic_poly, ctx);
            print_nmod_mpoly(fmpz_poly_aux1, "red: ", variables, ctx);

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
    

    return 0;
}

void Schoofs(fq_nmod_t A, fq_nmod_t B, fmpz_t q, fq_nmod_ctx_t nmod_ctx){
    fmpz_t * primes;
    fmpz_t * t_l;
    fmpz_t hasse_bound;
    fmpz_t current_prime;
    fmpz_t mult;
    fmpz_t aux;
    fq_nmod_mpoly_ctx_t ctx;
    fq_nmod_mpoly_ctx_t ctx_4_vars;

    char ** variables; 

    variables = (char **)malloc(4*sizeof(char * ));
    variables[0] = "x";
    variables[1] = "y";
    variables[2] = "A";
    variables[3] = "B";



    fmpz_t q_red;
    fmpz_t l;
    int num_of = 1;
    int it;
    primes = (fmpz_t *)malloc(sizeof(fmpz_t)*1);

    fq_nmod_mpoly_ctx_init(ctx, 4, ORD_LEX, nmod_ctx);
    fq_nmod_mpoly_ctx_init(ctx_4_vars, 4, ORD_LEX, nmod_ctx);

    fmpz_init(hasse_bound);
    fmpz_init(mult);
    fmpz_init(aux);
    fmpz_init_set_ui(current_prime,3);

    primes = (fmpz_t *)malloc(sizeof(fmpz_t)*1);
    fmpz_init_set(primes[num_of-1], current_prime);

    fmpz_sqrt(hasse_bound, q);
    fmpz_mul_ui(hasse_bound, hasse_bound, 4);

    fmpz_set(mult, current_prime);
    while(fmpz_cmp(mult, hasse_bound) <= 0){
        fmpz_add_ui(aux,current_prime,1);
        fmpz_nextprime(current_prime, aux,1);

        fmpz_mul(mult, mult, current_prime);

        num_of++;
        primes = realloc(primes, sizeof(fmpz_t)*num_of);
        fmpz_init_set(primes[num_of-1], current_prime);

    }


    t_l = (fmpz_t *)malloc(sizeof(fmpz_t)*1);


    /*for(int i = 0; i<num_of; i++){

    }*/

    fmpz_init_set_ui(l, 3);
    fmpz_init(q_red);
    fmpz_mod(q_red, q, l);
    fmpz_set(aux,q_red);
    fmpz_set_ui(q_red,3);
    fmpz_print(aux);
    flint_printf("\n");

    fq_nmod_mpoly_t poly_l;
    fq_nmod_mpoly_t poly_elliptic;
    fq_nmod_mpoly_t poly_elliptic_ohne_y;
    fq_nmod_mpoly_t gcd;

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
    

    fq_nmod_mpoly_evaluate_one_fq_nmod(poly_l, poly_l, 2, A, ctx);
    fq_nmod_mpoly_evaluate_one_fq_nmod(poly_l, poly_l, 3, B, ctx);

    division_polynomial(l, A, B,poly_elliptic_ohne_y, poly_l, ctx);

    print_nmod_mpoly(poly_l, "poly_l: ", variables, ctx);

    division_polynomials div_polys =  init_division_polynomials(l,A,B,poly_elliptic,NULL, ctx);


    fq_nmod_mpoly_t ret1;
    fq_nmod_mpoly_init(ret1, ctx);

    p_16(l, q, q_red, A, B ,poly_elliptic_ohne_y, poly_l, variables, ctx, ret1);

    fq_nmod_mpoly_gcd(gcd, ret1, poly_l, ctx);
    print_nmod_mpoly(gcd, "gcd: ", variables, ctx);
    if(!fq_nmod_mpoly_is_one(gcd, ctx)){//case 1
        printf("bingo\n");
    }else{//case 2

    }




    /*nP calculated_point; 
    rational_polynomial x_s_rat;
    init_rational_polynomial(&x_s_rat, ctx);
    init_nP(&calculated_point, ctx);

    i_p(q_red, A, B, poly_elliptic, &calculated_point, ctx, nmod_ctx);

    go_to_quotient(&calculated_point.x_side, poly_l, poly_elliptic, ctx);
    go_to_quotient(&calculated_point.y_side, poly_l, poly_elliptic, ctx);
    simplify_if_possible(&calculated_point.x_side, ctx);
    simplify_if_possible(&calculated_point.y_side, ctx);



    print_rational_func(&calculated_point.x_side, variables, ctx);
    print_rational_func(&calculated_point.y_side, variables, ctx);

    //print_rational_func(&calculated_point.x_side, variables, ctx);
    //print_rational_func(&calculated_point.y_side, variables, ctx);
    x_s(poly_elliptic_ohne_y, calculated_point.y_side, q, calculated_point.x_side, poly_l ,ctx, nmod_ctx ,&x_s_rat);

    print_rational_func(&x_s_rat, variables, ctx);


    ////////////////
    fmpz_t aux2;
    fmpz_init(aux2);
    fmpz_set(aux2, l);
    fmpz_sub_ui(aux2,aux2,1);
    fmpz_divexact_ui(aux2, aux2, 2);
    fmpz_set_ui(aux, 1);
    nP i_P; 
    rational_polynomial x_part;
    fq_nmod_mpoly_t poly_aux;
    fq_nmod_mpoly_t poly_aux2;
    fmpz_t arca_perdida;
    fq_nmod_mpoly_init(poly_aux,ctx);
    fq_nmod_mpoly_init(poly_aux2,ctx);
    fmpz_init(arca_perdida);

    init_nP(&i_P, ctx);
    init_rational_polynomial(&x_part, ctx);

    while(fmpz_cmp(aux, aux2)<=0){// aux from 1 to l-1/2
        printf("trying-.. ");
        fmpz_print(aux);
        i_p(aux, A, B, poly_elliptic, &i_P, ctx, nmod_ctx);

        fq_nmod_mpoly_set(x_part.num, i_P.x_side.num, ctx);
        fq_nmod_mpoly_set(x_part.denom, i_P.x_side.denom, ctx);

        print_rational_func(&x_part, variables, ctx);


        fq_nmod_mpoly_pow_fmpz(x_part.num, x_part.num, q, ctx);
        fq_nmod_mpoly_pow_fmpz(x_part.denom, x_part.denom, q, ctx);

        print_rational_func(&x_part, variables, ctx);

        
        simplify_if_possible(&x_part,ctx);

        x_part = simplify_sub(&x_s_rat,&x_part,ctx);

        simplify_if_possible(&x_part,ctx);
        go_to_quotient(&x_part, poly_l, poly_elliptic, ctx);


        fq_nmod_mpoly_divrem(poly_aux2, poly_aux, x_part.num, poly_l, ctx);

        print_rational_func(&x_part, variables, ctx);
        printf("poly l : ");
        fq_nmod_mpoly_print_pretty(poly_l, variables, ctx);
        printf("\nquotient: ");
        fq_nmod_mpoly_print_pretty(poly_aux2, variables, ctx);
        printf("\nresidue: ");
        fq_nmod_mpoly_print_pretty(poly_aux, variables, ctx);
        printf("\n");

        if(fmpz_mpoly_is_zero(poly_aux, ctx)){
            printf("bingo \n");
        }


        fmpz_add_ui(aux,aux,1);
    }

    int error = fmpz_sqrtmod(aux, q, l);
    if(error == 0){
        fmpz_set_ui(arca_perdida, 0);
    }
    fmpz_print(aux);
    printf("\n");*/






    
}

void simplify_if_possible(rational_polynomial * rat_poly, fq_nmod_mpoly_ctx_t ctx){
    fq_nmod_mpoly_t gcd;
    fq_nmod_mpoly_init(gcd, ctx);

    fq_nmod_mpoly_gcd(gcd, rat_poly->num, rat_poly->denom, ctx);

    if(fq_nmod_mpoly_is_one(gcd, ctx) == 0){
        fq_nmod_mpoly_divides(rat_poly->num, rat_poly->num, gcd, ctx);
        fq_nmod_mpoly_divides(rat_poly->denom, rat_poly->denom, gcd, ctx);
    }
}

void go_to_quotient(rational_polynomial * rat_poly, rational_polynomial * quot1, rational_polynomial * quot2, fq_nmod_mpoly_ctx_t ctx){
    fq_nmod_mpoly_t aux1;
    fq_nmod_mpoly_init(aux1, ctx);
    fq_nmod_mpoly_t aux2;
    fq_nmod_mpoly_init(aux2, ctx);

    char ** variables = (char **)malloc(4*sizeof(char * ));
    variables[0] = "x";
    variables[1] = "y";
    variables[2] = "A";
    variables[3] = "B";

    fq_nmod_mpoly_divrem(aux1, aux2, rat_poly->num, quot1, ctx);
    fq_nmod_mpoly_set(rat_poly->num, aux2, ctx);

    fq_nmod_mpoly_divrem(aux1, aux2, rat_poly->num, quot2, ctx);
    fq_nmod_mpoly_set(rat_poly->num, aux2, ctx);

    fq_nmod_mpoly_divrem(aux1, aux2, rat_poly->denom, quot1, ctx);
    fq_nmod_mpoly_set(rat_poly->denom, aux2, ctx);

    fq_nmod_mpoly_divrem(aux1, aux2, rat_poly->denom, quot2, ctx);
    fq_nmod_mpoly_set(rat_poly->denom, aux2, ctx);
}



void init_rational_polynomial(rational_polynomial * rac, fq_nmod_mpoly_ctx_t ctx){
    fq_nmod_mpoly_init(rac->num, ctx);
    fq_nmod_mpoly_init(rac->denom, ctx);
}

void init_nP(nP * nP_var, fq_nmod_mpoly_ctx_t ctx){
    fmpz_init(nP_var->n);
    init_rational_polynomial(&nP_var->x_side, ctx);
    init_rational_polynomial(&nP_var->y_side, ctx);
}


void i_p(fmpz_t i, fq_nmod_t A, fq_nmod_t B, fq_nmod_mpoly_t poly_elliptic, nP * calculated_point, fq_nmod_mpoly_ctx_t ctx, fq_nmod_ctx_t nmod_ctx){
    fq_nmod_mpoly_t poly_q_minus_one;
    fq_nmod_mpoly_t poly_q;
    fq_nmod_mpoly_t poly_q_plus_one;
    fq_nmod_mpoly_t poly_2q;
    fq_nmod_mpoly_t poly_x;
    fq_nmod_mpoly_t poly_y;


    fq_nmod_mpoly_t x_i_num;
    fq_nmod_mpoly_t y_i_num;
    fq_nmod_mpoly_t x_i_denom;
    fq_nmod_mpoly_t y_i_denom;
    fq_nmod_mpoly_t poly_aux1;
    fq_nmod_mpoly_t poly_aux2;



    char ** variables = (char **)malloc(4*sizeof(char * ));
    variables[0] = "x";
    variables[1] = "y";
    variables[2] = "A";
    variables[3] = "B";

    fq_nmod_mpoly_ctx_t n_ctx;
    fmpz_mpoly_ctx_init(n_ctx, 2, ORD_DEGLEX);



    fmpz_t aux;
    fq_nmod_t aux_nmod;

    fq_nmod_init(aux_nmod, nmod_ctx);
    
    fmpz_set(aux, i);



    fq_nmod_mpoly_init(poly_q, ctx);
    fq_nmod_mpoly_init(poly_x, ctx);
    fq_nmod_mpoly_init(poly_y, ctx);
    fq_nmod_mpoly_init(poly_aux1, ctx);
    fq_nmod_mpoly_init(poly_aux2, ctx);

    fq_nmod_mpoly_init(poly_q_minus_one, ctx);
    fq_nmod_mpoly_init(poly_q_plus_one, ctx);
    fq_nmod_mpoly_init(poly_2q, ctx);
    fq_nmod_mpoly_init(x_i_num, ctx);
    fq_nmod_mpoly_init(x_i_denom, ctx);
    fq_nmod_mpoly_init(y_i_num, ctx);
    fq_nmod_mpoly_init(y_i_denom, ctx);


    fq_nmod_mpoly_set_str_pretty(poly_x,"x", variables, ctx);
    fq_nmod_mpoly_set_str_pretty(poly_y,"y", variables, ctx);


    fmpz_print(aux);
    flint_printf("\n");
    division_polynomial(aux, A,B, poly_elliptic,poly_q, ctx);
    fmpz_sub_ui(aux,aux,1);
    division_polynomial(aux, A,B, poly_elliptic, poly_q_minus_one, ctx);
    fmpz_add_ui(aux,aux,2);
    division_polynomial(aux, A,B, poly_elliptic, poly_q_plus_one, ctx);
    fmpz_sub_ui(aux,aux,1);
    fmpz_mul_ui(aux,aux,2);
    division_polynomial(aux, A,B, poly_elliptic, poly_2q, ctx);
    
    fq_nmod_mpoly_evaluate_one_fq_nmod(poly_q, poly_q, 2, A,ctx);
    fq_nmod_mpoly_evaluate_one_fq_nmod(poly_q, poly_q, 3, B,ctx);

    fq_nmod_mpoly_evaluate_one_fq_nmod(poly_q_plus_one, poly_q_plus_one, 2, A,ctx);
    fq_nmod_mpoly_evaluate_one_fq_nmod(poly_q_plus_one, poly_q_plus_one, 3, B,ctx);

    fq_nmod_mpoly_evaluate_one_fq_nmod(poly_q_minus_one, poly_q_minus_one, 2, A,ctx);
    fq_nmod_mpoly_evaluate_one_fq_nmod(poly_q_minus_one, poly_q_minus_one, 3, B,ctx);

    fq_nmod_mpoly_evaluate_one_fq_nmod(poly_2q, poly_2q, 2, A,ctx);
    fq_nmod_mpoly_evaluate_one_fq_nmod(poly_2q, poly_2q, 3, B,ctx);





    // x_i_num and x_i_denom
    fq_nmod_mpoly_mul(x_i_num, poly_q_plus_one, poly_q_minus_one, ctx);
    fq_nmod_mpoly_pow_ui(poly_aux1, poly_q, 2, ctx);

    flint_printf("prueba: ");
	fq_nmod_mpoly_print_pretty(poly_aux1, variables, ctx);
	flint_printf("\n");

    fq_nmod_mpoly_set(x_i_denom, poly_aux1, ctx);

    fq_nmod_mpoly_mul(poly_aux1, poly_aux1, poly_x, ctx);

    flint_printf("prueba: ");
	fq_nmod_mpoly_print_pretty(poly_aux1, variables, ctx);
	flint_printf("\n");

    flint_printf("prueba: ");
	fq_nmod_mpoly_print_pretty(x_i_num, variables, ctx);
	flint_printf("\n");

    fq_nmod_mpoly_sub(x_i_num, poly_aux1, x_i_num, ctx);


    //
    fq_nmod_mpoly_pow_ui(poly_aux1, poly_q, 4, ctx);

    fq_nmod_set_ui(aux_nmod, 2, nmod_ctx);
    fq_nmod_mpoly_scalar_mul_fq_nmod(poly_aux1, poly_aux1, aux_nmod, ctx);
    fq_nmod_mpoly_set(y_i_denom, poly_aux1, ctx);

    fq_nmod_mpoly_set(y_i_num, poly_2q, ctx);

    ///////////////////////////////////////

    flint_printf("x_num: ");
	fq_nmod_mpoly_print_pretty(x_i_num, variables, ctx);
	flint_printf("\n");

    flint_printf("x_denom: ");
	fq_nmod_mpoly_print_pretty(x_i_denom, variables, ctx);
	flint_printf("\n");


    flint_printf("y_num: ");
	fq_nmod_mpoly_print_pretty(y_i_num, variables, ctx);
	flint_printf("\n");

    flint_printf("y_denom: ");
	fq_nmod_mpoly_print_pretty(y_i_denom, variables, ctx);
	flint_printf("\n");

    int divides = fq_nmod_mpoly_divides(poly_aux1, y_i_num, poly_y, ctx);
    if(divides == 1){
        fq_nmod_mpoly_set(y_i_num, poly_aux1, ctx);
    }


    flint_printf("y_num: ");
	fq_nmod_mpoly_print_pretty(y_i_num, variables, ctx);
	flint_printf("\n");

    fmpz_set(calculated_point->n, i);
    fq_nmod_mpoly_set(calculated_point->x_side.num, x_i_num, ctx);
    fq_nmod_mpoly_set(calculated_point->x_side.denom, x_i_denom, ctx);

    fq_nmod_mpoly_set(calculated_point->y_side.num, y_i_num, ctx);
    fq_nmod_mpoly_set(calculated_point->y_side.denom, y_i_denom, ctx);

    fq_nmod_mpoly_clear(poly_2q, ctx);
    fq_nmod_mpoly_clear(poly_q, ctx);
    fq_nmod_mpoly_clear(poly_aux1, ctx);
    fq_nmod_mpoly_clear(poly_aux2, ctx);
    fq_nmod_mpoly_clear(poly_q_minus_one, ctx);
    fq_nmod_mpoly_clear(poly_q_plus_one, ctx);
    fq_nmod_mpoly_clear(poly_x, ctx);
    fq_nmod_mpoly_clear(poly_y, ctx);


}

rational_polynomial simplify_sum(rational_polynomial * rat_poly1, rational_polynomial * rat_poly2, fq_nmod_mpoly_ctx_t ctx){
    fq_nmod_mpoly_t poly_aux1;
    fq_nmod_mpoly_t poly_aux2;
    fq_nmod_mpoly_t gcd;
    rational_polynomial ret;

    fq_nmod_mpoly_init(poly_aux1, ctx);
    fq_nmod_mpoly_init(poly_aux2, ctx);
    fq_nmod_mpoly_init(gcd, ctx);
    init_rational_polynomial(&ret, ctx);

    if(fq_nmod_mpoly_is_zero(rat_poly1->num, ctx) || fq_nmod_mpoly_is_zero(rat_poly1->denom, ctx)){
        fq_nmod_mpoly_set(ret.num,rat_poly2->num , ctx);
        fq_nmod_mpoly_set(ret.denom,rat_poly2->denom , ctx);

        fq_nmod_mpoly_clear(poly_aux1,ctx);
        fq_nmod_mpoly_clear(poly_aux2,ctx);
        fq_nmod_mpoly_clear(gcd,ctx);

        return ret;
    }
    if(fq_nmod_mpoly_is_zero(rat_poly2->num, ctx) || fq_nmod_mpoly_is_zero(rat_poly2->denom, ctx)){
        fq_nmod_mpoly_set(ret.num,rat_poly1->num , ctx);
        fq_nmod_mpoly_set(ret.denom,rat_poly1->denom , ctx);
        fq_nmod_mpoly_clear(poly_aux1,ctx);
        fq_nmod_mpoly_clear(poly_aux2,ctx);
        fq_nmod_mpoly_clear(gcd,ctx);

        return ret;
    }

    fq_nmod_mpoly_mul(poly_aux1, rat_poly1->denom, rat_poly2->denom, ctx);

    fq_nmod_mpoly_gcd(gcd, rat_poly1->denom, rat_poly2->denom,ctx);
    fq_nmod_mpoly_divides(ret.denom, poly_aux1, gcd, ctx);

    fq_nmod_mpoly_divides(poly_aux1, ret.denom, rat_poly1->denom, ctx);
    fq_nmod_mpoly_divides(poly_aux2, ret.denom, rat_poly2->denom, ctx);

    fq_nmod_mpoly_mul(ret.num, poly_aux1, rat_poly1->num, ctx);
    fq_nmod_mpoly_mul(poly_aux1, poly_aux2, rat_poly2->num, ctx);

    fq_nmod_mpoly_add(ret.num, ret.num, poly_aux1, ctx);

    fq_nmod_mpoly_clear(poly_aux1,ctx);
    fq_nmod_mpoly_clear(poly_aux2,ctx);
    fq_nmod_mpoly_clear(gcd,ctx);

    return ret;
}
//rat_poly1/rat_poly2
rational_polynomial simplify_division(rational_polynomial * rat_poly1, rational_polynomial * rat_poly2, fq_nmod_mpoly_ctx_t ctx){
    rational_polynomial ret;
    
    init_rational_polynomial(&ret, ctx);

    if(fq_nmod_mpoly_is_zero(rat_poly2->num, ctx)){
        fq_nmod_mpoly_zero(ret.num, ctx);
        fq_nmod_mpoly_one(ret.denom, ctx);

        return ret;
    }


    fq_nmod_mpoly_mul(ret.num, rat_poly1->num, rat_poly2->denom, ctx);
    fq_nmod_mpoly_mul(ret.denom, rat_poly2->num, rat_poly1->denom, ctx);

    return ret;
}
rational_polynomial simplify_sub(rational_polynomial * rat_poly1, rational_polynomial * rat_poly2, fq_nmod_mpoly_ctx_t ctx){
    fq_nmod_mpoly_t poly_aux1;
    fq_nmod_mpoly_t poly_aux2;
    fq_nmod_mpoly_t zero_pol;
    fq_nmod_mpoly_t gcd;
    rational_polynomial ret;

    fq_nmod_mpoly_init(poly_aux1, ctx);
    fq_nmod_mpoly_init(poly_aux2, ctx);
    fq_nmod_mpoly_init(zero_pol, ctx);
    fq_nmod_mpoly_init(gcd, ctx);
    init_rational_polynomial(&ret, ctx);
    fq_nmod_mpoly_zero(zero_pol, ctx);

    if(fq_nmod_mpoly_is_zero(rat_poly1->num, ctx) || fq_nmod_mpoly_is_zero(rat_poly1->denom, ctx)){
        fq_nmod_mpoly_set(ret.num,rat_poly2->num , ctx);
        fq_nmod_mpoly_sub(ret.num, zero_pol, ret.num, ctx);
        fq_nmod_mpoly_set(ret.denom,rat_poly2->denom , ctx);
        fq_nmod_mpoly_clear(poly_aux1,ctx);
        fq_nmod_mpoly_clear(poly_aux2,ctx);
        fq_nmod_mpoly_clear(gcd,ctx);

        return ret;
    }
    if(fq_nmod_mpoly_is_zero(rat_poly2->num, ctx) || fq_nmod_mpoly_is_zero(rat_poly2->denom, ctx)){
        fq_nmod_mpoly_set(ret.num,rat_poly1->num , ctx);
        fq_nmod_mpoly_set(ret.denom,rat_poly1->denom , ctx);
        fq_nmod_mpoly_clear(poly_aux1,ctx);
        fq_nmod_mpoly_clear(poly_aux2,ctx);
        fq_nmod_mpoly_clear(gcd,ctx);

        return ret;
    }

    fq_nmod_mpoly_mul(poly_aux1, rat_poly1->denom, rat_poly2->denom, ctx);

    fq_nmod_mpoly_gcd(gcd, rat_poly1->denom, rat_poly2->denom,ctx);
    fq_nmod_mpoly_divides(ret.denom, poly_aux1, gcd, ctx);

    fq_nmod_mpoly_divides(poly_aux1, ret.denom, rat_poly1->denom, ctx);
    fq_nmod_mpoly_divides(poly_aux2, ret.denom, rat_poly2->denom, ctx);

    fq_nmod_mpoly_mul(ret.num, poly_aux1, rat_poly1->num, ctx);
    fq_nmod_mpoly_mul(poly_aux1, poly_aux2, rat_poly2->num, ctx);

    fq_nmod_mpoly_sub(ret.num, ret.num, poly_aux1, ctx);

    fq_nmod_mpoly_clear(poly_aux1,ctx);
    fq_nmod_mpoly_clear(poly_aux2,ctx);
    fq_nmod_mpoly_clear(gcd,ctx);

    return ret;
}


rational_polynomial simplify_mult(rational_polynomial * rat_poly1, rational_polynomial * rat_poly2, fq_nmod_mpoly_ctx_t ctx){
    rational_polynomial ret;

    
    init_rational_polynomial(&ret, ctx);

    fq_nmod_mpoly_mul(ret.num, rat_poly1->num, rat_poly2->num, ctx);
    fq_nmod_mpoly_mul(ret.denom, rat_poly2->denom, rat_poly1->denom, ctx);


    return ret;


}

void x_s(fq_nmod_mpoly_t elliptic_poly, rational_polynomial rational_part_y, fmpz_t q, rational_polynomial rational_part_x, fq_nmod_mpoly_t poly_l,fq_nmod_mpoly_ctx_t ctx, fq_nmod_ctx_t nmod_ctx ,rational_polynomial * ret){
    fq_nmod_mpoly_t poly_aux1, poly_aux2, poly_aux3;
    fq_nmod_mpoly_t poly_x;
    fq_nmod_mpoly_t poly_x_pow_q_2;
    fq_nmod_mpoly_t poly_one;
    fq_nmod_mpoly_ctx_t ctx_extra;

    rational_polynomial r1, r2, r3;

    init_rational_polynomial(&r1, ctx);
    init_rational_polynomial(&r2, ctx);
    init_rational_polynomial(&r3, ctx);




    fmpz_t aux;
    fmpz_t aux2;

    char ** variables = (char **)malloc(4*sizeof(char * ));
    variables[0] = "x";
    variables[1] = "y";
    variables[2] = "A";
    variables[3] = "B";

    fq_nmod_mpoly_init(poly_aux1, ctx);
    fq_nmod_mpoly_init(poly_aux2, ctx);
    fq_nmod_mpoly_init(poly_aux3, ctx);
    fq_nmod_mpoly_init(poly_x_pow_q_2, ctx);
    fq_nmod_mpoly_init(poly_x, ctx);
    fq_nmod_mpoly_init(poly_one, ctx);
    fq_nmod_mpoly_ctx_init(ctx_extra, 2, ORD_DEGLEX, nmod_ctx);

    fq_nmod_mpoly_one(poly_one, ctx);
    fq_nmod_mpoly_set_str_pretty(poly_x, "x", variables,ctx);

    fmpz_init(aux);
    fmpz_init(aux2);
    fmpz_set(aux, q);
    fmpz_pow_ui(aux, aux, 2);
       


   

    fq_nmod_mpoly_set(poly_x_pow_q_2, poly_x,ctx);
    fq_nmod_mpoly_pow_fmpz(poly_x_pow_q_2, poly_x_pow_q_2, aux, ctx);

    /////////////////////////////////////////////////

    //(eliptic)^q^2-1/2
    fmpz_sub_ui(aux2, aux, 1);
    fmpz_divexact_ui(aux2, aux2, 2);
    fq_nmod_mpoly_pow_fmpz(poly_aux1, elliptic_poly, aux2, ctx);

    fq_nmod_mpoly_set(r1.num, poly_aux1, ctx);
    fq_nmod_mpoly_set(r1.denom, poly_one, ctx);

    //print_rational_func(&r1, variables, ctx);


    rational_polynomial inner = simplify_sub(&r1, &rational_part_y, ctx);

    //print_rational_func(&inner, variables, ctx);

    fq_nmod_mpoly_pow_ui(inner.num, inner.num, 2, ctx);
    fq_nmod_mpoly_pow_ui(inner.denom, inner.denom, 2, ctx);

    //print_rational_func(&inner, variables, ctx);


    fq_nmod_mpoly_set(r1.num, elliptic_poly, ctx);

    //print_rational_func(&inner, variables, ctx);
    //print_rational_func(&r1, variables, ctx);

    simplify_if_possible(&inner, ctx);

    //print_rational_func(&inner, variables, ctx);
    go_to_quotient(&inner, poly_l, elliptic_poly, ctx);

    //print_rational_func(&inner, variables, ctx);

    //fq_nmod_mpoly_mul(r2.num, r1.num, inner.num, ctx);
    r2 = simplify_mult(&r1,&inner, ctx);
    //fq_nmod_mpoly_mul(ret.denom, rat_poly2->denom, rat_poly1->denom, ctx); 

    print_rational_func(&r2, variables, ctx);
    fq_nmod_mpoly_clear(inner.num, ctx);
    fq_nmod_mpoly_clear(inner.denom, ctx);



    //r2 has the numerator (rational)
    //////////////////
    // denominator working
    //resetamos?:::
    fq_nmod_mpoly_set(poly_aux1, poly_x,ctx);
    fq_nmod_mpoly_pow_fmpz(poly_aux1, poly_aux1, aux, ctx);
    fq_nmod_mpoly_print_pretty(poly_aux1, variables, ctx);
    printf("\n");

    fq_nmod_mpoly_set(r1.num, poly_aux1, ctx);
    fq_nmod_mpoly_set(r1.denom, poly_one, ctx);

    print_rational_func(&r1, variables, ctx);
    print_rational_func(&rational_part_x, variables, ctx);



    r3 = simplify_sub(&r1, &rational_part_x, ctx);
    print_rational_func(&r3, variables, ctx);

    simplify_if_possible(&r3, ctx);
    print_rational_func(&r3, variables, ctx);
    go_to_quotient(&r3, poly_l, elliptic_poly, ctx);

    print_rational_func(&r3, variables, ctx);


    fq_nmod_mpoly_pow_ui(r3.num, r3.num, 2, ctx);
    fq_nmod_mpoly_pow_ui(r3.denom, r3.denom, 2, ctx);

    simplify_if_possible(&r3, ctx);
    go_to_quotient(&r3, poly_l, elliptic_poly, ctx);

    print_rational_func(&r3, variables, ctx);



    //print_rational_func(&r2, variables, ctx);
    //print_rational_func(&r3, variables, ctx);

    r1 = simplify_division(&r2,&r3, ctx);

    print_rational_func(&r1, variables, ctx);




    // r1 has the left part

    fq_nmod_mpoly_set(r2.num, poly_x_pow_q_2, ctx);
    fq_nmod_mpoly_set(r2.denom, poly_one, ctx);

    r3 = simplify_sum(&r2,&rational_part_x, ctx);

    print_rational_func(&r3, variables, ctx);

    simplify_if_possible(&r3, ctx);
    go_to_quotient(&r3, poly_l, elliptic_poly, ctx);

    print_rational_func(&r3, variables, ctx);
    print_rational_func(&r1, variables, ctx);




    //print_rational_func(&r1, variables, ctx);
    //print_rational_func(&r3, variables, ctx);

    r2 = simplify_sub(&r1, &r3, ctx);

    fq_nmod_mpoly_set(ret->num ,r2.num, ctx);
    fq_nmod_mpoly_set(ret->denom ,r2.denom, ctx);

    print_rational_func(&r2, variables, ctx);


    simplify_if_possible(ret, ctx);

    //print_rational_func(ret, variables, ctx);

    fq_nmod_mpoly_clear(poly_aux1, ctx);
    fq_nmod_mpoly_clear(poly_aux2, ctx);
    fq_nmod_mpoly_clear(poly_aux3, ctx);
    fq_nmod_mpoly_clear(poly_x, ctx);
    fq_nmod_mpoly_clear(poly_x_pow_q_2, ctx);
    fmpz_clear(aux2);

}


void print_rational_func(rational_polynomial * rat_poly1, char ** variables ,fq_nmod_mpoly_ctx_t ctx){
    flint_printf("f/g: ");
    fq_nmod_mpoly_print_pretty(rat_poly1->num, variables, ctx);
    flint_printf("  /  ");
    fq_nmod_mpoly_print_pretty(rat_poly1->denom, variables, ctx);

    flint_printf("\n");
}


void p_16(fmpz_t l, fmpz_t q, fmpz_t q_red, fq_nmod_t A, fq_nmod_t B, fq_nmod_mpoly_t elliptic_poly, fq_nmod_mpoly_t poly_l, char ** vars ,fq_nmod_mpoly_ctx_t ctx,fq_nmod_mpoly_t * ret){
    fq_nmod_mpoly_t poly_k_minus_one;
    fq_nmod_mpoly_t poly_k;
    fq_nmod_mpoly_t poly_k_plus_one;
    fq_nmod_mpoly_t poly_x;
    fq_nmod_mpoly_t poly_y;
    fq_nmod_mpoly_t poly_x_q_2;
    fq_nmod_mpoly_t poly_aux;
    fq_nmod_mpoly_t poly_aux2;
    fmpz_t aux;

    fmpz_init(aux);
    fmpz_set(aux, q);
    fmpz_pow_ui(aux,aux, 2);
    fq_nmod_mpoly_init(poly_k_minus_one, ctx);
    fq_nmod_mpoly_init(poly_k_plus_one, ctx);
    fq_nmod_mpoly_init(poly_k, ctx);
    fq_nmod_mpoly_init(poly_x_q_2, ctx);
    fq_nmod_mpoly_init(poly_aux, ctx);
    fq_nmod_mpoly_init(poly_aux2, ctx);
    fq_nmod_mpoly_init(poly_x, ctx);
    fq_nmod_mpoly_init(poly_y, ctx);
    fq_nmod_mpoly_init(poly_x_q_2, ctx);
    fq_nmod_mpoly_set_str_pretty(poly_x,"1*x", vars, ctx);
    fq_nmod_mpoly_set_str_pretty(poly_y,"1*y", vars, ctx);
    fq_nmod_mpoly_set(poly_x_q_2, poly_x, ctx);
    fq_nmod_mpoly_pow_fmpz(poly_x_q_2, poly_x_q_2, aux, ctx);

    division_polynomial(q_red, A,B, elliptic_poly,poly_k,ctx);
    fmpz_set(aux, q_red);
    fmpz_add_ui(aux,aux,1);
    division_polynomial(aux, A,B, elliptic_poly, poly_k_plus_one,ctx);
    fmpz_sub_ui(aux, aux, 2);
    division_polynomial(aux, A,B, elliptic_poly ,poly_k_minus_one,ctx);
    //fq_nmod_mpoly_evaluate_one_fq_nmod(poly_q, poly_q, 2, A,ctx);
    //fq_nmod_mpoly_evaluate_one_fq_nmod(poly_q, poly_q, 3, B,ctx);

    print_nmod_mpoly(poly_k, "ret: ", vars ,ctx);
    print_nmod_mpoly(poly_k_plus_one, "ret: ", vars ,ctx);
    print_nmod_mpoly(poly_k_minus_one, "ret: ", vars ,ctx);





    // poly_aux <-- leftpart
    fq_nmod_mpoly_sub(poly_aux, poly_x_q_2, poly_x, ctx);
    if(fmpz_is_even(q_red)){
        fq_nmod_mpoly_div(poly_k, poly_k, poly_y, ctx);
        fq_nmod_mpoly_mul(poly_aux, poly_aux, elliptic_poly, ctx);
    }
    print_nmod_mpoly(poly_k, "left: ", vars ,ctx);
    fq_nmod_mpoly_pow_ui(poly_aux2, poly_k, 2, ctx);

    print_nmod_mpoly(poly_aux, "left: ", vars ,ctx);
    print_nmod_mpoly(poly_aux2, "left: ", vars ,ctx);

    fq_nmod_mpoly_mul(poly_aux, poly_aux, poly_aux2, ctx);


    print_nmod_mpoly(poly_aux, "left: ", vars ,ctx);



    //poly_aux2 <-- righthand
    
    if(fmpz_is_odd(q_red)){
        fq_nmod_mpoly_div(poly_k_plus_one, poly_k_plus_one, poly_y, ctx);
        fq_nmod_mpoly_div(poly_k_minus_one, poly_k_minus_one, poly_y, ctx);
        fq_nmod_mpoly_mul(poly_aux2, poly_k_minus_one, poly_k_plus_one, ctx);
            
        print_nmod_mpoly(poly_k_minus_one, "right: ", vars ,ctx);
        print_nmod_mpoly(poly_k_plus_one, "right: ", vars ,ctx);


        fq_nmod_mpoly_mul(poly_aux2, poly_aux2, elliptic_poly, ctx);

    }else{
        fq_nmod_mpoly_mul(poly_aux2, poly_k_minus_one, poly_k_plus_one, ctx);
    }

    print_nmod_mpoly(poly_aux2, "right: ", vars ,ctx);

    fq_nmod_mpoly_add(poly_aux, poly_aux, poly_aux2, ctx);
    fq_nmod_mpoly_set(ret, poly_aux, ctx);

    print_nmod_mpoly(ret, "ret: ", vars ,ctx);

    fq_nmod_mpoly_clear(poly_k_minus_one, ctx);
    fq_nmod_mpoly_clear(poly_k_plus_one, ctx);
    fq_nmod_mpoly_clear(poly_k, ctx);
    fq_nmod_mpoly_clear(poly_x, ctx);
    fq_nmod_mpoly_clear(poly_x_q_2, ctx);
    fq_nmod_mpoly_clear(poly_y, ctx);
    fq_nmod_mpoly_clear(poly_aux, ctx);
    fq_nmod_mpoly_clear(poly_aux2, ctx);

}

void p_19x(fmpz_t l, fmpz_t rho, fmpz_t q, fmpz_t q_red, fq_nmod_t A, fq_nmod_t B, fq_nmod_mpoly_t elliptic_poly, fq_nmod_mpoly_t poly_l, char ** vars ,fq_nmod_mpoly_ctx_t ctx ,fq_nmod_mpoly_t * ret){

}



void print_nmod_mpoly(fq_nmod_mpoly_t poly, char *s, char ** vars ,fq_nmod_mpoly_ctx_t ctx){
    flint_printf(s);
    fq_nmod_mpoly_print_pretty(poly, vars, ctx);
    flint_printf("\n");
}

division_polynomials init_division_polynomials(fmpz_t n, fq_nmod_t A, fq_nmod_t B,fq_nmod_mpoly_t elliptic_poly,fq_nmod_mpoly_t ret, fq_nmod_mpoly_ctx_t ctx){
    
    int it = 0;
    ulong n_long;
    division_polynomials div_polys;
    n_long = fmpz_get_ui(n);


    div_polys.polynomial = malloc(sizeof(fq_nmod_mpoly_struct)*n_long);
    
    while(fmpz_cmp_ui(n, it)>=0){
        fq_nmod_mpoly_init(&div_polys.polynomial[it], ctx);
        division_polynomial(it, A, B, elliptic_poly, &div_polys.polynomial[it], ctx);
        n++;
    }

    return div_polys;

}