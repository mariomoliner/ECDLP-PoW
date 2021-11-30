#include "Utility.h"


void Print_hash(const unsigned char * hash, int size){
    int i;
	for (i = 0; i < size; i++)
		printf("%02x", hash[i]);
	putchar('\n');
}



BIGNUM * Next_prime(BIGNUM *x){
	BIGNUM *k = BN_new();
	BIGNUM *i = BN_new();
	int to_sum;
	BIGNUM *aux = BN_new();
	BIGNUM *aux2 = BN_new();
	BIGNUM *literal = BN_new();
	BIGNUM *o = BN_new();
	int a = 0;

	BN_set_word(literal, 2);
	
	BN_copy(k, x);
	BN_div_word(k,6);
	BN_copy(i, k);
	BN_mul_word(i,6);
	BN_sub(i,x,i);

	BN_print_fp(stdout,o);
	printf("\n");

	if(BN_cmp(i,literal)<0){
		to_sum = 4;
		BN_set_word(o, 1);
	}else{
		to_sum = 2;
		BN_set_word(o, 5);
	}

	BN_print_fp(stdout,o);
	printf("\n");

	BN_mul_word(k,6);
	BN_copy(x,k);
	//BN_div_word(x,6);
	BN_add(x,x,o);

	BN_print_fp(stdout,x);
	printf("\n");

	while(a <10){
		//BN_set_word(literal, 4);
		BN_add_word(x,to_sum);
		if(to_sum==4){
			to_sum=2;
		}else{
			to_sum=4;
		}

		BN_print_fp(stdout,x);
		printf("\n");

		

		a++;
	}
}
