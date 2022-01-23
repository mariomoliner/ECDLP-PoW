#include "Pow.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



static inline void print_hash(char  * msg,const unsigned char * hash, int size){
    int i;
    printf("%s ", msg);
	for (i = 0; i < size; i++)
		printf("%02x", hash[i]);
	putchar('\n');
}


double  DoProofOfWork(int difficulty){
    char * date;
    char * data;
    char * nonce;
    char * block;
    int total_length;
    double num_of_hashes = 0;
    char * hash;

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    date = asctime(tm);
    data = generate_random_chunk(300);

    total_length = strlen(date) + strlen(data) + 5;

    block = malloc(sizeof(char)*total_length+1);


    while(1){
        nonce = generate_random_chunk(5);
        memcpy(block, data, strlen(data));
        memcpy(&block[300], date, strlen(date));
        memcpy(&block[300 + strlen(date)], nonce, 5);

        
        hash = SHA256(block, total_length, NULL);
        SHA256(hash, SHA256_DIGEST_LENGTH, hash);
        num_of_hashes += 2;
        //print_hash("hash", hash, SHA256_DIGEST_LENGTH);
        if(heading_zeros(hash, difficulty) == 1){
            break;
        }
        else{

        }
    }
    print_hash("hash", hash, SHA256_DIGEST_LENGTH);
    printf("found\n");

    printf("num of hashes required: %lf\n", num_of_hashes);

    return num_of_hashes;


}

//counts zeros up to 0 (a byte)! 
int countZeros(int x)
{
    unsigned y;
    int n = 8;
    y = x >> 4;
    y = x >> 4;
    if (y != 0) {
        n = n - 4;
        x = y;
    }
    y = x >> 2;
    if (y != 0) {
        n = n - 2;
        x = y;
    }
    y = x >> 1;
    if (y != 0)
        return n - 2;
    return n - x;
}
 

int heading_zeros(char * str, int n){
    int left = n;
    unsigned int current_byte;
    int num_zeros;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++){
        current_byte = str[i];
        num_zeros = countZeros(current_byte);

        left -= num_zeros;
        if(left <= 0){
            return 1;
        }
        else{
            if(num_zeros != 8){
                return 0;
            }
        }
    }
    
}






char * generate_random_chunk(int number) {
    int i; 
    char abc[26]="abcdefghijklmnopqrstuvwxyz";
    char * output;
    output = malloc(sizeof(char)*number);

    for (i = 0; i < number; ++i) {
        output[i] = abc[rand() % (sizeof(abc) - 1)];
        //printf("%c ", output[i]);
    }
    output[number] = 0;

    return output;
}

int main(int argc, char *argv[]){
    int d = 8;

    clock_t begin, end;
    double time_spent;
    double num_of_hashes;


    if(argc%2 != 1){
        printf("NOT the correct number of arguments");
    }else{
        int i = 1;
        while(i < argc-1){
            if(strcmp(argv[i], "-d") == 0){
                d = atoi(argv[i+1]);
            }
            i++;
        }
    }
    printf("d %d\n", d);
    srand(time(NULL));

    begin = clock();

    num_of_hashes = DoProofOfWork(d);

    end = clock();
    time_spent = (double)(end - begin)/CLOCKS_PER_SEC;

    printf("Time for calculating the solution of the PoW %lf seg.\n",time_spent);
    printf("num of hashes required: %lf\n", num_of_hashes);


}