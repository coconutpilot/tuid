#ifndef tuid_h__
#define tuid_h__

#include <time.h>

typedef uint64_t tuid64_t; 
typedef uint32_t tuid32_t;

typedef struct {
    uint64_t epoch_offset;
    uint64_t sec_last;
    uint64_t sec_mask;
    uint8_t  sec_shift;
    uint64_t minimum_increment;
    uint64_t nsec_last;
    uint64_t nsec_mask;
    uint8_t  nsec_shift;
    uint64_t id;
    uint16_t counter_last;
    uint16_t counter_max;
    uint8_t  counter_shift;
    uint64_t random;
    uint64_t random_mask;
    uint8_t  random_shift;
    tuid64_t last;
} tuid64_s;

typedef struct {
    uint64_t epoch_offset;
    uint64_t sec_last;
    uint32_t sec_mask;
    uint8_t  sec_shift;
    uint64_t nsec_last;
    uint32_t nsec_mask;
    uint8_t  nsec_shift;
    uint32_t id;
    uint16_t counter_last;
    uint16_t counter_max;
    uint8_t  counter_shift;
    uint32_t random;
    uint32_t random_mask;
    uint8_t  random_shift;
    tuid32_t last;
} tuid32_s;

extern tuid64_t tuid64_r(tuid64_s *);
extern tuid32_t tuid32_r(tuid32_s *);

extern tuid64_t tuid64(void);
extern tuid32_t tuid32(void);

extern int check_tuid64_spec(tuid64_s *);
extern int check_tuid32_spec(tuid32_s *);

uint64_t calculate_minimum_increment(uint64_t);

uint64_t xorshift64(uint64_t *);
uint32_t xorshift32(uint32_t *);

#endif
