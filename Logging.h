

#ifndef _LOGGING_H
#define _LOGGING_H

#include <openssl/bn.h>
#include <stdio.h>


#define VERBOSE 0x00
#define ERROR 0x01
#define CLEAR 0x02

#ifndef LOG_LEVEL 
#define LOG_LEVEL VERBOSE
#endif


#if LOG_LEVEL == VERBOSE
#define LOG(message)   print_msg(message)
#define LOG_BN(message, big_int, args...)   print_bn(message, big_int)
#define LOG_HASH(message, hash, size, ...)  print_hash(message, hash, size)
#else
#define LOG(message, args...)   
#endif


#if LOG_LEVEL == CLEAR
#define LOG(message)   
#define LOG_BN(message, big_int, args...)  
#define LOG_HASH(message, hash, size, ...)  
#else
#define LOG(message, args...)   
#endif


static inline void print_msg(char * msg){
   printf("LOG | %s\n", msg);
}

static inline void print_bn(char * msg, BIGNUM * bn){
    printf("LOG | %s ", msg);
    BN_print_fp(stdout, bn);
    printf("\n");
}

static inline void print_hash(char  * msg,const unsigned char * hash, int size){
    int i;
    printf("LOG | %s ", msg);
	for (i = 0; i < size; i++)
		printf("%02x", hash[i]);
	putchar('\n');
}

#endif