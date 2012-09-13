#include <inttypes.h>
#include <pthread.h>
#include <stdio.h>
#include "tuid.h"

#define THREADS 32
#define ITERATIONS 100000

void * test_tuid(void * t)
{
    int i;
    for (i = 0; i < ITERATIONS; i++) {
        uint32_t tid32 = tuid32();
    //    printf("Thread %i got a tuid32: %" PRIu32 "\n", (int)t, tid32);
        printf("%" PRIX64 "\n", tid32);
    }

}

int main(void)
{
    pthread_t threads[THREADS];

    int t;
    for (t = 0; t < THREADS; t++) {
        printf("Starting thread %d\n", t);
        int rc;
        rc = pthread_create(&threads[t], NULL, test_tuid, (void *)t);
        if (rc) {
            printf("pthread_create failed: %d\n", rc);
            return 13;
        }
    }
    pthread_exit(NULL);
}

