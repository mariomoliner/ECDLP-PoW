#include "ECDLP_PoW.h"
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include "Utility.h"
#include <openssl/bn.h>
#include <openssl/ec.h>
#include "Logging.h"

int main(){
    
    LOG("Debugging mode");

    BIGNUM *prime = BN_new();
    const char *original = "Rosetta cosdsdde";
    const unsigned char *s = (const unsigned char *)original;
	unsigned char *hash;

    hash = malloc(sizeof(char)*SHA256_DIGEST_LENGTH); 
    
    SHA256(s, strlen(s), hash);




    char * hash_prev = "dsdeneiu33euenwjnwddue33&/&23";
    char * M = "032smwd9343493232msd9edeendndfndfdfdf99343me9eerer93i4933i933jeje9we93i439323";


    /*BIGNUM * prueba = BN_new();
    BIGNUM * prueba2 = BN_new();
    BIGNUM * xx = BN_new();

    BN_set_word(prueba2,7);
    BN_set_word(prueba, 4);
    Elliptic_curve e;
    init_Elliptic_curve(&e);
    BN_set_word(e.E_A,21003);
    BN_set_word(e.E_B,5668);

    BN_set_word(prueba,5668);
    BN_set_word(prueba2, 28703);


    xx = EvaluateElliptic(e,prueba, prueba2);
    LOG_BN("sdsd", xx);*/

    EPOCH_POW_INSTANCE * instance = EpochPowInstance_new(hash, 2);
    ECDLP_POW_PROBLEM * problem = ECDLPPowProblem_new(instance, hash_prev,M);

    /*const BIGNUM * a = BN_new();
    const BIGNUM * b = BN_new();
    const BIGNUM * p = BN_new();
    BN_CTX * bn_ctx = BN_CTX_new();

    BN_set_word(a,1);
    BN_set_word(b, 6);
    BN_set_word(p,11);

    prime = prime_Gen(2, hash);
    EC_GROUP * E;
    EC_POINT * P;

    E = E_Gen(prime, hash);

    char * hash_P = CurveAndPrimeToHash(E);
    P_Gen(hash_P,sizeof(int),E);*/

 


    return 0;
}