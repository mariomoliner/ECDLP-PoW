#include "ECDLP_PoW.h"
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include "Utility.h"
#include <openssl/bn.h>
#include <openssl/ec.h>
#include "Logging.h"
#include "Utility_Flint.h"


void slice(const char *str, char *result, size_t start, size_t end)
{
    strncpy(result, str + start, end - start);
}

int main(int argc, char *argv[]){
    
    /*const char *string_received = "Rosetta cosdsdde";
    int d = 7;
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

    BIGNUM *prime = BN_new();
    const unsigned char *s = (const unsigned char *)string_received;
	unsigned char *hash;

    hash = malloc(sizeof(char)*SHA256_DIGEST_LENGTH); 
    
    SHA256(s, strlen(s), hash);




    char * hash_prev = "dsdeneiu33euenwjnwddue33&/&23";
    char * M = "032smwd9343493232msd9edeendndfndfdfdf99343me9eerer93i4933i933jeje9we93i439323";*/


    //EPOCH_POW_INSTANCE instance = EpochPowInstance_new(hash, d);

    //ECDLP_POW_PROBLEM problem = ECDLPPowProblem_new(&instance, hash_prev,M);

    //ECDLP_POW_SOLUTION solution = ECDLPPowSolution_new(&problem);
    
    
    /*fmpz_t l;
    fmpz_mpoly_t polynomial;
    fmpz_mpoly_ctx_t ctx;

    fmpz_mpoly_ctx_init(ctx, 4, ORD_DEGLEX);
    fmpz_init_set_ui(l, 6);
    fmpz_mpoly_init(polynomial, ctx);

    division_polynomial(l, polynomial);

    char ** variables; 

    variables = (char **)malloc(4*sizeof(char * ));
    variables[0] = "x";
    variables[1] = "y";
    variables[2] = "A";
    variables[3] = "B";

    flint_printf("f: ");
	fmpz_mpoly_print_pretty(polynomial, variables, ctx);
	flint_printf("\n");*/

    /*fmpz_mpoly_ctx_t ctx_B;
    fmpz_mpoly_ctx_t ctx_A;
    
    fmpz_mpoly_ctx_t ctx_BB;
    fmpz_mpoly_t poly1;
    fmpz_mpoly_t poly2;

    fmpz_mpoly_t polyq;
    fmpz_mpoly_t polyr;

    char ** variables = (char **)malloc(4*sizeof(char * ));
    variables[0] = "x";

    char ** variables2 = (char **)malloc(4*sizeof(char * ));
    variables2[0] = "z";



    fmpz_mpoly_ctx_init(ctx_B, 1 , ORD_DEGLEX);


    fmpz_mpoly_ctx_init(ctx_A, 2 , ORD_DEGLEX);

    fmpz_mpoly_init(poly1, ctx_B);
    fmpz_mpoly_init(polyq, ctx_B);

    fmpz_mpoly_set_str_pretty(poly1, "x + 2*x", variables, ctx_B);

    fmpz_poly_t new_subst[2];

    fmpz_mpoly_struct * new_subs;
    new_subs = malloc(sizeof(fmpz_mpoly_struct)*1);



    fmpz_mpoly_init(&new_subs[0], ctx_B);
    fmpz_mpoly_set_str_pretty(&new_subs[0], "2*z", variables2, ctx_BB);


    flint_printf("f: ");
	fmpz_mpoly_print_pretty(&new_subs[0], variables2, ctx_BB);
	flint_printf("\n");




    int err = fmpz_mpoly_compose_fmpz_mpoly(polyq, poly1, new_subs, ctx_B, ctx_BB);
    printf("err %d\n", err);

    flint_printf("f: ");
	fmpz_mpoly_print_pretty(polyq, variables2, ctx_BB);
	flint_printf("\n");
    */

    /*fmpz_mpoly_ctx_t ctx;
    fmpz_mpoly_ctx_init(ctx, 2 , ORD_DEGLEX);

    char ** variables = (char **)malloc(2*sizeof(char * ));
    variables[0] = "x";
    variables[1] = "y";



    rational_polynomial r1,r2, ret;
    init_rational_polynomial(&r1, ctx);
    init_rational_polynomial(&r2, ctx);

    fmpz_mpoly_set_str_pretty(r1.num, "x^2 + y", variables, ctx);
    fmpz_mpoly_set_str_pretty(r1.denom, "x", variables, ctx);

    fmpz_mpoly_set_str_pretty(r2.num, "x", variables, ctx);
    fmpz_mpoly_set_str_pretty(r2.denom, "y", variables, ctx);

    ret = simplify_division(&r1, &r2, ctx);

    flint_printf("f: ");
	fmpz_mpoly_print_pretty(ret.num, variables, ctx);
	flint_printf("\n");

    flint_printf("f: ");
	fmpz_mpoly_print_pretty(ret.denom, variables, ctx);
	flint_printf("\n");*/


    /*char ** variables = (char **)malloc(2*sizeof(char * ));
    variables[0] = "x";
    variables[1] = "y";

    char ** variables2 = (char **)malloc(2*sizeof(char * ));
    variables2[0] = "x";
    variables2[1] = "z";


 
    fq_nmod_mpoly_t nmod_poly;
    fq_nmod_mpoly_t nmod_poly2;
    fq_nmod_mpoly_ctx_t ctx;
    fq_nmod_ctx_t nmod_ctx;
    fq_nmod_poly_struct * new_vars;
    new_vars = malloc(sizeof(new_vars)*2);


    fmpz_t q;
    fmpz_init(q);
    fmpz_set_ui(q, 5);
    fq_nmod_ctx_init(nmod_ctx, q, 1, "x");
    fq_nmod_mpoly_ctx_init(ctx, 1, ORD_LEX, nmod_ctx);
    fq_nmod_mpoly_init(nmod_poly, ctx);
    fq_nmod_mpoly_init(nmod_poly2, ctx);

    fq_nmod_poly_init(&new_vars[0],ctx);
    fq_nmod_poly_init(&new_vars[1], ctx);
    
    fq_nmod_poly_set_str_pretty(&new_vars[0], "x", variables2, ctx);
    fq_nmod_poly_set_str_pretty(&new_vars[1], "y", variables2, ctx);
    fq_nmod_poly_se


    fq_nmod_mpoly_set_str_pretty(nmod_poly, "x", variables, ctx);
    fq_nmod_mpoly_compose_fq_nmod_poly(nmod_poly2, nmod_poly, new_vars ,ctx);   

    fq_nmod_mpoly_print_pretty(nmod_poly, variables2, ctx);

    printf("\n");*/

    fmpz_t q; 
    fmpz_t cardinal; 
    fq_nmod_t A;
    fq_nmod_t B;
    fq_nmod_ctx_t nmod_ctx;
        
    
    fmpz_init_set_ui(q, 229);
    fq_nmod_ctx_init(nmod_ctx, q, 1, "-");
    fmpz_init(cardinal);

    fq_nmod_init(A, nmod_ctx);
    fq_nmod_init(B, nmod_ctx);

    fq_nmod_set_ui(A, 13, nmod_ctx);
    fq_nmod_set_ui(B, 215, nmod_ctx);



    Schoofs(A,B,q, cardinal, nmod_ctx);

    fmpz_print(cardinal);
    flint_printf("\n");

    return 0;
}