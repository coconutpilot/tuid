#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tuid.h"

int main(void)
{
    tuid32_s * ctx32 = malloc(sizeof(* ctx32));

    ctx32->sec_mask = 0x00000000FFFF0000LL;
    ctx32->sec_shift = 0;

    ctx32->nsec_mask = 0x0000000000000000LL;
    ctx32->nsec_shift = 0;

    ctx32->id = 0x0000000b;

    ctx32->counter_last = ctx32->counter_max = 0xa;
    ctx32->counter_shift = 0;

    ctx32->last = 0;
    ctx32->random = 0x5240f46d;
    ctx32->random_mask = 0x7;
    ctx32->random_shift = 0;

    int i;
    for (i=0; i < 0x02FF; i++) {

        uint32_t tid32 = tuid32_r(ctx32);
        if (tid32 == 0) {
            printf("FATAL: no tuid\n");
            exit(1);
        }
//        printf("%d Got a tuid32: %" PRIu32 "\n", i, tid32);
//        printf("Got a tuid32: %" PRIx32 "\n", tid32);
    }

    free(ctx32);
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
