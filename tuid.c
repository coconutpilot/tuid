#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tuid.h"
#include "dbg.h"

/*
 * Algorithm:
 * 1 Get a timestamp masked to the desired bits.
 * 2 Return tuids using this time until counter_max reached.
 * 3 When counter_max, get new timestamp as per 1.  If equal
 * or lower increment by 1.  Reset counter.
 *
 */

tuid64_t tuid64_r(tuid64_s * ctx)
{
    if (++ctx->counter_last > ctx->counter_max) {
        ctx->counter_last = 0;

        struct timespec tp;
        clock_gettime(CLOCK_REALTIME, &tp);

        tuid64_t secs = tp.tv_sec & ctx->sec_mask;
        secs <<= ctx->sec_shift;
        if (ctx->sec_last && ctx->sec_last >= secs) {
            debug("Collision incrementing %" PRIx64, ctx->minimum_increment);
            ctx->sec_last += ctx->minimum_increment;
        }
        else {
            debug("New time %" PRIx64 " Old time %" PRIx64, secs, ctx->sec_last);
            ctx->sec_last = secs;
        }

        tuid64_t nsecs = tp.tv_nsec & ctx->nsec_mask;
        nsecs <<= ctx->nsec_shift;
        ctx->nsec_last = nsecs;
    }

    tuid64_t t64 = ctx->sec_last;
    t64 |= ctx->nsec_last;

    tuid64_t counter = ctx->counter_last;
    counter <<= ctx->counter_shift;
    t64 |= counter;

    t64 |= ctx->id;

    tuid64_t rnd = xorshift64(&(ctx->random)) & ctx->random_mask;
    rnd <<= ctx->random_shift;
    t64 |= rnd;

    if (t64 <= ctx->last) {
        debug("tuid too small: %" PRIx64 ", incrementing last tuid by 1", t64);
        ++ctx->last;
        t64 = ctx->last;
    }
    else {
        ctx->last = t64;
    }

    debug("generated tuid: %" PRIx64, t64);
    return t64;
}

tuid32_t tuid32_r(tuid32_s * ctx)
{
    if (++ctx->counter_last > ctx->counter_max) {
        ctx->counter_last = 0;

        struct timespec tp;
        clock_gettime(CLOCK_REALTIME, &tp);

        tuid64_t secs = tp.tv_sec & ctx->sec_mask;
        secs <<= ctx->sec_shift;
        ctx->sec_last = secs;

        tuid64_t nsecs = tp.tv_nsec & ctx->nsec_mask;
        nsecs <<= ctx->nsec_shift;
        ctx->nsec_last = nsecs;
    }

    tuid32_t t32 = ctx->sec_last;
    t32 |= ctx->nsec_last;

    tuid32_t counter = ctx->counter_last;
    counter <<= ctx->counter_shift;
    t32 |= counter;

    t32 |= ctx->id;

    tuid32_t rnd = xorshift32(&(ctx->random)) & ctx->random_mask;
    rnd <<= ctx->random_shift;
    t32 |= rnd;

    if (t32 <= ctx->last) {
        debug("tuid too small: %" PRIx32 ", incrementing last tuid by 1", t32);
        ++ctx->last;
        t32 = ctx->last;
    }
    else {
        ctx->last = t32;
    }

    debug("generated tuid: %" PRIx32, t32);
    return t32;
}

void tuid64_reset_counter(tuid64_s * ctx)
{
    ctx->counter_last = ctx->counter_max;
}

void tuid32_reset_counter(tuid32_s * ctx)
{
    ctx->counter_last = ctx->counter_max;
}

int check_tuid64_spec(tuid64_s * ctx)
{
    return 0;    
}

int check_tuid32_spec(tuid32_s * ctx)
{
    return 0;    
}

uint64_t calculate_minimum_increment(uint64_t mask)
{
    /* there must be a simpler way */
    uint64_t mi = ((mask ^ (mask - 1)) >> 1) + 1;
    return mi;
}

/* Algorithm taken from: Xorshift RNGs - George Marsaglia
 * http://www.jstatsoft.org/v08/i14/paper
 */
tuid64_t xorshift64(uint64_t * random)
{
    *random ^= (*random<<13);
    *random ^= (*random>>7);
    *random ^= (*random<<17);

    return *random;
}

tuid32_t xorshift32(uint32_t * random)
{
    *random ^= (*random<<17);
    *random ^= (*random>>15);
    *random ^= (*random<<23);

    return *random;
}
