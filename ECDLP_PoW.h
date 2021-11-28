#ifndef _ECDLP_POW_H_
#define _ECDLP_POW_H_

struct Elliptic_curve{
    int E_A;
    int E_B;
};

typedef struct Elliptic_curve Elliptic_curve;

double prime_Gen(int d, const unsigned char * hash);
double P_Gen(int hash, Elliptic_curve E);
double E_Gen(int p, int hash);

double prueba();


#endif