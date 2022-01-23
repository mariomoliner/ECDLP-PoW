#include "Utility.h"
#include "Logging.h"



BIGNUM * Next_prime(BIGNUM *x){
	LOG_BN_DEBUG("Finding next prime of number", x);
	BIGNUM *k = BN_new();
	BIGNUM *i = BN_new();
	int to_sum;
	BIGNUM *aux = BN_new();
	BIGNUM *aux2 = BN_new();
	BIGNUM *literal = BN_new();
	BIGNUM *o = BN_new();
	BN_CTX * bn_ctx = BN_CTX_new();
	int a = 0;
	bool found = FALSE;

	BN_set_word(literal, 2);
	
	BN_copy(k, x);
	BN_div_word(k,6);
	BN_copy(i, k);
	BN_mul_word(i,6);
	BN_sub(i,x,i);


	if(BN_cmp(i,literal)<0){
		to_sum = 4;
		BN_set_word(o, 1);
	}else{
		to_sum = 2;
		BN_set_word(o, 5);
	}

	BN_mul_word(k,6);
	BN_copy(x,k);
	//BN_div_word(x,6);
	BN_add(x,x,o);


	while(a <1000000){
		//BN_set_word(literal, 4);
		if(to_sum==4){
			to_sum=2;
		}else{
			to_sum=4;
		}


		if(BN_is_prime(x,128,NULL,bn_ctx,NULL)){
			LOG_BN_DEBUG("Prime found!", x);
			found = TRUE;
			break;
			
		}
		BN_add_word(x,to_sum);
		a++;
	}

	BN_free(k);
	BN_free(i);
	BN_free(o);
	BN_free(aux);
	BN_free(aux2);
	BN_free(literal);
	BN_CTX_free(bn_ctx);

	if(found == TRUE){
	}else{
		LOG("prime not found!");
		BN_set_word(x,-1);
	}

	return x;


}

BIGNUM * Cardinal_EllipticCurveGroup(EC_GROUP * E){
	BIGNUM *a = BN_new();
	BIGNUM *b = BN_new();
	BIGNUM *p = BN_new();
	BIGNUM *aux = BN_new();
	BIGNUM * bn_ctx = BN_CTX_new();
	BIGNUM * iter = BN_new();
	BIGNUM * M = BN_new();
	bool finished = FALSE;
	bool unique = FALSE;
	int num_founds = 0;
	EC_POINT * point = EC_POINT_new(E);
	EC_POINT * point_to = EC_POINT_new(E);

	EC_GROUP_get_curve(E, p, a, b, bn_ctx);

	BIGNUM * cota_inf = BN_new();
	BIGNUM * cota_sup = BN_new();

	
	aux = SquareRoot(p);
	BN_mul_word(aux,2);

	BN_copy(cota_inf, p);
	BN_copy(cota_sup, p);
	BN_add_word(cota_sup,1);
	BN_add_word(cota_inf,1);


	BN_add(cota_sup, cota_sup, aux);
	BN_sub(cota_inf, cota_inf, aux);



	while(!unique){

		point = getRandomPoint(E);


		BN_copy(iter,cota_inf);
		finished = FALSE;
		num_founds = 0;

		while(!finished){

			EC_POINT_mul(E,point_to,NULL,point, iter, bn_ctx);

			if(EC_POINT_is_at_infinity(E,point_to)){
				num_founds++;
				BN_copy(M,iter);
			}

			if(num_founds > 1){
				finished = TRUE;
			}
			
			if(BN_cmp(cota_sup,iter)==0){
				finished = TRUE;
				if(num_founds == 1){
					unique = TRUE;
				}else{
					unique = FALSE;
					
				}
			}
			BN_add_word(iter,1);
		}
	}

	BN_free(a);
	BN_free(b);
	BN_free(aux);
	BN_free(p);
	BN_CTX_free(bn_ctx);
	BN_free(iter);


	return M;


	

}

BIGNUM * Schoofs_Elkies_Atkin(EC_GROUP * E){
	BIGNUM *A = BN_new();
	BIGNUM *B = BN_new();
	BIGNUM *p = BN_new();
	BIGNUM * bn_ctx = BN_CTX_new();
	BIGNUM *cardinal = BN_new();
	fmpz_t n;
	fmpz_t A_fmpz;
	fmpz_t B_fmpz;
	fmpz_t p_fmpz;

	fmpz_init(n);
	fmpz_init(A_fmpz);
	fmpz_init(B_fmpz);
	fmpz_init(p_fmpz);


	char * A_hex;
	char * B_hex;
	char * p_hex;
	char * card_str;

	bool finished = FALSE;
	bool unique = FALSE;
	int num_founds = 0;

	EC_GROUP_get_curve(E, p, A, B, bn_ctx);

	A_hex = BN_bn2hex(A);
	B_hex = BN_bn2hex(B);
	p_hex = BN_bn2hex(p);

	fmpz_set_str(p_fmpz, p_hex, 16);
	fmpz_set_str(A_fmpz, A_hex, 16);
	fmpz_set_str(B_fmpz, B_hex, 16);



	if(SEA(n, p_fmpz, A_fmpz, B_fmpz, NONE, 0) == 0){
		/*flint_printf("alles gut");
		fmpz_print(A_fmpz);
		flint_printf("\n");
		fmpz_print(B_fmpz);
		flint_printf("\n");
		fmpz_print(n);
		flint_printf("\n");*/
	}else{
		//we asing a random non-prime to the cardinal
		fmpz_set_ui(n,4);
	}

	card_str = fmpz_get_str(NULL, 16, n);
	//printf("card in str: %s\n", card_str);
	BN_hex2bn(&cardinal, card_str);

	//LOG_BN("cardinal: ", cardinal);

	return cardinal;
	
}

BIGNUM * order(BIGNUM * b, BIGNUM * p){
	BIGNUM * k = BN_new();
	BIGNUM * one = BN_new();
	BIGNUM * calc = BN_new();
	BIGNUM * bn_ctx = BN_CTX_new();

	BN_one(one);
	BN_one(k);

	while(1){
		
		BN_mod_exp(calc, b, k, p, bn_ctx);

		if(BN_cmp(calc, one)==0){
			break;
		}
		
		BN_add_word(k,1);
	}
	
	BN_free(one);
	BN_free(calc);
	BN_CTX_free(bn_ctx);

	return k;

}

bool EulerCriterion(BIGNUM * n, BIGNUM * p){
	BIGNUM * bn_ctx = BN_CTX_new();
	BIGNUM * aux = BN_new();
	BIGNUM * one = BN_new();
	BN_one(one);
	BN_mod(n,n,p,bn_ctx);
	bool found = FALSE;

	BN_copy(aux,p);
	BN_sub_word(aux,1);
	BN_div_word(aux,2);

	BN_mod_exp(aux,n,aux, p,bn_ctx);
	if(BN_cmp(one, aux)== 0){
		//LOG("There exists!");
		found = TRUE;
	}
	
	BN_free(aux);
	BN_free(one);
	BN_CTX_free(bn_ctx);

	return found;


}

EC_POINT * getRandomPoint(EC_GROUP * E){
	BIGNUM *a = BN_new();
	BIGNUM *b = BN_new();
	BIGNUM *p = BN_new();
	BIGNUM *aux = BN_new();
	BIGNUM * bn_ctx = BN_CTX_new();
	bool found = FALSE;
	BIGNUM * x = BN_new();

	EC_POINT * point = EC_POINT_new(E);

	EC_GROUP_get_curve(E, p, a, b, bn_ctx);
	
	while(!found){
		generate_random(x,p);
		EC_POINT_set_compressed_coordinates_GFp(E,point,x,0,bn_ctx);
		if(EC_POINT_is_on_curve(E,point,bn_ctx)){
			found = TRUE;
		}
	}


	return point;
}

BIGNUM * Convertx2e(BIGNUM *x, BIGNUM * e){
	BN_zero(e);
	bool divisible = TRUE;
	BIGNUM * two = BN_new();
	BIGNUM * modulus_two = BN_new();
	BIGNUM * zero = BN_new();
	BN_zero(zero);
	BN_set_word(two,2);
	BIGNUM * bn_ctx = BN_CTX_new();

	BN_mod(modulus_two,x,2, bn_ctx);

	while(BN_cmp(modulus_two, zero) == 0){
		BN_div_word(x,2);
		BN_add_word(e,1);
	}

	return x;
}

BIGNUM * Naive_Cardinal_EllipticCurveGroup(EC_GROUP * E){

	BIGNUM *a = BN_new();
	BIGNUM *b = BN_new();
	BIGNUM *p = BN_new();
	BIGNUM * bn_ctx = BN_CTX_new();
	BIGNUM * lit = BN_new();

	EC_GROUP_get_curve(E, p, a, b, bn_ctx);



	BIGNUM *it = BN_new();
	BIGNUM *aux = BN_new();
	BIGNUM *aux2 = BN_new();
	BIGNUM *three = BN_new();
	BIGNUM *calculation = BN_new();
	BIGNUM * count = BN_new();
	BN_zero(lit);

	BN_set_word(three,3);
	BN_zero(count);

	while(BN_cmp(it,p)<0){
		//LOG_BN("iteration", it);
		calculation = EvaluateElliptic(E,it);

		if(BN_cmp(lit, calculation) == 0){
			BN_add_word(count,1);
		}
		else{
			if(EulerCriterion(calculation,p)){
				BN_add_word(count,2);
			}
		}

		BN_add_word(it,1);
	}

	//the infinty pt
	BN_add_word(count, 1);
	LOG_BN_DEBUG("the number of points in the Elliptic curve is",count);
	return count;

	

}

BIGNUM * EvaluateElliptic(EC_GROUP *E, BIGNUM * x){

	BIGNUM *a = BN_new();
	BIGNUM *b = BN_new();
	BIGNUM *p = BN_new();
	BIGNUM * bn_ctx = BN_CTX_new();

	EC_GROUP_get_curve(E, p, a, b, bn_ctx);


	BIGNUM *it = BN_new();
	BIGNUM *aux = BN_new();
	BIGNUM *aux2 = BN_new();
	BIGNUM *three = BN_new();
	BIGNUM *calculation = BN_new();

	BN_set_word(three,3);

	BN_mod_exp(aux,x,three,p,bn_ctx);
	BN_mul(aux2, a, x,bn_ctx);
	BN_add(calculation, aux, aux2);
	BN_add(calculation, calculation, b);


	BN_mod(calculation,calculation,p,bn_ctx);

	BN_free(a);
	BN_free(b);
	BN_free(p);
	BN_CTX_free(bn_ctx);

	return calculation;

}

bool Embedding_Degree(BIGNUM * cardinal, BIGNUM *p, int minimum){
	BIGNUM * aux = BN_new();
	BIGNUM * mod = BN_new();
	BIGNUM * zero = BN_new();
	BN_zero(zero);
	BIGNUM * literal = BN_new();
	BIGNUM * bn_ctx = BN_CTX_new();
	for(int i = 1; i<minimum; i++){
		BN_set_word(literal,i);
		BN_exp(aux,p, literal,bn_ctx);
		BN_sub_word(aux, 1);

		BN_mod(mod,aux,cardinal, bn_ctx);
		if(BN_cmp(mod,zero)==0){
			return FALSE;
		}
	}
	return TRUE;
}

BIGNUM * SquareRoot(BIGNUM * num){
	LOG_BN_DEBUG("Calculating square root of:", num);

	bool found = FALSE;
	BIGNUM * prev = BN_new();
	BIGNUM * current = BN_new();
	BIGNUM * aux = BN_new();
	BIGNUM * aux2 = BN_new();
	BN_CTX * bn_ctx = BN_CTX_new();

	BN_copy(current,num);

	while(!found){
		//prev = current;
		BN_copy(prev, current);
		
		BN_div(aux,NULL,num,prev,bn_ctx);
		BN_add(aux, aux, prev);
		BN_div_word(aux,2);

		BN_copy(current, aux);

		if(BN_cmp(prev, current)==0){
			found = TRUE;
			LOG_BN_DEBUG("square root found", current);
		}
	}
	return current;
}

BIGNUM * SquareRootMod(BIGNUM * n, BIGNUM * p){
	BIGNUM * it = BN_new();
	BIGNUM * half_p = BN_new();
	BIGNUM * result = BN_new();
	BIGNUM * two = BN_new();
	BN_CTX * bn_ctx = BN_CTX_new();

	BN_copy(half_p, p);
	BN_set_word(two,2);
	BN_div_word(half_p,2);
	BN_zero(it);
	while(TRUE){
		if(BN_cmp(half_p,it)<0){
			break;
		}

		BN_mod_exp(result, it, two, p, bn_ctx);
		if(BN_cmp(result, n)==0){
			//found
			return it;
		}


		BN_add_word(it,1);
	}

	LOG_DEBUG("square root not found, sure it does exist?");
}

EC_POINT * f_func(EC_POINT* p, EC_GROUP * group, EC_POINT * P, EC_POINT * Q){

	BIGNUM * x = BN_new();
	BIGNUM * y = BN_new();
	BIGNUM * rem = BN_new();
	BIGNUM * lit = BN_new();
	BIGNUM * divider = BN_new();
	BN_CTX * bn_ctx = BN_CTX_new();
	

	EC_POINT_get_affine_coordinates_GFp(group,p,x,y,bn_ctx);
	
	BN_zero(lit);
	BN_set_word(divider, 3);
	BN_mod(rem,x,divider,bn_ctx);
	if(BN_cmp(rem,lit) == 0 || EC_POINT_is_at_infinity(group, p)){
		EC_POINT_add(group, p, p, P, bn_ctx);
		//LOG_POINT("inside p ", p, group);
		//printf("\n");


		BN_free(divider);
		BN_free(lit);
		BN_free(rem);
		BN_CTX_free(bn_ctx);

		return p;
	}
	BN_set_word(lit, 1);
	if(BN_cmp(rem,lit) == 0){
		EC_POINT_add(group, p, p, p, bn_ctx);
		//LOG_POINT("X_i", p,group);
		//printf("\n");
	}
	BN_set_word(lit,2);
	if(BN_cmp(rem,lit) == 0){
		EC_POINT_add(group, p, Q, p, bn_ctx);
		//LOG_POINT("X_i", p,group);
		//printf("\n");
	}


	BN_free(divider);
	BN_free(lit);
	BN_free(rem);
	BN_CTX_free(bn_ctx);

	return p;
}

BIGNUM * g_func(EC_POINT * p, BIGNUM * x, EC_GROUP * E){
	BIGNUM * rem = BN_new();
	BIGNUM * lit = BN_new();
	BN_CTX * bn_ctx = BN_CTX_new();
	BIGNUM * divider = BN_new();
	BIGNUM * px = BN_new();
	BIGNUM * py = BN_new();

	EC_POINT_get_affine_coordinates(E, p, px, py, bn_ctx);

		
	BN_zero(lit);
	BN_set_word(divider, 3);
	BN_mod(rem,px,divider,bn_ctx);

	if(EC_POINT_is_at_infinity(E, p)){
		BN_add_word(x,1);

		return x;
	}
	if(BN_cmp(rem,lit) == 0){
		BN_add_word(x,1);
	}
	BN_set_word(lit, 1);
	if(BN_cmp(rem,lit) == 0){
		BN_add(x,x,x);
	}
	BN_set_word(lit,2);
	if(BN_cmp(rem,lit) == 0){
	}


	BN_free(divider);
	BN_free(lit);
	BN_free(rem);
	BN_free(px);
	BN_free(py);
	BN_CTX_free(bn_ctx);

	return x;


}


char * generate_random_chunk(int number) {
    int i; 
    char abc[26]="abcdefghijklmnopqrstuvwxyz";
    char * output;
    output = malloc(sizeof(char)*number);

    for (i = 0; i < number; ++i) {
        output[i] = abc[rand() % (sizeof(abc) - 1)];
        //printf("%c ", output[i]);
    }
    output[number] = 0;

    return output;
}

int PollardRho(EC_GROUP * elliptic_curve, EC_POINT * P, EC_POINT * Q, BIGNUM * N){
	BIGNUM * bn_ctx = BN_CTX_new();

	BIGNUM * ECW = BN_new();


	BIGNUM * gcd = BN_new();
	BIGNUM * p = BN_new();
    BIGNUM * a = BN_new();
    BIGNUM * b = BN_new();
	EC_POINT * X_i= EC_POINT_new(elliptic_curve);
	EC_POINT * X_2i = EC_POINT_new(elliptic_curve);
	EC_POINT * p_aux = EC_POINT_new(elliptic_curve);

	BIGNUM * n = BN_new();
	BIGNUM * aux1 = BN_new();
	BIGNUM * aux2 = BN_new();
	BIGNUM * aux3 = BN_new();
	BIGNUM * solution = BN_new();

	BIGNUM * a1 = BN_new();
	BIGNUM * a2 = BN_new();
	BIGNUM * b1 = BN_new();
	BIGNUM * b2 = BN_new();


    EC_GROUP_get_curve(elliptic_curve,p,a,b,bn_ctx);
	BIGNUM * prr = EC_GROUP_get0_order(elliptic_curve);	
	//LOG_BN("cardinal!!", prr);

	int i = 1;
	bool found_cycle = FALSE;

	BIGNUM * a_i = BN_new();
	BIGNUM * b_i = BN_new();
	BIGNUM * a_2i = BN_new();
	BIGNUM * b_2i = BN_new();

	BN_zero(ECW);

	while(i<=3){

		generate_random(a_i, prr);
		generate_random(b_i, prr);
		//generate_random(b_2i, prr);
		//generate_random(a_2i, prr);
		BN_copy(a_2i,a_i);
		BN_copy(b_2i,b_i);

		/*BN_set_word(a_i,1);
		BN_set_word(b_i,0);
		BN_set_word(a_2i,1);
		BN_set_word(b_2i,2);*/


		EC_POINT_mul(elliptic_curve,X_i, NULL, P, a_i,bn_ctx);
		EC_POINT_mul(elliptic_curve,p_aux, NULL, Q, b_i,bn_ctx);
		EC_POINT_add(elliptic_curve,X_i,X_i,p_aux,bn_ctx);

		EC_POINT_mul(elliptic_curve,X_2i, NULL, P, a_2i,bn_ctx);
		EC_POINT_mul(elliptic_curve,p_aux, NULL, Q, b_2i,bn_ctx);
		EC_POINT_add(elliptic_curve,X_2i,X_2i,p_aux,bn_ctx);

		found_cycle = FALSE;
	
		while(!found_cycle){
			//single step calcs
			a_i = g_func(X_i, a_i, elliptic_curve);
			b_i = h_func(X_i, b_i, elliptic_curve);
			f_func(X_i, elliptic_curve, P,Q);
			
			//double step calcs
			aux1 = g_func(X_2i,a_2i, elliptic_curve);
			aux2 = h_func(X_2i,b_2i, elliptic_curve);
			f_func(X_2i, elliptic_curve, P,Q);

			a_2i = g_func(X_2i,aux1, elliptic_curve);
			b_2i = h_func(X_2i,aux2, elliptic_curve);
			f_func(X_2i, elliptic_curve, P,Q);

			BN_add_word(ECW, 1);

			if(EC_POINT_cmp(elliptic_curve,X_2i,X_i,bn_ctx) == 0){ //candidate found?


				BN_copy(a1,a_i);
				BN_copy(a2,a_2i);
				BN_copy(b1,b_i);
				BN_copy(b2,b_2i);

				BN_sub(aux1, b2, b1);
				BN_sub(aux3, a1, a2);

				if(BN_cmp(b_i,b_2i)!=0){
					//not valid! retry
				
					BN_gcd(gcd, aux1, p, bn_ctx);
					BN_one(aux2);
					if(BN_cmp(gcd, aux2) == 0){
						aux1 = ModNegativeNumber(prr,aux1);
						aux3 = ModNegativeNumber(prr,aux3);
						BN_mod_inverse(aux1,aux1, prr, bn_ctx);
						BN_mod_mul(solution,aux3, aux1,prr, bn_ctx);


						BN_free(aux1);
						BN_free(aux2);
						BN_free(aux3);

						///LOG_BN_dec("Number of ECW: ", ECW);

						BN_copy(N,solution);
						return 0;
					}
				}
				found_cycle = TRUE;
				i++;
			}
		}
		return 1;
	}

	BN_zero(solution);
	LOG("A solution to the ECDLP problem couldnt be found");
	return 1;


}

void generate_random(BIGNUM * rnd, BIGNUM * range){
	bool found = FALSE;
	BIGNUM * zero = BN_new();
	BN_zero(zero);

	while(!found){
		BN_rand_range(rnd,range);

		if(BN_cmp(zero, rnd) != 0){
			found = TRUE;
		}
	}
}

BIGNUM *  h_func(EC_POINT * p, BIGNUM * x, EC_GROUP * E){
	BIGNUM * rem = BN_new();
	BIGNUM * lit = BN_new();
	BN_CTX * bn_ctx = BN_CTX_new();
	BIGNUM * divider = BN_new();
	BIGNUM * px = BN_new();
	BIGNUM * py = BN_new();

	EC_POINT_get_affine_coordinates(E, p, px, py, bn_ctx);
	
	BN_zero(lit);
	BN_set_word(divider, 3);
	BN_mod(rem,px,divider,bn_ctx);
	if(EC_POINT_is_at_infinity(E, p)){
		return x;
	}
	if(BN_cmp(rem,lit) == 0 || EC_POINT_is_at_infinity(E, p)){
		
	}
	BN_set_word(lit, 1);
	if(BN_cmp(rem,lit) == 0){
		BN_add(x,x,x);
	}
	BN_set_word(lit,2);
	if(BN_cmp(rem,lit) == 0){
		BN_add_word(x,1);
	}

	BN_free(divider);
	BN_free(lit);
	BN_free(rem);
	BN_free(px);
	BN_free(py);
	BN_CTX_free(bn_ctx);

	return x;
	
}


BIGNUM * ModNegativeNumber(BIGNUM * mod, BIGNUM * num){

	BN_CTX * bn_cx = BN_CTX_new();
	BIGNUM * ret = BN_new();
	BIGNUM * lit = BN_new();
	BIGNUM * aux = BN_new();
	BIGNUM * aux2 = BN_new();

	BN_zero(lit);
	BN_sub_word(lit,1);
	

	if(BN_is_negative(num)){
		BN_mul(aux,num,lit,bn_cx);
		BN_mod(aux, aux, mod, bn_cx);

		BN_sub(ret,mod,aux);
	}else{
		BN_mod(ret,num,mod,bn_cx);
	}

	BN_CTX_free(bn_cx);
	return ret;

}