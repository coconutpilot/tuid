#include <inttypes.h>
#include <pthread.h>
#include <stdio.h>
#include "tuid.h"
#include "tap/tap.h"

#define THREADS 4
#define ITERATIONS 10

void * test_tuid(void * t)
{
    int i;
    for (i = 0; i < ITERATIONS; i++) {
        tuid64_s *ctx = tuid64_init(0);
        uint64_t t64 = tuid64_r(ctx);
        printf("%" PRIX64 "\n", t64);
    }
    pthread_exit(NULL);
}

int main(void)
{
    plan(NO_PLAN);

    pthread_t threads[THREADS];

    int t;
    for (t = 0; t < THREADS; t++) {
        diag("Starting thread %d\n", t);
        int rc;
        rc = pthread_create(&threads[t], NULL, test_tuid, (void *)t);
        if (rc) {
            fail("pthread_create failed: %d\n", rc);
            return 13;
        }
    }

    for (t = 0; t < THREADS; t++) {
        int rc;
        void * t_rc;
        rc = pthread_join(threads[t], &t_rc);
        if (rc) {
            fail("pthread_join failed: %d\n", rc);
            return 13;
        }
        pass("thread exited with status: %d\n", (int)t_rc);
    }
    return 0;
}
