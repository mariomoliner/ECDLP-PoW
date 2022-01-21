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

void iterative_test(int max){
    char * chunk_prev;
    char * trans_data;
    chunk_prev = generate_random_chunk(256);
    trans_data = generate_random_chunk(500);
    int d = 10;

    printf("ITERATIVE TEST FROM d = 5 UNTIL d = %d\n\n", max);
    
	unsigned char *hash;
    hash = malloc(sizeof(char)*SHA256_DIGEST_LENGTH); 
    SHA256(chunk_prev, strlen(chunk_prev), hash);

    print_hash("hash_prev: ", hash, SHA256_DIGEST_LENGTH);
    printf("tansactions data: %s\n", trans_data);
    printf("\n\n");

    int count_correct = 0;
    int total = max - 4;

    EPOCH_POW_INSTANCE instance;
    ECDLP_POW_PROBLEM problem;
    ECDLP_POW_SOLUTION solution;

    for(int i = 5; i <= max; i++){
        printf("DIFFICULTY d = %d\n\n", i);
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

    //printf("countt %d \n",count_correct);

    if(count_correct == total){
        printf(GREEN "ALL TESTS PASSED\n" RESET);
    }else{
        printf(RED "SOME TESTS FAILED\n" RESET);
    }

}


void repetitive_test(int d, int repes){
    char * chunk_prev;
    char * trans_data;
    //chunk_prev = generate_random_chunk(256);
    //trans_data = generate_random_chunk(500);
    

    printf("REPETITIVE TEST FOR d = %d, %d TIMES\n\n", d, repes);

	unsigned char *hash;
    hash = malloc(sizeof(char)*SHA256_DIGEST_LENGTH); 


    int count_correct = 0;
    int total = repes;

    EPOCH_POW_INSTANCE instance;
    ECDLP_POW_PROBLEM problem;
    ECDLP_POW_SOLUTION solution;

    for(int i =0 ; i<repes; i++){
        chunk_prev = generate_random_chunk(256);
        trans_data = generate_random_chunk(500);

        SHA256(chunk_prev, strlen(chunk_prev), hash);

        printf("DIFFICULTY d = %d\n\n", d);
        print_hash("hash_prev: ", hash, SHA256_DIGEST_LENGTH);
        printf("tansactions data: %s\n", trans_data);
        printf("\n\n");

        instance = EpochPowInstance_new(hash, d);
        problem = ECDLPPowProblem_new(&instance, hash, trans_data);
        solution = ECDLPPowSolution_new(&problem);
        if(ECDLPPowCheckSolution(&solution)){
            printf(GREEN "OK\n" RESET);
            count_correct++;
        }else{
            printf(RED "NO OK\n" RESET);
        }
    }

    if(count_correct == total){
        printf(GREEN "ALL TESTS PASSED\n" RESET);
    }else{
        printf(RED "SOME TESTS FAILED\n" RESET);
    }

}


int main(int argc, char *argv[]){

    printf("Set of tests:\n");
    srand(time(NULL));

    int i = 1;

    while(i < argc-1){
        if(strcmp(argv[i], "-i") == 0){
            int max = atoi(argv[i+1]);
            iterative_test(max);
        }
        if(strcmp(argv[i], "-d") == 0){
            int d;
            int repes;
            d = atoi(argv[i+1]);
            repes = atoi(argv[i+2]);

            repetitive_test(d,repes);
        }
        i++;
    }

    return 0;
}