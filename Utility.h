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
int PollardRho(EC_GROUP * elliptic_curve, EC_POINT * P, EC_POINT * Q, BIGNUM * N);
void generate_random(BIGNUM * rnd, BIGNUM * range);
BIGNUM * ModNegativeNumber(BIGNUM * mod, BIGNUM * num);
EC_POINT * getRandomPoint(EC_GROUP * e);
//BIGNUM * Schoofs(EC_GROUP * E);

EC_POINT * f_func(EC_POINT* p, EC_GROUP * group, EC_POINT * P, EC_POINT * Q);
BIGNUM *  g_func(EC_POINT * p, BIGNUM * x, EC_GROUP * E);
BIGNUM *  h_func(EC_POINT * p, BIGNUM * x, EC_GROUP * E);
//for the is_prime implementation we will rely in the one from openSSL




#endif