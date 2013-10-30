/*
 * TUID Copyright (c) 2013 David Sparks
 */

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tuid.h"
#include "dbg.h"

/* 1 billion nanoseconds in a second! */
static const uint64_t sec2nsec = 1000000000ULL;

/**
 * get_min_inc64 - calculate the minimum increment based on a bitmask
 * @mask: the bitmask we want the increment for
 *
 * Effectively returns the LSB in mask (except when mask == 0 it returns 1).
 */
static uint64_t get_min_inc64(uint64_t mask)
{
    uint64_t mi = ((mask ^ (mask - 1)) >> 1) + 1;
    return mi;
}

/**
 * xorshift64 - fast random number generator
 * @random: pointer to prev random value, will point at next random value
 *
 * This simple random number generator will return all 2^64(*) possibilities
 * before cycling.
 * (*) except 0.
 *
 * Algorithm taken from: Xorshift RNGs - George Marsaglia
 * http://www.jstatsoft.org/v08/i14/paper
 */
static uint64_t xorshift64(uint64_t *random)
{
    *random ^= (*random << 13);
    *random ^= (*random >> 7);
    *random ^= (*random << 17);

    return *random;
}

tuid64_s * tuid64_create()
{
    tuid64_s *ctx = malloc(sizeof(*ctx));
    check_mem(ctx);

    return ctx;
error:
    return 0;
}

int tuid64_init(tuid64_s *ctx, const char *spec)
{
    check(ctx, "Invalid tuid context");

    debug("Decoding TUID spec: %s", spec);

    while (*spec) {
        char type = *spec;
        ++spec;

        int val = 0;
        while (*spec) {
            char valc = *spec;

            val *= 10;
            val += valc - '0';
            ++spec;
        }
        debug("Key: %c Val: %d", type, val);
    }


    ctx->nsec_offset = 0;
    ctx->nsec = 0;
    ctx->nsec_mask = 0;
    ctx->nsec_shift = 0;
    ctx->nsec_min_increment = get_min_inc64(ctx->nsec_mask);

    ctx->id = 0;

    ctx->counter = 0;
    ctx->counter_max = 0;
    ctx->counter_shift = 0;
 
    ctx->random = 0x5248c8561600f46dULL;
    ctx->random_mask = 0;
    ctx->random_shift = 0;

    ctx->last = 0;

    return 1;
error:
    return 0;
}

void tuid64_destroy(tuid64_s *ctx)
{
    check(ctx, "Invalid tuid context");
    free(ctx);
    ctx = NULL;
error:
    return;
}

/*
 * Algorithm:
 * 1 Get a timestamp masked to the desired bits.
 * 2 Return tuids using this time until counter_max reached.
 * 3 When counter_max, get new timestamp as per 1.  If equal
 * or lower(ntp?) increment by min_increment.  Reset counter.
 *
 */
uint64_t tuid64_r(tuid64_s *ctx)
{
    check(ctx, "Invalid tuid context");

    if (++ctx->counter > ctx->counter_max) {
        ctx->counter = 0;

        struct timespec tp;
        clock_gettime(CLOCK_REALTIME, &tp);

        uint64_t nsec = tp.tv_sec * sec2nsec;
        nsec += tp.tv_nsec;

        nsec <<= ctx->nsec_shift;
        if (ctx->nsec && ctx->nsec >= nsec) {
            debug("Collision, incrementing by %" PRIx64, ctx->nsec_min_increment);
            ctx->nsec += ctx->nsec_min_increment;
        }
        else {
            debug("New nanoseconds: %" PRIx64 " Old nanoseconds: %" PRIx64, nsec, ctx->nsec);
            ctx->nsec = nsec;
        }
    }

    uint64_t t64 = ctx->nsec;

    uint64_t counter = ctx->counter;
    counter <<= ctx->counter_shift;
    t64 |= counter;

    t64 |= ctx->id;

    uint64_t rnd = xorshift64(&(ctx->random));
    rnd &= ctx->random_mask;
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
error:
    return 0;
}

void tuid64_reset_counter(tuid64_s *ctx)
{
    check(ctx, "Invalid tuid context");
    ctx->counter = ctx->counter_max;
error:
    return;
}

/**
 * xorshift32 - fast random number generator
 * @random: pointer to prev random value, will return next random value
 *
 * See xorshift64 for details.
 */
/* XXX: commented to silence -Wall
static uint32_t xorshift32(uint32_t *random)
{
    *random ^= (*random << 17);
    *random ^= (*random >> 15);
    *random ^= (*random << 23);

    return *random;
}
*/
