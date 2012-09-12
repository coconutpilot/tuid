#include <inttypes.h>
#include <stdio.h>
#include "tuid.h"
 
int main(void)
{
    uint64_t tid64 = tuid64();
    printf("Got a tuid64: %" PRIu64 "\n", tid64);

    uint32_t tid32 = tuid32();
    printf("Got a tuid32: %" PRIu32 "\n", tid32);
    return 0;
}
