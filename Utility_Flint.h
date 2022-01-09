#ifndef _UTILITY_FLINT_H_
#define _UTILITY_FLINT_H_

#include <flint/fq_poly.h>
#include <flint/fmpz_mpoly.h>
#include <flint/fmpq_mpoly.h>
#include <flint/fmpz.h>
#include <flint/fq_nmod_mpoly.h>
#include <flint/fq_nmod.h>

struct division_polynomials{
    fq_nmod_mpoly_struct * polynomial;
    double n;
};

typedef struct division_polynomials division_polynomials;

struct rational_polynomial{
    fq_nmod_mpoly_t num;
    fq_nmod_mpoly_t denom;
};

typedef struct rational_polynomial rational_polynomial;

struct nP{
    fmpz_t n;
    rational_polynomial x_side;
    rational_polynomial y_side;
};

typedef struct nP nP;


void prueba();
int division_polynomial(fmpz_t l, fq_nmod_t A, fq_nmod_t B, fq_nmod_mpoly_t elliptic_poly,fq_nmod_mpoly_t ret,fq_nmod_mpoly_ctx_t ctx);


///////// Pendiente de migrar
void Schoofs(fq_nmod_t A, fq_nmod_t B, fmpz_t q, fmpz_t cardinal, fq_nmod_ctx_t nmod_ctx);

void i_p(fmpz_t i, fq_nmod_t A, fq_nmod_t B, fq_nmod_mpoly_t poly_elliptic, nP * calculated_point, fq_nmod_mpoly_ctx_t ctx, fq_nmod_ctx_t nmod_ctx);
void x_s(fq_nmod_mpoly_t elliptic_poly, rational_polynomial rational_part_y, fmpz_t q, rational_polynomial rational_part_x, fq_nmod_mpoly_t poly_l ,fq_nmod_mpoly_ctx_t ctx, fq_nmod_ctx_t nmod_ctx ,rational_polynomial * ret);
rational_polynomial simplify_sum(rational_polynomial * rat_poly1, rational_polynomial * rat_poly2, fq_nmod_mpoly_ctx_t ctx);
rational_polynomial simplify_sub(rational_polynomial * rat_poly1, rational_polynomial * rat_poly2, fq_nmod_mpoly_ctx_t ctx);
rational_polynomial simplify_division(rational_polynomial * rat_poly1, rational_polynomial * rat_poly2, char ** vars ,fq_nmod_mpoly_ctx_t ctx);
void simplify_if_possible(fq_nmod_mpoly_t poly, fq_nmod_mpoly_t poly_ret, fq_nmod_mpoly_t poly_elliptic ,char ** vars ,fq_nmod_mpoly_ctx_t ctx);
void go_to_quotient(rational_polynomial * rat_poly, rational_polynomial * quot1, rational_polynomial * quot2, fq_nmod_mpoly_ctx_t ctx);
void print_rational_func(rational_polynomial * rat_poly1, char ** variables ,fq_nmod_mpoly_ctx_t ctx);
rational_polynomial simplify_mult(rational_polynomial * rat_poly1, rational_polynomial * rat_poly2, fq_nmod_mpoly_ctx_t ctx);
void init_rational_polynomial(rational_polynomial * rac, fq_nmod_mpoly_ctx_t ctx);
void init_nP(nP * nP_var, fq_nmod_mpoly_ctx_t ctx);
////////////////////////////////////////////////////

//extra
void p_16(fmpz_t l, fmpz_t q, fmpz_t q_red, fq_nmod_t A, fq_nmod_t B, fq_nmod_mpoly_t elliptic_poly, fq_nmod_mpoly_t poly_l,division_polynomials * polinomials_division,char ** vars ,fq_nmod_mpoly_ctx_t ctx ,fq_nmod_mpoly_t * ret);
void p_17(fmpz_t l, fmpz_t q, fmpz_t q_red, fq_nmod_t A, fq_nmod_t B, fq_nmod_mpoly_t elliptic_poly, fq_nmod_mpoly_t poly_l,division_polynomials * polinomials_division,char ** vars ,fq_nmod_mpoly_ctx_t ctx ,fq_nmod_mpoly_t * ret);
void p_18(fmpz_t l, fmpz_t q, fmpz_t q_red, fq_nmod_t A, fq_nmod_t B, fq_nmod_mpoly_t elliptic_poly, fq_nmod_mpoly_t poly_l,division_polynomials * polinomials_division,char ** vars ,fq_nmod_mpoly_ctx_t ctx ,fq_nmod_mpoly_t * ret);
void p_19y(fmpz_t l, fmpz_t rho, fmpz_t q, fmpz_t q_red, fq_nmod_t A, fq_nmod_t B, fq_nmod_mpoly_t elliptic_poly, division_polynomials * polinomials_division, fq_nmod_mpoly_t alpha,  fq_nmod_mpoly_t beta, char ** vars ,fq_nmod_mpoly_ctx_t ctx ,fq_nmod_mpoly_t * ret);
void p_19x(fmpz_t l, fmpz_t rho, fmpz_t q, fmpz_t q_red, fq_nmod_t A, fq_nmod_t B, fq_nmod_mpoly_t elliptic_poly, division_polynomials * polinomials_division,fq_nmod_mpoly_t alpha,  fq_nmod_mpoly_t beta,char ** vars ,fq_nmod_mpoly_ctx_t ctx ,fq_nmod_mpoly_t * ret);
void alpha_k(fmpz_t l, fmpz_t q, fmpz_t k, fq_nmod_mpoly_t elliptic_poly, division_polynomials * polinomials_division,char ** vars ,fq_nmod_mpoly_ctx_t ctx ,fq_nmod_mpoly_t * ret);
void beta_k(fmpz_t l, fmpz_t q, fmpz_t k, fq_nmod_mpoly_t elliptic_poly, division_polynomials * polinomials_division,char ** vars ,fq_nmod_mpoly_ctx_t ctx ,fq_nmod_mpoly_t * ret);
void reduce_poly_l(fq_nmod_mpoly_t poly,fq_nmod_mpoly_t poly_l,fq_nmod_mpoly_ctx_t ctx ,fq_nmod_mpoly_t * ret);
void check_2(fmpz_t q, fq_nmod_mpoly_t elliptic_poly,char ** vars,fq_nmod_mpoly_ctx_t ctx ,fq_nmod_mpoly_t * ret);
void p_19x_prueba(fmpz_t l, fmpz_t rho, fmpz_t q, fmpz_t q_red, fq_nmod_t A, fq_nmod_t B, fq_nmod_mpoly_t elliptic_poly, division_polynomials * polinomials_division, char ** vars ,fq_nmod_mpoly_ctx_t ctx ,fq_nmod_mpoly_t * ret);
void get_final_l(int num_of, fmpz_t * primes, fmpz_t * t_l, fmpz_t hasse_bound, fmpz_t l_ret);
void poly_exp_mod(fq_nmod_mpoly_t poly, fmpz_t exp, fq_nmod_mpoly_t mod, char ** vars  ,fq_nmod_mpoly_ctx_t ctx, fq_nmod_mpoly_t ret);

void print_nmod_mpoly(fq_nmod_mpoly_t poly, char * s, char ** vars,fq_nmod_mpoly_ctx_t ctx);
division_polynomials init_division_polynomials(fmpz_t n, fq_nmod_t A, fq_nmod_t B,fq_nmod_mpoly_t elliptic_poly,fq_nmod_mpoly_t ret, fq_nmod_mpoly_ctx_t ctx);

#endif