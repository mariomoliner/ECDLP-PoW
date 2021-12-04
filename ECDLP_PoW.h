#ifndef _ECDLP_POW_H_
#define _ECDLP_POW_H_

#include <openssl/sha.h>
#include <openssl/bn.h>


#define FALSE 0
#define TRUE 1

struct Elliptic_curve{
    BIGNUM* E_A;
    BIGNUM* E_B;
};

typedef struct Elliptic_curve Elliptic_curve;

BIGNUM * prime_Gen(int d, const unsigned char * hash);
double P_Gen(const unsigned char * hash, Elliptic_curve E);
Elliptic_curve E_Gen(BIGNUM * p, const unsigned * hash);

double prueba();

void init_Elliptic_curve(Elliptic_curve e);
void free_Elliptic_curve(Elliptic_curve e);


#endif