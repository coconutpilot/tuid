#include <inttypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tuid.h"
#include "dbg.h"

#define THREADS 8
#define ITERATIONS 100

typedef struct arg_s {
    int      tid;
    tuid64_s *ctx;
} arg_s;

void * test_tuid(void * t)
{
    arg_s *a = t;
    int i;
    long unsigned milisec = 999999999;
    for (i = 0; i < ITERATIONS; i++) {

        struct timespec req={0};
        req.tv_sec=0;
        req.tv_nsec=milisec;

        while(nanosleep(&req,&req) == -1 && errno == EINTR)
            continue;

        uint64_t t64 = tuid64_r(a->ctx);
        printf("%d: %" PRIX64 "\n", a->tid, t64);
    }

    tuid64_destroy(a->ctx);
    a->ctx = 0;
    free(a);
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t threads[THREADS];

    int t;
    for (t = 0; t < THREADS; t++) {
        log_info("Starting thread %d", t);

        tuid64_s *ctx = tuid64_create(0);

        char spec[1000];
        sprintf(spec, "N60I%d", t);
        if (! tuid64_init(ctx, spec)) {
            log_err("Error: tuid_init()");
	    exit(1);
        }

        arg_s *myarg = malloc(sizeof(* myarg));
        myarg->ctx = ctx;
        myarg->tid = t;

        int rc;
        rc = pthread_create(&threads[t], NULL, test_tuid, (void *)myarg);
        if (rc) {
            log_err("pthread_create failed: %d", rc);
            return 13;
        }
    }

    for (t = 0; t < THREADS; t++) {
        int rc;
        void * t_rc;
        rc = pthread_join(threads[t], &t_rc);
        if (rc) {
            log_err("pthread_join failed: %d", rc);
            return 13;
        }
//        log_info("thread exited with status: %d", (uint64_t)t_rc);
    }

    return 0;
}
