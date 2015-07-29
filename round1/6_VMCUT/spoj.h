#include <cassert>
#include <cstdio>
#include <cstdlib>

FILE
        *spoj_p_in,             /* problem's input */
        *spoj_p_out,    /* problem's output */
        *spoj_t_out,    /* tested program's output */
        *spoj_t_src,    /* tested program's source */
        *spoj_score,    /* score for the program, for challenge problems */
        *spoj_p_info,   /* additional info - problemsetter only */
        *spoj_u_info;   /* additional info - psetter and solution's owner */


/* must be called before using other functions or variables */
void spoj_init() {
    spoj_p_in = fopen("input.txt", "r");
    spoj_p_out = fopen("output.sol", "r");
    spoj_t_out = fopen("output.txt", "r");
    spoj_score = fopen("result.txt", "w");
}

void spoj_finalize() {
}

#define spoj_assert assert
