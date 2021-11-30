#include "ECDLP_PoW.h"
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include "Utility.h"
#include <openssl/bn.h>

int main(){
    
    printf("hola\n");

    const char *original = "Rosetta cosdsdde";
    const unsigned char *s = (const unsigned char *)original;
	const unsigned char *d = SHA256(s, strlen(original), 0);
    
    /*
    PRUEBAS CON BN
    const char *original = "Rosetta code";
    const unsigned char *s = (const unsigned char *)original;
	const unsigned char *d = SHA256(s, strlen(original), 0);
    
    
    Print_hash(d, SHA256_DIGEST_LENGTH);
    printf("\n");

    BIGNUM *p = BN_bin2bn(d, 2, NULL);

    unsigned char * hexadecimal = BN_bn2hex(p);
    unsigned char * decimal = BN_bn2dec(p);

    printf("decimal: %s\n", decimal);*/

	//prime_Gen(10, d);
    //prime_Gen(30, d);
    //prime_Gen(60, d);

    BIGNUM *bn = BN_new();
    BN_set_word(bn, 12);
    Next_prime(bn);

    return 0;
}