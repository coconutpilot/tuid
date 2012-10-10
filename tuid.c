#include <inttypes.h>
#include <stdio.h>
#include <time.h>
#include "tuid.h"


uint64_t tuid64(void)
{
    static uint64_t last = 0;
    struct timespec tp;

    clock_gettime(CLOCK_REALTIME, &tp);

    uint64_t t64 = tp.tv_sec;

    t64 <<= 32;

    t64 |= tp.tv_nsec;

    if (t64 <= last) {
        ++last;
#ifdef WARNINGS
        fprintf(stderr, "tuid64() collision at time: %" PRIu64 ", forced tuid64 to:  %" PRIu64 "\n", t64, last);
#endif
        t64 = last;
    }
    else {
        last = t64;
    }

    return t64;
}

uint64_t tuid64_r(void * ctx)
{
    struct timespec tp;

    clock_gettime(CLOCK_REALTIME, &tp);

    uint64_t t64 = tp.tv_sec;

    t64 <<= 32;

    t64 |= tp.tv_nsec & 0xFF00;

    t64 |= (((s_t64 *)ctx)->id);

    return t64;
}

uint32_t tuid32(void)
{
    static uint32_t last = 0;
    struct timespec tp;

    clock_gettime(CLOCK_REALTIME, &tp);

    uint32_t t32 = tp.tv_sec & 0xFFFFFFFF;

    if (t32 <= last) {
        ++last;
#ifdef WARNINGS
        fprintf(stderr, "tuid32() collision at time: %d, forced tuid32 to: %d\n", t32, last);
#endif
        t32 = last;
    }
    else {
        last = t32;
    }

    return t32;
}

uint32_t tuid32_r(void * ctx)
{
    struct timespec tp;

    clock_gettime(CLOCK_REALTIME, &tp);

    uint32_t t32 = tp.tv_sec & 0xFFFFFFF0;

    t32 |= (((s_t32 *)ctx)->id);

    return t32;
}
