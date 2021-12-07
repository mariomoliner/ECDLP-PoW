#include "Utility.h"
#include "Logging.h"





/*
*
* INPUT: An integer number x
* OUTPUT: The next prime following x if found, -1 otherwise
*
*/
BIGNUM * Next_prime(BIGNUM *x){
	LOG_BN("Finding next prime of number", x);
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
			LOG_BN("Prime found!", x);
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

	if(found == TRUE){
	}else{
		LOG("prime not found!");
		BN_set_word(x,-1);
	}

	return x;


}


BIGNUM * Cardinal_EllipticCurveGroup(BIGNUM *p , Elliptic_curve E){
	BIGNUM * m;
	BIGNUM *it = BN_new();

	BN_zero(it);

	m = SquareRoot(SquareRoot(p));
	LOG_BN("square square root" , m);

	BN_add_word(m,2);
	

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
			return k;
		}
		
		BN_add_word(k,1);
	}
}

bool EulerCriterion(BIGNUM * n, BIGNUM * p){
	//LOG("calculating if theres quadratic residue of");
	//LOG_BN("",n);
	//LOG_BN("over", p);

	BIGNUM * bn_ctx = BN_CTX_new();
	BIGNUM * aux = BN_new();
	BIGNUM * one = BN_new();
	BN_one(one);
	BN_mod(n,n,p,bn_ctx);

	BN_copy(aux,p);
	BN_sub_word(aux,1);
	BN_div_word(aux,2);

	BN_mod_exp(aux,n,aux, p,bn_ctx);
	if(BN_cmp(one, aux)== 0){
		//LOG("There exists!");
		return TRUE;
	}
	else{
		//LOG("Doesnt exists!");
		return FALSE;
	}


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

/*BIGNUM * ShanksTonelli(BIGNUM * n, BIGNUM * p){
	LOG("calculating the square root of")
	LOG_BN("",n);
	LOG_BN("over ", p);

	BIGNUM * aux = BN_new();
	BIGNUM * aux2 = BN_new();
	BIGNUM * aux3 = BN_new();
	BIGNUM * aux4 = BN_new();
	BIGNUM * aux5 = BN_new();
	BIGNUM * aux6 = BN_new();
	BIGNUM * bn_ctx = BN_CTX_new();

	BIGNUM * s = BN_new();
	BIGNUM * e = BN_new();
	BIGNUM * q = BN_new();

	BN_copy(aux, p);
	BN_sub_word(aux,1);
	BN_copy(aux2, aux);
	BN_div_word(aux,2);
	//aux = (p-1)/2
	//aux2 = (p-1)



	BN_mod_exp(aux, n, aux, p, bn_ctx);
	if(BN_cmp(aux,aux2)==0){
		LOG("The square root is not possible");
	}

	BN_copy(aux,aux2);
	BN_div_word(aux,2);
	//aux is back to (p-1)/2

	s = Convertx2e(aux2, e);
	BN_set_word(q,2);
	while(1){
		
		aux3 = BN_mod_exp(aux3, q, aux, p, bn_ctx);
		
		if(BN_cmp(aux3,aux2)==0){
			break;
		}
		BN_add_word(q,1);
	}

	BIGNUM * x = BN_new();
	BIGNUM * b = BN_new();
	BIGNUM * g = BN_new();
	BIGNUM * r = BN_new();

	BIGNUM * m = BN_new();

	BN_copy(aux, s);
	BN_add_word(aux,1);
	BN_div_word(aux,2);

	BN_mod_exp(x, n, aux, p, bn_ctx);
	BN_mod_exp(b, n, s, p, bn_ctx);
	BN_mod_exp(g, q, s, p, bn_ctx);


	BN_copy(r,e);
	BN_set_word(aux3,2);

	while(1){

		BN_zero(m);

		while(BN_cmp(m, r)<0){

			BN_exp(aux2,aux3,m,bn_ctx);

			if(BN_cmp(order(b,p), aux2) == 0){
				break;
			}

			BN_add_word(m,1);
		}
		BN_zero(aux2);
		if(BN_cmp(m, aux2) == 0){
			return x;
		}




	}




}*/

BIGNUM * Naive_Cardinal_EllipticCurveGroup(BIGNUM *p , Elliptic_curve E){

	BIGNUM *it = BN_new();
	BIGNUM *aux = BN_new();
	BIGNUM *aux2 = BN_new();
	BIGNUM *three = BN_new();
	BIGNUM *calculation = BN_new();
	BIGNUM * bn_ctx = BN_CTX_new();
	BIGNUM * count = BN_new();

	BN_set_word(three,3);
	BN_zero(count);

	while(BN_cmp(it,p)<0){
		//LOG_BN("iteration", it);
		calculation = EvaluateElliptic(E,it,p);


		if(EulerCriterion(calculation,p)){
			BN_add_word(count,2);
		}

		BN_add_word(it,1);
	}

	//the infinty pt
	BN_add_word(count, 1);
	LOG("the number of points in the Elliptic curve is ");
	LOG_BN("",count);
	return count;

	

}

BIGNUM * EvaluateElliptic(Elliptic_curve E, BIGNUM * x, BIGNUM * p){

	BIGNUM *it = BN_new();
	BIGNUM *aux = BN_new();
	BIGNUM *aux2 = BN_new();
	BIGNUM *three = BN_new();
	BIGNUM *calculation = BN_new();
	BIGNUM * bn_ctx = BN_CTX_new();

	BN_set_word(three,3);

	BN_mod_exp(aux,x,three,p,bn_ctx);
	BN_mul(aux2, E.E_A, x,bn_ctx);
	BN_add(calculation, aux, aux2);
	BN_add(calculation, calculation, E.E_B);


	BN_mod(calculation,calculation,p,bn_ctx);
	//we return y^2
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
/*
*
* INPUT: num to calculate square root over the integers
* OUTPUT: the integer truncated square root
*
*/
BIGNUM * SquareRoot(BIGNUM * num){
	LOG_BN("Calculating square root of:", num);

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
		LOG_BN("current ", current);

		if(BN_cmp(prev, current)==0){
			found = TRUE;
			LOG_BN("square root found", current);
		}
	}
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

	LOG("square root not found, sure it does exist?");
}


//INITIALIZIATION OF THE TYPES
void init_Elliptic_curve(Elliptic_curve * e){
    e->E_A = BN_new();
    e->E_B = BN_new();
}

void free_Elliptic_curve(Elliptic_curve * e){
    BN_free(e->E_A);
    BN_free(e->E_B);
}

void POINT_new(POINT p){
	p.x = BN_new();
	p.y = BN_new();
}

void POINT_free(POINT p){
	BN_free(p.x);
	BN_free(p.y);
}