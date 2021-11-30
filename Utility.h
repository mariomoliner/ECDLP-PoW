#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <openssl/sha.h>
#include <openssl/bn.h>

void Print_hash(const unsigned char * hash, int size);
BIGNUM * Next_prime(BIGNUM * num);
//The is_prime implementation we will rely in the one from openSSL



#endif