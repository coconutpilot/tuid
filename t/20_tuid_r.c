#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "tuid.h"

int main(void)
{
    tuid64_s * ctx64 = malloc(sizeof(* ctx64));
    ctx64->id = 1;
    ctx64->sec_bits = 3;

    uint64_t tid64 = tuid64_r(ctx64);
    printf("Got a tuid64: %" PRIu64 "\n", tid64);

    tuid32_s * ctx32 = malloc(sizeof(* ctx32));
    ctx32->id = 1;

    uint32_t tid32 = tuid32_r(ctx32);
    printf("Got a tuid32: %" PRIu32 "\n", tid32);
    return 0;
}
