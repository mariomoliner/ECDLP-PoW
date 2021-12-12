

#ifndef _LOGGING_H
#define _LOGGING_H

#include <openssl/bn.h>
#include <openssl/ec.h>
#include <stdio.h>

#define CLEAR 0x00
#define VERBOSE 0x01
#define DEBUG 0x02


#ifndef LOG_LEVEL 
#define LOG_LEVEL VERBOSE
#endif


#if LOG_LEVEL >= VERBOSE
#define LOG(message)   print_msg(message)
#define LOG_BN(message, big_int, args...)   print_bn(message, big_int)
#define LOG_HASH(message, hash, size, ...)  print_hash(message, hash, size)
#define LOG_POINT(message, POINT, CURVE,...)      print_point(message, POINT, CURVE)
#define LOG_ELLIPTIC(message, E, ...)       print_elliptic(message, E)
#else 
#define LOG(message)   
#define LOG_BN(message, big_int, args...)  
#define LOG_HASH(message, hash, size, ...) 
#define LOG_POINT(message, POINT, CURVE,...)   
#define LOG_ELLIPTIC(message, E, ...)   
#endif


#if LOG_LEVEL >= DEBUG
#define LOG_DEBUG(message)   print_msg(message)
#define LOG_BN_DEBUG(message, big_int, args...)   print_bn(message, big_int)
#define LOG_HASH_DEBUG(message, hash, size, ...)  print_hash(message, hash, size)
#define LOG_POINT_DEBUG(message, POINT, CURVE,...)      print_point(message, POINT, CURVE)
#define LOG_ELLIPTIC_DEBUG(message, E, ...)       print_elliptic(message, E)
#else
#define LOG_DEBUG(message)   
#define LOG_BN_DEBUG(message, big_int, args...)   
#define LOG_HASH_DEBUG(message, hash, size, ...)
#define LOG_POINT_DEBUG(message, POINT, CURVE,...)
#define LOG_ELLIPTIC_DEBUG(message, E, ...)

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

static inline void print_point(char * msg, EC_POINT * p, EC_GROUP * E){
    BIGNUM * px = BN_new();
    BIGNUM * py = BN_new();
    BN_CTX * bn_ctx = BN_CTX_new();

    EC_POINT_get_affine_coordinates(E, p, px, py, bn_ctx);

    printf("%s (", msg);
    BN_print_fp(stdout, px);
    printf(",");
    BN_print_fp(stdout, py);
    printf(")");
}

static inline void print_elliptic(char * msg, Elliptic_curve * e){
    BIGNUM *a = BN_new();
	BIGNUM *b = BN_new();
	BIGNUM *p = BN_new();
	BIGNUM * bn_ctx = BN_CTX_new();

	EC_GROUP_get_curve(e, p, a, b, bn_ctx);

    printf("LOG | %s:", msg);
    printf(" y^2 = x^3 + ");
    BN_print_fp(stdout, a);
    printf("x + ");
    BN_print_fp(stdout, b);
    printf("\n");

    BN_free(a);
    BN_free(b);
    BN_free(p);
    BN_CTX_free(bn_ctx);
}

#endif