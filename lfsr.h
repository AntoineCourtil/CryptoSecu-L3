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
	uint8_t fsm;

	// sortie fsm
	uint8_t out;
};

typedef struct E0_state E0;

#define get_bit(reg, no) ( ( reg & ((uint64_t)1 << ((uint64_t)no)) ) >> ((uint64_t)no) )
#define get_xor_lfsr_1(reg) ( get_bit(reg, (uint64_t)24) ^ get_bit((uint64_t)reg, (uint64_t)19) ^ get_bit((uint64_t)reg, (uint64_t)11) ^ get_bit((uint64_t)reg, (uint64_t)7) )
#define get_xor_lfsr_2(reg) ( get_bit(reg, (uint64_t)30) ^ get_bit((uint64_t)reg, (uint64_t)23) ^ get_bit((uint64_t)reg, (uint64_t)15) ^ get_bit((uint64_t)reg, (uint64_t)11) )
#define get_xor_lfsr_3(reg) ( get_bit(reg, (uint64_t)32+(uint64_t)31) ^ get_bit((uint64_t)reg, (uint64_t)27+(uint64_t)31) ^ get_bit((uint64_t)reg, (uint64_t)23+(uint64_t)31) ^ get_bit((uint64_t)reg, (uint64_t)11+(uint64_t)31) )
#define get_xor_lfsr_4(reg) ( get_bit(reg, (uint64_t)38+(uint64_t)25) ^ get_bit((uint64_t)reg, (uint64_t)35+(uint64_t)25) ^ get_bit((uint64_t)reg, (uint64_t)27+(uint64_t)25) ^ get_bit((uint64_t)reg, (uint64_t)3+(uint64_t)25) )


#define set_bit(reg, no, val) ( reg = (reg &  ~((uint64_t)1 << (uint64_t)no)) | ((uint64_t)val << (uint64_t)no))
#define set_0_lfsr_1(reg) ( set_bit(reg, 0, 0) )
#define set_0_lfsr_2(reg) ( set_bit(reg, 0, 0) )
#define set_0_lfsr_3(reg) ( set_bit(reg, 31, 0) )
#define set_0_lfsr_4(reg) ( set_bit(reg, 25, 0) )

#define left_shift(r) (r = r << 1)


void init_lfsr_state_test(E0 *state);
void init_lfsr_state_random(E0 *state);

void print_lsfr1(E0 *state);
void print_lsfr2(E0 *state);
void print_lsfr3(E0 *state);
void print_lsfr4(E0 *state);
void print_E0(E0 *state);

int testLFSR();
void lfsr();

void cycle_lfsr(E0 *state);
void calcul_fsm(E0 *state);

uint8_t next_bit(E0 *state);
uint32_t genere32(E0 *state);
uint64_t rand_uint64t();


#endif

