/*
 * TUID Copyright (c) 2013 David Sparks
 */

#ifndef tuid_h__
#define tuid_h__

#include <time.h>

/**
 * This struct represents a TUID context.
 *
 * Note nanoseconds abbreviated as nsec.
 */
typedef struct tuid64_s {
    uint64_t nsec_offset;       /* nsec offset from unixtime epoch */
    uint64_t nsec;              /* unixtime in nsec, adjusted by offset */
    uint64_t nsec_mask;         /* the bits of nsec to be used in the TUID */
    uint8_t  nsec_shift;        /* how far to left shift the nsec bits */
    uint64_t nsec_min_increment;/* minimum increment required if nsec mask was too coarse */
    uint64_t id;                /* static id, ie machine id */
    uint16_t counter;           /* a counter, current value */
    uint16_t counter_max;       /* when to reset the counter to 0 */
    uint8_t  counter_shift;     /* how far to left shift the counter bits */
    uint64_t random;            /* a random #, also used as seed */
    uint64_t random_mask;       /* the bits of the random # to be used */
    uint8_t  random_shift;      /* XXX: turns out this is not needed */
    uint64_t last;              /* the last TUID, used for uniqueness check */
} tuid64_s;

/**
 * tuid64_init - initialize a context to generate TUIDs
 * @ctx: pointer to pre-malloced tuid64_s struct
 *
 * TUID generation requires a context that defines the layout and tracks data
 * about previously generated TUIDs.  This function initializes that context.
 *
 * Examples:
 *      tuid64_s *ctx = malloc(sizeof(*ctx));
 *      tuid64_init(ctx);
 *
 *      tuid64_s *ctx = tuid64_init(NULL);
 */
extern int          tuid64_init(tuid64_s *ctx, const char *spec);

/**
 * If unable to malloc the context emits a warning to stderr and returns NULL.
 */
extern tuid64_s *   tuid64_create();

/**
 * tuid64_destroy - release memory allocated to the TUID context
 * @ctx: pointer to TUID context
 *
 * This function needs to be called for contexts allocated by tuid64_create.
 *
 * If ctx is NULL emits a warning to stderr and continues.
 *
 * Example:
 *      tuid64_destroy(ctx);
 */
extern void         tuid64_destroy(tuid64_s *ctx);

/**
 * tuid64_reset_counter - reset TUIDs internal counter
 * @ctx: pointer to TUID context
 *
 * Reset the counter to 0.  This is useful to synchronize a TUID to an
 * external event.
 *
 * If ctx is NULL emits a warning to stderr and continues.
 *
 * Example:
 *      tuid64_reset_counter(ctx);
 */
extern void         tuid64_reset_counter(tuid64_s *ctx);

/**
 * tuid64_r - generate a TUID
 * @ctx:  pointer to TUID context
 *
 * Generate a TUID.
 *
 * Returns 0 on error.
 *
 * Example:
 *      uint64_t mytuid = tuid64_r(my_ctx);
 */
extern uint64_t     tuid64_r(tuid64_s *ctx);

#endif
