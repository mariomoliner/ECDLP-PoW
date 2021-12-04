#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <openssl/sha.h>
#include <openssl/bn.h>
#include "ECDLP_PoW.h"

typedef int bool;
#define FALSE 0
#define TRUE 1

void Print_hash(const unsigned char * hash, int size);
BIGNUM * Next_prime(BIGNUM * num);
BIGNUM * SquareRoot(BIGNUM * num);
BIGNUM * Cardinal_EllipticCurveGroup(BIGNUM *p , Elliptic_curve E);
//for the is_prime implementation we will rely in the one from openSSL



#endif