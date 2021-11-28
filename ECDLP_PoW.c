#include "ECDLP_PoW.h"
#include <openssl/sha.h>
#include <math.h>
#include <string.h>
#include "Utility.h"
#include <openssl/bn.h>


double prime_Gen(int d, const unsigned char * hash){
    int i = 0;
    char * two_str = "2";
    int two = 2;
    int power_to_potentiate = 2*d;
    BN_CTX * bn_ctx = BN_CTX_new();

    const unsigned char *Power_as_char = (char *)&power_to_potentiate;
    const unsigned char *two_as_char = (char *)&two;

    const unsigned char * computed_hash = hash;
    computed_hash = SHA256(computed_hash, strlen((const char*)computed_hash), 0);

    BIGNUM *two_bn = BN_bin2bn(two_as_char, strlen(two_as_char), NULL);
    BIGNUM *result_power = BN_new();
    BIGNUM *result_modulo = BN_new();
    BIGNUM *hash_bn = BN_bin2bn(computed_hash, strlen(computed_hash), NULL);
    BIGNUM *power = BN_bin2bn(Power_as_char, strlen(Power_as_char), NULL);
    //BN_dec2bn(&power, Power_as_char);
    //BN_dec2bn(&two_bn, two_str);

   

    BN_exp(result_power, two_bn, power, bn_ctx);
    BN_mod(result_modulo, hash_bn, result_power, bn_ctx);
    //BN_print_fp(stdout, result_power);
    //BN_print(stdout, two_bn);

    printf("to check if is prime and/or find the nearest:\n");
    BN_print_fp(stdout, result_modulo);
    printf("\n");

    BN_print_fp(stdout, result_power);
    printf("\n");

    BN_print_fp(stdout, hash_bn);
    printf("\n");
    
    /*
    while(i<10){
        computed_hash = SHA256(computed_hash, strlen((const char*)computed_hash), 0);

        BN_exp(result_power, two_bn, power, NULL);
        BN_print(stdout, result_power);
        i++;
    }*/
}



