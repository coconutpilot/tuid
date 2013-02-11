#ifndef tuid_h__
#define tuid_h__

extern uint64_t tuid64(void);
extern uint32_t tuid32(void);

typedef struct {
    uint64_t epoch_offset;
    int T_bits;
    int t_bits;
    int id;
    int c_bits;
    int r_bits;
} s_t64;

typedef struct {
    int id;
    int T_bits;
    int t_bits;
    int r_bits;
} s_t32;


extern uint64_t tuid64_r(void *);
extern uint32_t tuid32_r(void *);

#endif
