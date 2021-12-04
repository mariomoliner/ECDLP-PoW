#include "ECDLP_PoW.h"
#include <openssl/sha.h>
#include <math.h>
#include <string.h>
#include "Utility.h"
#include "Logging.h"
#include <openssl/bn.h>


BIGNUM * prime_Gen(int d, const unsigned char * hash){
    LOG("Generating the prime base field...");
    LOG_HASH("Starting hash:", hash, strlen(hash));
    int i = 0;

    int power_to_potentiate = 2*d;
    BN_CTX * bn_ctx = BN_CTX_new();
    const char* computed_hash = hash;

    
    BIGNUM *result_power = BN_new();
    BIGNUM *result_modulo = BN_new();
    BIGNUM *hash_bn = BN_new(); 
    BIGNUM *power = BN_new(); 
    BIGNUM *two = BN_new();
    BIGNUM *p = BN_new();
    BIGNUM *literal = BN_new();
    
    
    
    BN_set_word(two, 2);
    BN_set_word(literal, -1);
    BN_set_word(power, power_to_potentiate);
    
    //BN_dec2bn(&power, Power_as_char);
    //BN_dec2bn(&two_bn, two_str);

   
    computed_hash = SHA256(computed_hash, strlen((const char*)computed_hash), 0);
    hash_bn = BN_bin2bn(computed_hash, strlen(computed_hash), NULL);

    BN_exp(result_power, two, power, bn_ctx);
    BN_mod(result_modulo, hash_bn, result_power, bn_ctx);
    p = Next_prime(result_modulo);
    
    /*
    while(i<10){
        computed_hash = SHA256(computed_hash, strlen((const char*)computed_hash), 0);

        BN_exp(result_power, two_bn, power, NULL);
        BN_print(stdout, result_power);
        i++;
    }*/

    if(BN_cmp(p,literal)==0){
        LOG("prime field not found");
    }
    else{
        LOG_BN("prime field found", p);
    }

    return p;
}



Elliptic_curve E_Gen(BIGNUM * p, const unsigned * hash){
    LOG("Generating Elliptic curve for prime field: ")
    LOG_BN("",p);
    LOG("and starting hash")
    LOG_HASH("",hash, strlen(hash));

    int i = 0;
    const unsigned * A_raw, * B_raw;
    BIGNUM *E_A = BN_new();
    BIGNUM *E_B = BN_new();

    Elliptic_curve e;
    init_Elliptic_curve(e);

    while(TRUE){//until satisfies curve properties
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

    while(TRUE){

        //h = h + 1
        BN_set_word(aux,i);
        BN_add(x_value, x_value, aux);

        BN_exp(aux, x_value, BN_set_word(literal,3),bn_ctx);
        BN_mul(aux2,x_value,E.E_A,bn_ctx);
        BN_add(aux,aux,aux2);
        BN_add(calculated_squared_image,aux,E.E_B);

         //there are two images 

        //}*/
        i++;
    }
}



//INITIALIZIATION OF THE TYPES
void init_Elliptic_curve(Elliptic_curve e){
    e.E_A = BN_new();
    e.E_B = BN_new();
}

void free_Elliptic_curve(Elliptic_curve e){
    BN_free(e.E_A);
    BN_free(e.E_B);
}