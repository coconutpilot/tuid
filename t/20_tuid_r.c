#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "tuid.h"

int main(void)
{
    s_t64 * ctx64 = malloc(sizeof(* ctx64));
    ctx64->id = 1;

    uint64_t tid64 = tuid64_r(ctx64);
    printf("Got a tuid64: %" PRIu64 "\n", tid64);

    s_t32 * ctx32 = malloc(sizeof(* ctx32));
    ctx32->id = 1;

    uint32_t tid32 = tuid32_r(ctx32);
    printf("Got a tuid32: %" PRIu32 "\n", tid32);
    return 0;
}
