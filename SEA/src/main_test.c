
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <flint/fmpz.h>
#include <flint/fmpz_mod_poly.h>
#include "SEA/EllipticCurvePointCounting.h"
#include "SEA/toolbox.h"
#include "SEA/params.h"

#define SECURITY_BITS 256
#define PATH_AS "./build/data/A256"
#define PATH_BS "./build/data/B256"


int
main(int _, char **v)
{

    fmpz_t p, p2, n, A, B;
    slong i;

    fmpz_init(p);
    fmpz_init(p2);
    fmpz_init(n);
    fmpz_init(A);
    fmpz_init(B);


    //fmpz_set_str(p2, "fa20779bfa20779bfa20779bfa20779bfa20779bfa20779bfa20779bfa20779bfa20779bfa20779bfa20779bfa20779bf", 16); // example with a volcano at ell = 3
    //fmpz_set_str(p2, "79bfa2079bfa20779bfa20779bf20779bfa20779bfa20779bfa20779bf207", 16);
//     fmpz_set_str(p2, "79bfa2079bfa20779bfa20779bf20779bfa2", 16);
//     fmpz_set_str(p2, "fa20779b", 16); // a very small example

//     nextPrime(p, p2);

    printf("Initialization...\n");

    SEA_init();

    fmpz_set_ui(A, 13);
    fmpz_set_ui(B, 215);
    fmpz_set_ui(p, 229);
    flint_printf("p = ");
    fmpz_print(p);
    flint_printf("\n");


    if (SEA(n, p, A, B, NONE, 0) == 0)
    {

        printf("N = ");
        fmpz_print(n);

        printf("\n");


        flint_printf("A = ");
        fmpz_print(A);
        flint_printf("\n");
        flint_printf("B = ");
        fmpz_print(B);
        flint_printf("\n");



        if (fmpz_is_probabprime(n))
        {
//             printf("\n(%d,\t%d)\t", a, b);
            fflush(stdout);
            printf("N = ");
            fmpz_print(n);

            fmpz_neg(n, n);
            fmpz_add_ui(n, n, 2);
            fmpz_add(n, n, p);
            fmpz_add(n, n, p);

            if (fmpz_is_probabprime(n))
            {
                printf("\tTwist-secure curve");
            }
            else
            {
                printf("\tPrime curve");
            }
            printf("\n");

        }

    }
    else
    {
        /* printf("bad\n"); */
    }

    printf("SEA ");
    tac(0);
    printf("\n");

   

    SEA_clear();

    fmpz_clear(p);
    fmpz_clear(p2);
    fmpz_clear(n);
    fmpz_clear(A);
    fmpz_clear(B);



    return 0;
}
