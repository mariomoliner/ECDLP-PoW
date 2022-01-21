

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
#define LOG_simple(message)   print(message)
#define LOG_BN_dec(message, big_int, args...)   print_bn_dec(message, big_int)
#define LOG_BN_simple(message, big_int)  print_bn_simple(message, big_int)
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
   printf("%s\n", msg);
}

static inline void print(char * msg){
    printf("%s", msg);
}

static inline void print_bn(char * msg, BIGNUM * bn){
    printf("%s 0x", msg);
    BN_print_fp(stdout, bn);
    printf("\n");
}

static inline void print_bn_simple(char * msg, BIGNUM * bn){
    char * num = BN_bn2dec(bn);
    printf("%s ", msg);
    printf("%s", num);
}

static inline void print_bn_dec(char * msg, BIGNUM * bn){
    char * num = BN_bn2dec(bn);
    printf("%s ", msg);
    printf("%s", num);
    printf("\n");
}



static inline void print_hash(char  * msg,const unsigned char * hash, int size){
    int i;
    printf("%s ", msg);
	for (i = 0; i < size; i++)
		printf("%02x", hash[i]);
	putchar('\n');
}

static inline void print_point(char * msg, EC_POINT * p, EC_GROUP * E){
    BIGNUM * px = BN_new();
    BIGNUM * py = BN_new();
    BN_CTX * bn_ctx = BN_CTX_new();

    EC_POINT_get_affine_coordinates(E, p, px, py, bn_ctx);

    char * numx = BN_bn2dec(px);
    char * numy = BN_bn2dec(py);

    printf("%s(", msg);
    printf("%s",numx);
    printf(",");
    printf("%s",numy);
    printf(")");

    BN_free(px);
    BN_free(py);
    BN_CTX_free(bn_ctx);
}

static inline void print_elliptic(char * msg, EC_GROUP * e){
    BIGNUM *a = BN_new();
	BIGNUM *b = BN_new();
	BIGNUM *p = BN_new();
	BIGNUM * bn_ctx = BN_CTX_new();

	EC_GROUP_get_curve(e, p, a, b, bn_ctx);

    char * numx = BN_bn2dec(a);
    char * numy = BN_bn2dec(b);

    printf("%s:", msg);
    printf("y^2 = x^3 + ");
    printf("%s",numx);
    printf("x + ");
    printf("%s",numy);
    printf("\n");

    BN_free(a);
    BN_free(b);
    BN_free(p);
    BN_CTX_free(bn_ctx);
}

#endif