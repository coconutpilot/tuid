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

    tuid64_s *ctx = malloc(sizeof(*ctx));
    ok(ctx != NULL, "malloc");
    
    int status = tuid64_init(ctx);
    ok(status, "Context initialzed");

    tuid64_s *ctx2 = tuid64_create(NULL);
    ok(ctx2 != NULL, "Context malloc-ed in tuid64_create");

    uint64_t t = tuid64_r(ctx);
    ok(t, "Got a tuid");

    t = tuid64_r(0);
    ok(! t, "Test invalid context, expected 0 got %" PRIx64, t);

    tuid64_destroy(ctx2);
    free(ctx);
    return exit_status();
}
