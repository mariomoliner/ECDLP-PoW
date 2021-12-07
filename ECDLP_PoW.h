#ifndef _ECDLP_POW_H_
#define _ECDLP_POW_H_

#include <openssl/sha.h>
#include <openssl/bn.h>
#include <math.h>
#include <string.h>
#include "Utility.h"
#include "Logging.h"

typedef int bool;
#define FALSE 0
#define TRUE 1


BIGNUM * prime_Gen(int d, const unsigned char * hash);
POINT * P_Gen(const unsigned char * hash, Elliptic_curve E, BIGNUM *p);
Elliptic_curve E_Gen(BIGNUM * p, const unsigned * hash);
bool ValidEllipticCurve(Elliptic_curve e, BIGNUM * p);


double prueba();

void init_Elliptic_curve(Elliptic_curve * e);
void free_Elliptic_curve(Elliptic_curve * e);


#endif