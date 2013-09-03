#ifndef tuid_h__
#define tuid_h__

#include <time.h>

typedef uint64_t tuid64_t; 
typedef uint32_t tuid32_t;

// ssssssnnnniiccrr
typedef struct {
    uint64_t epoch_offset;
    uint8_t sec_bits;
    uint8_t nsec_bits;
    uint32_t id;
    uint8_t c_bits;
    uint8_t r_bits;
    tuid64_t initial;
    tuid64_t last;
} tuid64_s;

typedef struct {
    uint64_t epoch_offset;
    uint8_t sec_bits;
    uint8_t nsec_bits;
    uint32_t id;
    uint8_t c_bits;
    uint8_t r_bits;
    tuid32_t initial;
    tuid32_t last;
} tuid32_s;

extern tuid64_t tuid64(void);
extern tuid64_t tuid64_r(void *);
extern tuid32_t tuid32(void);
extern tuid32_t tuid32_r(void *);
extern int check_tuid64_spec(tuid64_s *);
extern int check_tuid32_spec(tuid32_s *);

#endif
