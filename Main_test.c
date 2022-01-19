#include "ECDLP_PoW.h"
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include "Utility.h"
#include <openssl/bn.h>
#include <openssl/ec.h>
#include "Logging.h"

#include <pthread.h>
#include <flint/fmpz.h>
#include <flint/fmpz_mod_poly.h>
#include "SEA/src/SEA/EllipticCurvePointCounting.h"
#include "SEA/src/SEA/toolbox.h"
#include "SEA/src/SEA/params.h"

#define RESET   "\033[0m"
#define GREEN   "\033[32m" 
#define RED     "\033[31m"


int main(int argc, char *argv[]){

    printf("Set of tests:\n");

    srand(time(NULL));

    char * chunk_prev;
    char * trans_data;
    chunk_prev = generate_random_chunk(256);
    trans_data = generate_random_chunk(500);
    int d = 10;


	unsigned char *hash;
    hash = malloc(sizeof(char)*SHA256_DIGEST_LENGTH); 
    SHA256(chunk_prev, strlen(chunk_prev), hash);

    print_hash("hash_prev: ", hash, SHA256_DIGEST_LENGTH);
    printf("tansactions data: %s\n", trans_data);
    printf("\n\n");

    int count_correct = 0;
    int total = 11;

    EPOCH_POW_INSTANCE instance = EpochPowInstance_new(hash, d);
    ECDLP_POW_PROBLEM problem = ECDLPPowProblem_new(&instance, hash, trans_data);
    ECDLP_POW_SOLUTION solution = ECDLPPowSolution_new(&problem);

    for(int i = 5; i < 16; i++){
        instance = EpochPowInstance_new(hash, i);
        problem = ECDLPPowProblem_new(&instance, hash, trans_data);
        solution = ECDLPPowSolution_new(&problem);
        if(ECDLPPowCheckSolution(&solution)){
            printf(GREEN "OK\n" RESET);
            count_correct++;
        }else{
            printf(RED "NO OK\n" RESET);
        }
    }

    printf("countt %d \n",count_correct);

    if(count_correct == total){
        printf(GREEN "ALL TESTS PASSED\n" RESET);
    }else{
        printf(RED "SOME TESTS FAILED\n" RESET);
    }

    return 0;
}