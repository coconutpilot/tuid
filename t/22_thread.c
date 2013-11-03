#include <inttypes.h>
#include <pthread.h>
#include <stdio.h>
#include "tuid.h"
#include "tap/tap.h"

#define THREADS 8
#define ITERATIONS 100

typedef struct arg_s {
    int      tid;
    FILE     *fp;
    tuid64_s *ctx;
} arg_s;

void * test_tuid(void * t)
{
    arg_s *a = t;
    int i;
    for (i = 0; i < ITERATIONS; i++) {
        uint64_t t64 = tuid64_r(a->ctx);
        fprintf(a->fp, "%" PRIX64 "\n", t64);
    }
    if (fclose(a->fp)) {
        BAIL_OUT("Error: fclose()");
    }

    tuid64_destroy(a->ctx);
    a->ctx = 0;
    free(a);
    pthread_exit(NULL);
}

int main(void)
{
    plan(NO_PLAN);

    FILE *cmd;

    /* fork and exec replacement */
    cmd = popen("mkdir tmp", "r");
    pclose(cmd);

    pthread_t threads[THREADS];

    int t;
    for (t = 0; t < THREADS; t++) {
        diag("Starting thread %d\n", t);

        tuid64_s *ctx = tuid64_create(0);

        char spec[1000];
        sprintf(spec, "N60I%d", t);
        tuid64_init(ctx, spec);

        char fn[1000];
        FILE *fp;
        sprintf(fn, "tmp/%d.txt", t);

        fp = fopen(fn, "w");
        if (! fp) {
            BAIL_OUT("fopen failed");
        }

        arg_s *myarg = malloc(sizeof(* myarg));
        myarg->ctx = ctx;
        myarg->tid = t;
        myarg->fp = fp;

        int rc;
        rc = pthread_create(&threads[t], NULL, test_tuid, (void *)myarg);
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

    cmd = popen("cd tmp; sort * | uniq -d" , "r");
    if (! cmd) {
        BAIL_OUT("Reading results failed");
    }

    char buf[1024];

    int failed = 0;

    while (fgets(buf, sizeof(buf), cmd)) {
        diag("Duplicate tuid: %s", buf);
        ++failed;
    }
    pclose(cmd);

    if (failed) {
        fail("Duplicates found");
    }
    else {
        pass();
    }

    return exit_status();
}
