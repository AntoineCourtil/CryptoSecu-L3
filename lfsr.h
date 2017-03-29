#ifndef LFSR_H
#define LFSR_H

#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

struct E0_state
{
	// 25 bits LFSR1 + 39 bits LFSR4 = 64 bits
	uint64_t lfsr_1_4;

	// 31 bits LFSR2 + 33 bits LFSR3 = 64 bits
	uint64_t lfsr_2_3;

	// memoire fsm
	uint8_t memoire_fsm;
};

typedef struct E0_state E0;

#define get_bit(reg, no) ( ( (uint64_t)reg & (1 << ((uint64_t)no)) ) >> ((uint64_t)no) )
#define get_xor_lfsr_1(reg) ( get_bit((uint64_t)reg, 24) ^ get_bit((uint64_t)reg, 19) ^ get_bit((uint64_t)reg, 11) ^ get_bit((uint64_t)reg, 7) )
#define get_xor_lfsr_2(reg) ( get_bit((uint64_t)reg, 30) ^ get_bit((uint64_t)reg, 23) ^ get_bit((uint64_t)reg, 15) ^ get_bit((uint64_t)reg, 11) )
#define get_xor_lfsr_3(reg) ( get_bit((uint64_t)reg, 32+31) ^ get_bit((uint64_t)reg, 27+31) ^ get_bit((uint64_t)reg, 23+31) ^ get_bit((uint64_t)reg, 11+31) )
#define get_xor_lfsr_4(reg) ( get_bit((uint64_t)reg, 38+25) ^ get_bit((uint64_t)reg, 35+25) ^ get_bit((uint64_t)reg, 27+25) ^ get_bit((uint64_t)reg, 3+25) )


#define set_bit(r, no, val) ( r = (r &  ~(1 << (uint64_t)no)) | ((uint64_t)val << (uint64_t)no))
#define set_0_lfsr_1(reg) ( set_bit((uint64_t)reg, 0, 0) )
#define set_0_lfsr_2(reg) ( set_bit((uint64_t)reg, 0, 0) )
#define set_0_lfsr_3(reg) ( set_bit((uint64_t)reg, 31, 0) )
#define set_0_lfsr_4(reg) ( set_bit((uint64_t)reg, 25, 0) )


void init_lfsr_state_test(E0 *state);
void print_lsfr1(E0 *state);
void print_lsfr2(E0 *state);
void print_lsfr3(E0 *state);
void print_lsfr4(E0 *state);
int test();
void lfsr();

#endif

