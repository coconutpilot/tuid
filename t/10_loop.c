/*
 * TUID Copyright (c) 2013 David Sparks
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tuid.h"
#include "tap/tap.h"


const int TESTMAX = 100000;

int main(void)
{
    plan(NO_PLAN);

    tuid64_s *ctx = malloc(sizeof(*ctx));
    tuid64_init(ctx);
    pass("Initialized");

    uint64_t t1, t2 = 0;
    
    int i;
    
    diag("Looping %d times ...", TESTMAX);
    for (i = 0; i < TESTMAX; ++i) {
        t1 = tuid64_r(ctx); 
        /* Too many ok() overflows terminal scrollback */
        if (! t1 > t2) {
            fail("Monotonically increasing");
        }
        t2 = t1;
    }
    pass("Done");

    free(ctx);
    return exit_status();
}
