#include "ECDLP_PoW.h"
#include <openssl/sha.h>
#include <math.h>
#include <string.h>
#include "Utility.h"
#include <openssl/bn.h>


BIGNUM * prime_Gen(int d, const unsigned char * hash){



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
    BIGNUM *p = BN_new();
    //BN_dec2bn(&power, Power_as_char);
    //BN_dec2bn(&two_bn, two_str);

   

    BN_exp(result_power, two_bn, power, bn_ctx);
    BN_mod(result_modulo, hash_bn, result_power, bn_ctx);
    //BN_print_fp(stdout, result_power);
    //BN_print(stdout, two_bn);

    printf("to check if is prime and/or find the nearest:\n");
    BN_print_fp(stdout, result_modulo);
    
    p = Next_prime(result_modulo);
    //DO WE HAVE TO CHECK PRIMALITY CONDITIONS?

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
    return p;
}


Elliptic_curve E_Gen(BIGNUM * p, const unsigned * hash){



    int i = 0;
    const unsigned * A_raw, * B_raw;
    BIGNUM *E_A = BN_new();
    BIGNUM *E_B = BN_new();

    Elliptic_curve e;
    init_Elliptic_curve(e);

    while(true){//until satisfies curve properties
        i++;
        A_raw = SHA256(hash, strlen((const char*)hash), 0);
        E_A = BN_bin2bn(A_raw, strlen((const char*)A_raw),0);
        B_raw = SHA256(A_raw, strlen((const char*)A_raw), 0);


        /*if(){
            
        }*/
    }
}


double P_Gen(const unsigned char * hash, Elliptic_curve E){
    int i = 0;
    BIGNUM *x_value = BN_bin2bn(hash, strlen((const char*)hash),NULL);
    BIGNUM * calculated_squared_image = BN_new();
    BIGNUM * literal = BN_new();
    BIGNUM *aux, *aux2;

    BN_CTX * bn_ctx = BN_CTX_new();

    while(true){

        //h = h + 1
        BN_set_word(aux,i);
        BN_add(x_value, x_value, aux);

        BN_exp(aux, x_value, BN_set_word(literal,3),bn_ctx);
        BN_mul(aux2,x_value,E.E_A,bn_ctx);
        BN_add(aux,aux,aux2);
        BN_add(calculated_squared_image,aux,E.E_B);

        if(BN_cmp(calculated_squared_image, BN_zero)>0){ //there are two images 
            
        }
        i++;
    }
}


void init_Elliptic_curve(Elliptic_curve e){
    e.E_A = BN_new();
    e.E_B = BN_new();
}

void free_Elliptic_curve(Elliptic_curve e){
    BN_free(e.E_A);
    BN_free(e.E_B);
}