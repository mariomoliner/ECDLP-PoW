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

	m = SquareRoot(SquareRoot(p));
	LOG_BN("square square root" , m);

	BN_add_word(m,2);

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