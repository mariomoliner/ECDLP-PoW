#include "ECDLP_POW/ECDLP_PoW.h"
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include "ECDLP_POW/Utility.h"
#include <openssl/bn.h>
#include <openssl/ec.h>
#include "ECDLP_POW/Logging.h"

#include <pthread.h>
#include <flint/fmpz.h>
#include <flint/fmpz_mod_poly.h>
#include "SEA/src/SEA/EllipticCurvePointCounting.h"
#include "SEA/src/SEA/toolbox.h"
#include "SEA/src/SEA/params.h"


int main(int argc, char *argv[]){

    //check_sea();
    
    const char *string_received = "Rosetta cosdsdde";
    int d = 16;
    if(argc%2 != 1){
        LOG("NOT the correct number of arguments");
    }else{
        int i = 1;
        while(i < argc-1){
            LOG(argv[i]);
            if(strcmp(argv[i], "-d") == 0){
                d = atoi(argv[i+1]);
            }
            if(strcmp(argv[i], "-h") == 0){
                string_received = argv[i+1];
            }
            i += 2;
        }
    }

    srand(time(NULL));

    char * hash_prev;
    char * trans_data;
    hash_prev = generate_random_chunk(256);
    trans_data = generate_random_chunk(500);


    BIGNUM *prime = BN_new();
    const unsigned char *s = (const unsigned char *)string_received;
	unsigned char *hash;

    hash = malloc(sizeof(char)*SHA256_DIGEST_LENGTH); 
    
    SHA256(s, strlen(s), hash);




    //char * hash_prev = "dsdeneiu33euenwjnwddue33&/&23";
    //char * M = "032smwd9343493232msd9edeendndfndfdfdf99343me9eerer93i4933i933jeje9we93i439323";


    EPOCH_POW_INSTANCE instance = EpochPowInstance_new(hash_prev, d);
    ECDLP_POW_PROBLEM problem = ECDLPPowProblem_new(&instance, hash_prev, trans_data);
    ECDLP_POW_SOLUTION solution = ECDLPPowSolution_new(&problem);
  

    return 0;
}
