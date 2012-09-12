#include <inttypes.h>
#include <stdio.h>
#include <time.h>
#include "tuid.h"

#define ITERATIONS 10000000

void test32(void)
{
    printf("Testing tuid32 on %d iterations\n", ITERATIONS);

    uint32_t tid1, tid2;
    int i;
    for (i = 0; i < ITERATIONS; i++) {
        tid1 = tuid32();
//        printf("Got a tuid: %" PRIX32 "\n", tid1);

        if (tid1 == tid2) {
            printf("collision: %" PRIX32 "\n", tid1);
        }
        tid2 = tid1;

    }
}

void test64(void)
{
    printf("Testing tuid64 on %d iterations\n", ITERATIONS);

    uint64_t tid1, tid2;
    int i;
    for (i = 0; i < ITERATIONS; i++) {
        tid1 = tuid64();
//        printf("Got a tuid: %" PRIX64 "\n", tid1);

        if (tid1 == tid2) {
            printf("collision: %" PRIX64 "\n", tid1);
        }
        tid2 = tid1;

    }
}

int main(void)
{
    printf("long: %d\n", sizeof(long));
    printf("uint32_t: %d\n", sizeof(uint32_t));

    struct timespec  ts1,  ts2;
    struct timespec cpu1, cpu2;
    double duration, cpu;

    clock_gettime(CLOCK_REALTIME, &ts1);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cpu1);
    test32();
    clock_gettime(CLOCK_REALTIME, &ts2);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &cpu2);

    duration  = ts2.tv_sec + ts2.tv_nsec/1E9;
    duration -= ts1.tv_sec + ts1.tv_nsec/1E9;

    cpu  = cpu2.tv_sec + cpu2.tv_nsec/1E9;
    cpu -= cpu1.tv_sec + cpu1.tv_nsec/1E9;

    printf("tuid32 real: %f cpu: %f\n", duration, cpu);

    clock_gettime(CLOCK_REALTIME, &ts1);
    test64();
    clock_gettime(CLOCK_REALTIME, &ts2);

    duration  = ts2.tv_sec + ts2.tv_nsec/1E9;
    duration -= ts1.tv_sec + ts1.tv_nsec/1E9;
    
    cpu  = cpu2.tv_sec + cpu2.tv_nsec/1E9;
    cpu -= cpu1.tv_sec + cpu1.tv_nsec/1E9;

    printf("tuid64 real: %f cpu: %f\n", duration, cpu);
    return 0;
}

