#include "ECDLP_PoW.h"

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

bool ValidEllipticCurve(Elliptic_curve e, BIGNUM * p){
    LOG_BN("Checking if the elliptic curve \nE_A", e.E_A);
    LOG_BN("E_B", e.E_B);
    LOG("is valid");
    BIGNUM * cardinal = Naive_Cardinal_EllipticCurveGroup(p, e);
    BN_CTX * bn_ctx = BN_CTX_new();

    LOG("checking primality of the elliptic curve");
    if(!BN_is_prime(cardinal,128,NULL,bn_ctx,NULL)){
        LOG("the cardinal of the elliptic is not prime");
        return FALSE;
    }

    LOG("checking of p = cardinal");
    if(BN_cmp(cardinal,p)==0){
        LOG("the cardinal of the ellitpic curve equal p");
        return FALSE;
    }


    LOG("checking embeding degree");
    if(!Embedding_Degree(cardinal,p,21)){
        LOG("the embedding degree of the curve is smaller");
        return FALSE;
    }

    return TRUE;




}



Elliptic_curve E_Gen(BIGNUM * p, const unsigned * hash){
    LOG("Generating Elliptic curve for prime field: ");
    LOG_BN("",p);
    LOG("and starting hash");

    LOG_HASH("",hash, strlen(hash));

    const unsigned * hash_added;
    BIGNUM * i = BN_new();
    BN_zero(i);

    const unsigned * A_raw, * B_raw;
    BIGNUM *E_A = BN_new();
    BIGNUM *E_B = BN_new();
    BIGNUM *prev = BN_new();
    BN_CTX *bn_ctx = BN_CTX_new();

    Elliptic_curve e;
    init_Elliptic_curve(&e);

    while(TRUE){//until satisfies curve properties
        
        prev = BN_bin2bn(hash, strlen(hash),0);

        BN_add(prev,prev,i);

        BN_bn2bin(prev, hash_added);



        A_raw = SHA256(hash_added, strlen((const char*)hash_added), 0);
        E_A = BN_bin2bn(A_raw, strlen((const char*)A_raw),0);
        BN_mod(E_A,E_A,p,bn_ctx);
        B_raw = SHA256(A_raw, strlen((const char*)A_raw), 0);
        E_B = BN_bin2bn(B_raw, strlen((const char*)B_raw),0);
        BN_mod(E_B,E_B,p,bn_ctx);

        e.E_A = E_A;
        e.E_B = E_B;

        
        if(ValidEllipticCurve(e,p)){
            LOG_BN("Valid elliptic curve E_A: ", e.E_A);
            LOG_BN("E_B ", e.E_B);
            return e;
        }

        BN_add_word(i,1);

        /*if(){
            
        }*/
    }
}


POINT * P_Gen(const unsigned char * hash, Elliptic_curve E, BIGNUM * p){
    int i = 0;
    BIGNUM * calculated_squared_image = BN_new();
    BN_CTX * bn_ctx = BN_CTX_new();
    BIGNUM * x = BN_new();
    BIGNUM * y = BN_new();
    
    POINT point;
    POINT_new(point);
    BN_zero(x);
    BN_bin2bn(hash, strlen(hash), x);
    BN_mod(x,x,p,bn_ctx);
    


    LOG_BN("x value", x);
    while(TRUE){

        BN_add_word(x, i);


        calculated_squared_image = EvaluateElliptic(E,x,p);
        LOG_BN("image ", calculated_squared_image);


        if(EulerCriterion(calculated_squared_image,p)){
            //found
            break;
        }

        i++;
    }

    y = SquareRootMod(calculated_squared_image, p);

    point.x = x;
    point.y = y;

    

    //final_result[0] = BN_new();
    //final_result[1] = BN_new();

    LOG_BN("Point found in: (", point.x);
    LOG_BN(",",point.y);
    LOG(")");

    return &point;


}


