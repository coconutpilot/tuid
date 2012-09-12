#include <inttypes.h>
#include <stdio.h>
#include <time.h>
 
 
uint64_t tuid64(void)
{
    struct timespec tp;

    clock_gettime(CLOCK_REALTIME, &tp); 

    uint64_t t64 = tp.tv_sec;

    t64 <<= 32;

    t64 |= tp.tv_nsec;

    return t64;
}

uint32_t tuid32(void)
{
    struct timespec tp;

    clock_gettime(CLOCK_REALTIME, &tp); 

    uint32_t t32 = tp.tv_sec & 0xFFFF0000;

    t32 |= tp.tv_nsec & 0xFFFF;

    return t32;
}
