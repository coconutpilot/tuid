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
    ok(t == NULL, "Test invalid context, expected 0 got %" PRIx64, t);

/*
//    ctx->nsec_min_increment = nsec_min_increment((ctx->nsec_mask << ctx->nsec_shift));

    ctx->id        = 0x0000000012000000ULL;

    ctx->counter = ctx->counter_max = 0xF;
    ctx->counter_shift = 8;

    ctx->last = 0;

    ctx->random = 0x5248c8561600f46dULL;
    ctx->random_mask = 0xFF;
    ctx->random_shift = 4;

    int i;
    for (i=0; i < 0x02FF; i++) {

        uint64_t tid64 = tuid64_r(ctx);
        if (tid64 == 0) {
            printf("FATAL: no tuid\n");
            exit(1);
        }
//        printf("%d Got a tuid64: %" PRIu64 "\n", i, tid64);
//        printf("Got a tuid64: %" PRIx64 "\n", tid64);
    }
*/

    tuid64_end(ctx2);
    free(ctx);
    return 0;
}
