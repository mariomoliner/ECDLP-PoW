#ifndef _POW_H_
#define _POW_H_

#include <openssl/sha.h>
#include <time.h>



char * generate_random_chunk(int number);
double  DoProofOfWork(int difficulty);
static inline void print_hash(char  * msg,const unsigned char * hash, int size);
int countZeros(int x);


#endif
