#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tuid.h"

int main(void)
{
    tuid64_s * ctx64 = malloc(sizeof(* ctx64));

    ctx64->sec_mask = 0x00000000FFFFFFFFLL;
    ctx64->sec_shift = 32;

    ctx64->nsec_mask = 0x00000000FF000000LL;
    ctx64->nsec_shift = 0;

    ctx64->id = 0x000000000012000000LL;

    ctx64->counter_last = ctx64->counter_max = 0xFF;
    ctx64->counter_shift = 8;

    ctx64->last = 0;
    ctx64->random = 0x5248c8561600f46d;
    ctx64->random_mask = 0xFF;
    ctx64->random_shift = 0;

    int i;
    for (i=0; i < 0x02FF; i++) {

        uint64_t tid64 = tuid64_r(ctx64);
        if (tid64 == 0) {
            printf("FATAL: no tuid\n");
            exit(1);
        }
//        printf("%d Got a tuid64: %" PRIu64 "\n", i, tid64);
//        printf("Got a tuid64: %" PRIx64 "\n", tid64);
    }

    free(ctx64);
    return 0;
}

/*
typedef struct {
    uint64_t epoch_offset;
    uint64_t sec_mask;
    uint8_t  sec_shift;
    uint64_t nsec_mask;
    uint8_t  nsec_shift;
    uint64_t id;
    uint16_t counter;
    uint16_t counter_max;
    uint8_t  counter_shift;
    tuid64_t initial;
    tuid64_t last;
} tuid64_s;
*/
