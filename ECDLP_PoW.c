#include "ECDLP_PoW.h"

//META FUNCTIONS

EPOCH_POW_INSTANCE * EpochPowInstance_new(const char * hash, int d){
    LOG(" ---  Generating EPOCH block parameters --- ");
    BIGNUM * prime = BN_new();
    EC_GROUP * E;
    EC_POINT * P;
    char * hash_P;
    EPOCH_POW_INSTANCE instance;

    prime = prime_Gen(d, hash);
    E = E_Gen(prime, hash);
    hash_P = CurveAndPrimeToHash(E);
    P = P_Gen(hash_P,sizeof(int),E);

    instance.elliptic_curve = E;
    instance.P = P;

    LOG_BN("prime field p:",prime);
    LOG_ELLIPTIC("elliptic curve: ", E);
    LOG_POINT("base point: ", P, E);

    return &instance;
}

ECDLP_POW_PROBLEM * ECDLPPowProblem_new(EPOCH_POW_INSTANCE * instance, const char * hash_prev, const char * M){
    LOG("\n ---  Generating ECDLP POW PROBLEM --- ");

    EC_POINT * Q1;
    EC_POINT * Q2 = BN_new();

    ECDLP_POW_PROBLEM problem;

    unsigned char * o1 = malloc(SHA256_DIGEST_LENGTH);
    unsigned char * o2 = malloc(SHA256_DIGEST_LENGTH);

    SHA256(hash_prev, SHA256_DIGEST_LENGTH, o1);
    SHA256(M, strlen(M), o2);

    LOG_POINT("point", instance->P,instance->elliptic_curve);

    //Q1 = P_Gen(o1,SHA256_DIGEST_LENGTH, instance->elliptic_curve);
    //Q2 = P_Gen(o2,SHA256_DIGEST_LENGTH, instance->elliptic_curve);

    LOG_POINT("point", instance->P,instance->elliptic_curve);
        
    problem.Q_2 = Q2;
    problem.Q_1 = Q1;

    problem.epoch_instance = instance;
    

      

    LOG_POINT("point", instance->P,instance->elliptic_curve);
    //problem.Q2 = Q2;    

    LOG("ECDLP problem: ");
    LOG_POINT("", Q1,instance->elliptic_curve);
    LOG_POINT("= N1*", instance->P, instance->elliptic_curve);

    LOG_POINT("", Q2, instance->elliptic_curve);
    LOG_POINT("= N2*", instance->P, instance->elliptic_curve);



    return &problem;

}

ECDLP_POW_SOLUTION * ECDLPPowSolution_new(ECDLP_POW_PROBLEM * problem){
    //pollard rho?
}


//BASIC FUNCTIONS

BIGNUM * prime_Gen(int d, const unsigned char * hash){
    LOG_DEBUG("Generating the prime base field...");
    LOG_HASH_DEBUG("Starting hash:", hash, SHA256_DIGEST_LENGTH);
    int i = 0;

    int power_to_potentiate = 2*d;
    BN_CTX * bn_ctx = BN_CTX_new();

    const char* computed_hash = malloc(sizeof(char)*(SHA256_DIGEST_LENGTH));
    memcpy(computed_hash, hash, SHA256_DIGEST_LENGTH);

    
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
    

    SHA256(computed_hash, SHA256_DIGEST_LENGTH, computed_hash);


    hash_bn = BN_bin2bn(computed_hash, SHA256_DIGEST_LENGTH, NULL);


    BN_exp(result_power, two, power, bn_ctx);
    BN_mod(result_modulo, hash_bn, result_power, bn_ctx);
    p = Next_prime(result_modulo);
    
    //we dont do checks for the prime yet...

    if(BN_cmp(p,literal)==0){
        LOG_DEBUG("prime field not found");
    }
    else{
        LOG_BN_DEBUG("prime field found", p);
    }


    BN_free(result_power);
    BN_free(two);
    BN_free(literal);
    BN_free(hash_bn);
    BN_free(power);

    return p;
}

bool ValidEllipticCurve(EC_GROUP * E){
    BIGNUM * p = BN_new();
    BIGNUM * a = BN_new();
    BIGNUM * b = BN_new();
    BN_CTX * bn_ctx = BN_CTX_new();
    EC_GROUP_get_curve(E,p,a,b,bn_ctx);

    LOG_BN_DEBUG("Checking if the elliptic curve \nE_A", a);
    LOG_BN_DEBUG("E_B", b);
    LOG_DEBUG("is valid");

    BIGNUM * cardinal = BN_new();
    cardinal = Naive_Cardinal_EllipticCurveGroup(E);
    
    if(!BN_is_prime(cardinal,128,NULL,bn_ctx,NULL)){
        LOG_DEBUG("the cardinal of the elliptic is not prime");
        return FALSE;
    }

    LOG_DEBUG("checking of p = cardinal");
    if(BN_cmp(cardinal,p)==0){
        LOG_DEBUG("the cardinal of the ellitpic curve equal p");
        return FALSE;
    }


    LOG_DEBUG("checking embeding degree");
    if(!Embedding_Degree(cardinal,p,21)){
        LOG_DEBUG("the embedding degree of the curve is smaller");
        return FALSE;
    }

    return TRUE;




}



EC_GROUP * E_Gen(BIGNUM * p, const unsigned * hash){
    LOG_DEBUG("Generating Elliptic curve for prime field: ");
    LOG_BN_DEBUG("",p);
    LOG_DEBUG("and starting hash");
    LOG_HASH_DEBUG("",hash, SHA256_DIGEST_LENGTH);

    unsigned char * hash_added = malloc(sizeof(char)*SHA256_DIGEST_LENGTH);
    BIGNUM * i = BN_new();
    BN_zero(i);

    unsigned char * A_raw = malloc(sizeof(char)*SHA256_DIGEST_LENGTH);
    unsigned char * B_raw = malloc(sizeof(char)*SHA256_DIGEST_LENGTH);

    BIGNUM *E_A = BN_new();
    BIGNUM *E_B = BN_new();
    BIGNUM *prev = BN_new();
    BN_CTX *bn_ctx = BN_CTX_new();


    EC_GROUP * E = EC_GROUP_new(EC_GFp_simple_method());

    while(TRUE){//until satisfies curve properties
        
        prev = BN_bin2bn(hash, SHA256_DIGEST_LENGTH,0);
        BN_add(prev,prev,i);
        BN_bn2bin(prev, hash_added);



        SHA256(hash_added, SHA256_DIGEST_LENGTH, A_raw);
        E_A = BN_bin2bn(A_raw, SHA256_DIGEST_LENGTH,0);
        BN_mod(E_A,E_A,p,bn_ctx);
        SHA256(A_raw, SHA256_DIGEST_LENGTH, B_raw);
        E_B = BN_bin2bn(B_raw, SHA256_DIGEST_LENGTH,0);
        BN_mod(E_B,E_B,p,bn_ctx);

        EC_GROUP_set_curve_GFp(E,p,E_A,E_B,bn_ctx);
        
        if(ValidEllipticCurve(E)){
            LOG_BN_DEBUG("Valid elliptic curve E_A: ", E_A);
            LOG_BN_DEBUG("E_B ", E_B);
            //return e;
            break;
        }

        BN_add_word(i,1);
    }

    BN_free(prev);
    BN_free(E_A);
    BN_free(E_B);
    BN_CTX_free(bn_ctx);
    free(A_raw);
    free(B_raw);
    free(hash_added);

    return E;
}

unsigned char * CurveAndPrimeToHash(EC_GROUP * E){
    BIGNUM * prime = BN_new();
    BIGNUM * a = BN_new();
    BIGNUM * b = BN_new();
    BN_CTX * bn_ctx = BN_CTX_new();
    BIGNUM * aux = BN_new();
    EC_GROUP_get_curve(E,prime,a,b,bn_ctx);

    /*unsigned char * prime_bytes =  malloc(sizeof(char)*BN_num_bytes(prime));
    unsigned char * a_bytes =  malloc(sizeof(char)*BN_num_bytes(a));
    unsigned char * b_bytes =  malloc(sizeof(char)*BN_num_bytes(b));

    BN_bn2bin(prime, prime_bytes);
    BN_bn2bin(a,a_bytes);
    BN_bn2bin(b,b_bytes);*/

    char * prime_bytes = BN_bn2dec(prime);
    char * a_bytes = BN_bn2dec(a);
    char * b_bytes = BN_bn2dec(b);



    char * result_char = calloc(1,sizeof(int));
    int result;


    int prime_int = atoi(prime_bytes);
    int a_int = atoi(a_bytes);
    int b_int = atoi(b_bytes);

    result = prime_int | a_int;
    result = b_int | result;

    BN_set_word(aux, result);
    BN_bn2bin(aux, result_char);

    free(prime_bytes);
    free(a_bytes);
    free(b_bytes);
    BN_free(prime);
    BN_free(a);
    BN_free(b);

    return result_char;

}

EC_POINT * P_Gen(const unsigned char * hash, int size, EC_GROUP * E){
    BIGNUM * p = BN_new();
    BIGNUM * a = BN_new();
    BIGNUM * b = BN_new();
    BN_CTX * bn_ctx = BN_CTX_new();
    EC_GROUP_get_curve(E,p,a,b,bn_ctx);

    int i = 0;
    BIGNUM * calculated_squared_image = BN_new();
    BIGNUM * x = BN_new();
    BIGNUM * y = BN_new();
    
    EC_POINT * point = EC_POINT_new(E);

    BN_zero(x);
    BN_bin2bn(hash, size, x);
    BN_mod(x,x,p,bn_ctx);
    
    while(TRUE){

        BN_add_word(x, i);
        calculated_squared_image = EvaluateElliptic(E,x);

        if(EulerCriterion(calculated_squared_image,p)){
            //found
            break;
        }
        i++;
    }

    int error = EC_POINT_set_compressed_coordinates(E,point,x,0,bn_ctx);

    if(error == 1){
        LOG_POINT_DEBUG("Point found", point, E);
    }else{
        LOG_DEBUG("Point not found properly");
    }

    return point;

}


