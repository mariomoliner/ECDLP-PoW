#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <openssl/sha.h>
#include <openssl/bn.h>
#include <openssl/ec.h>
#include <flint/fmpz.h>
#include "../SEA/src/SEA/EllipticCurvePointCounting.h"
#include "../SEA/src/SEA/toolbox.h"
#include "../SEA/src/SEA/params.h"

typedef int bool;
#define FALSE 0
#define TRUE 1




//next prime following a given one
BIGNUM * Next_prime(BIGNUM * num);

//square root for bignum's
BIGNUM * SquareRoot(BIGNUM * num);

//criterion of euler for bignum's
bool EulerCriterion(BIGNUM * n, BIGNUM * p);

//improved computation of the cardinal of the elliptic curve
BIGNUM * Cardinal_EllipticCurveGroup(EC_GROUP * E);

//computation of the cardinal of the elliptic curve
BIGNUM * Naive_Cardinal_EllipticCurveGroup(EC_GROUP * E);

BIGNUM * Schoofs_Elkies_Atkin(EC_GROUP * E);

//evaluates a x in the elliptic curve to get the smaller y
BIGNUM * EvaluateElliptic(EC_GROUP * E, BIGNUM * x);

//check if the embedding degree of the elliptic curve is bigger (true) or not (false)
bool Embedding_Degree(BIGNUM * cardinal, BIGNUM *p, int minimum);

//calculates the square root modulo some prime
BIGNUM * SquareRootMod(BIGNUM * n, BIGNUM * p);

// Generates random in a certain range
void generate_random(BIGNUM * rnd, BIGNUM * range);
// get the positive equivalent number modulo some number
BIGNUM * ModNegativeNumber(BIGNUM * mod, BIGNUM * num);
// get a random point of a elliptic curve
EC_POINT * getRandomPoint(EC_GROUP * e);

char * generate_random_chunk(int number);

// Pollard rho specific functions
int PollardRho(EC_GROUP * elliptic_curve, EC_POINT * P, EC_POINT * Q, BIGNUM * N);
EC_POINT * f_func(EC_POINT* p, EC_GROUP * group, EC_POINT * P, EC_POINT * Q);
BIGNUM *  g_func(EC_POINT * p, BIGNUM * x, EC_GROUP * E);
BIGNUM *  h_func(EC_POINT * p, BIGNUM * x, EC_GROUP * E);





#endif
