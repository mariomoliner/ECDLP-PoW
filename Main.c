#include "ECDLP_PoW.h"
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include "Utility.h"
#include <openssl/bn.h>
#include "Logging.h"

int main(){
    
    LOG("Debugging mode");

    BIGNUM *prime;
    const char *original = "Rosetta cosdsdde";
    const unsigned char *s = (const unsigned char *)original;
	const unsigned char *hash = SHA256(s, strlen(original), 0);



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

    prime = prime_Gen(4, hash);
    Elliptic_curve e;
    e = E_Gen(prime,hash);

    P_Gen(hash, e, prime);

    prime = prime_Gen(8, hash);
    e = E_Gen(prime,hash);

    P_Gen(hash, e, prime);






    return 0;
}