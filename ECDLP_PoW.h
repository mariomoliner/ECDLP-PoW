#ifndef _ECDLP_POW_H_
#define _ECDLP_POW_H_

#include <openssl/sha.h>
#include <openssl/bn.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>  
#include "Utility.h"
#include "Logging.h"
#include <openssl/ec.h>

typedef int bool;
#define FALSE 0
#define TRUE 1

struct EPOCH_POW_INSTANCE {
    EC_GROUP * elliptic_curve;
    EC_POINT * P;
};

typedef struct EPOCH_POW_INSTANCE EPOCH_POW_INSTANCE;

struct ECDLP_POW_PROBLEM {
    EC_POINT * Q_1;
    EC_POINT * Q_2;
    EPOCH_POW_INSTANCE * epoch_instance; 
};

typedef struct ECDLP_POW_PROBLEM ECDLP_POW_PROBLEM;

struct ECDLP_POW_SOLUTION {
    BIGNUM * N1;
    BIGNUM * N2;
    ECDLP_POW_PROBLEM * problem;
};

typedef struct ECDLP_POW_SOLUTION ECDLP_POW_SOLUTION;


//META FUNCTIONS FOR THE ABSTRACTIONS OF THE ALGORITHM
EPOCH_POW_INSTANCE * EpochPowInstance_new(const char * hash, int d);
ECDLP_POW_PROBLEM * ECDLPPowProblem_new(EPOCH_POW_INSTANCE * instance, const char * hash_prev, const char * M);
ECDLP_POW_SOLUTION * ECDLPPowSolution_new(ECDLP_POW_PROBLEM * problem);

//BASIC FUNCTIONS OF THE POW ALGORTIHM
BIGNUM * prime_Gen(int d, const unsigned char * hash);
EC_POINT * P_Gen(const unsigned char * hash, int size , EC_GROUP * E);
EC_GROUP * E_Gen(BIGNUM * p, const unsigned * hash);
bool ValidEllipticCurve(EC_GROUP * E);
unsigned char * CurveAndPrimeToHash(EC_GROUP * E);




#endif