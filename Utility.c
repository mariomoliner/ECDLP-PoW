#include "Utility.h"
#include <openssl/sha.h>
#include <openssl/bn.h>

void Print_hash(const unsigned char * hash, int size){
    int i;
	for (i = 0; i < size; i++)
		printf("%02x", hash[i]);
	putchar('\n');
}



BIGNUM * Next_prime(BIGNUM *num){
}