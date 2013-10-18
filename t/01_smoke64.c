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
    tuid64_s *oldptr = ctx;
    tuid64_init(ctx);
    ok(oldptr == ctx, "Context initialzed with pre-malloc");

    tuid64_s *ctx2 = tuid64_init(NULL);
    ok(ctx2 != NULL, "Context malloc-ed in tuid64_init");

    uint64_t t = tuid64_r(ctx);
    ok(t != 0, "Got a tuid");

    t = tuid64_r(0);
    ok(! t, "Test invalid context, expected 0 got %" PRIx64, t);

    tuid64_end(ctx2);
    free(ctx);
    return exit_status();
}
