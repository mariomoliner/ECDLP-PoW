#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <openssl/sha.h>
#include <openssl/bn.h>
#include <openssl/ec.h>

typedef int bool;
#define FALSE 0
#define TRUE 1


struct POINT {
    BIGNUM * x;
    BIGNUM * y;
};


struct Elliptic_curve{
    BIGNUM* E_A;
    BIGNUM* E_B;
};

typedef struct Elliptic_curve Elliptic_curve;

typedef struct POINT POINT;

void Print_hash(const unsigned char * hash, int size);
BIGNUM * Next_prime(BIGNUM * num);
BIGNUM * SquareRoot(BIGNUM * num);
bool EulerCriterion(BIGNUM * n, BIGNUM * p);
BIGNUM * Cardinal_EllipticCurveGroup(EC_GROUP * E);
BIGNUM * Naive_Cardinal_EllipticCurveGroup(EC_GROUP * E);
BIGNUM * EvaluateElliptic(EC_GROUP * E, BIGNUM * x);
bool Embedding_Degree(BIGNUM * cardinal, BIGNUM *p, int minimum);
BIGNUM * SquareRootMod(BIGNUM * n, BIGNUM * p);
//for the is_prime implementation we will rely in the one from openSSL

void init_Elliptic_curve(Elliptic_curve * e);
void free_Elliptic_curve(Elliptic_curve * e);

void POINT_new(POINT p);
void POINT_free(POINT p);



#endif