/*
 * TUID Copyright (c) 2013 David Sparks
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tuid.h"
#include "tap/tap.h"

int main(void)
{
    plan(NO_PLAN);
    note("Testing failure conditions, expect ERRORs below");

    tuid64_s *ctx = malloc(sizeof(*ctx));
    ok(ctx != NULL, "malloc");
    
    int status;
    status = tuid64_init(ctx, "N54C8R2E12345678901234567890");
    ok(status == 0, "Epoch offset overflow");

    status = tuid64_init(ctx, "N65");
    ok(status == 0, "Nanosec overflow");

    status = tuid64_init(ctx, "C10N55");
    ok(status == 0, "Nanosec overflow");

    status = tuid64_init(ctx, "C65");
    ok(status == 0, "Counter overflow");

    status = tuid64_init(ctx, "N54C11");
    ok(status == 0, "Counter overflow");

    status = tuid64_init(ctx, "R65");
    ok(status == 0, "Random overflow");

    status = tuid64_init(ctx, "N54R11");
    ok(status == 0, "Random overflow");

    status = tuid64_init(ctx, "N54C8R2I12345678901234567890");
    ok(status == 0, "ID overflow");

    free(ctx);
    return exit_status();
}
