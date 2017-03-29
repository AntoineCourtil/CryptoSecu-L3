#include "lfsr.h"

void init_lfsr_state_test(E0 *state) {
  
  state->lfsr_1_4 = (uint64_t)0x04B583D;
  state->lfsr_1_4 += ((uint64_t) 0x0F7A2A42BB << 25);
  state->lfsr_2_3 =  (uint64_t)0x208E1EC1;
  state->lfsr_2_3 +=  ((uint64_t) 0x063C142F0 << 31);

  //state->fsm_memory = 3; //  C[t] <= 11
  //state->fsm_memory += (1 << 2); // C[t-1] <= 01
}

void print_lfsr1(E0 *state) {
  uint64_t lfsr1 = state->lfsr_1_4 & 0x1FFFFFF;
  printf("[LFSR1] 0x%lx -> \n", lfsr1);
  int i;

  for (i = 0; i < 25; i++) {
    if(i%4 == 0){
      printf(" ");
    }
    //printf("%d:%lu ", i, get_bit(lfsr1, i));
    printf("%lu ", get_bit(lfsr1, i));
  }
  
  printf("\n");

  for (i = 0; i < 25; i++) {
    if(i % 4 == 0){
        printf(" ");
    }
    if(i == 24 || i == 19 || i == 11 || i == 7){

      printf("x ");
    }
    else{
      printf("  ");
    }
  }

  printf("\n");
  
}

void print_lfsr2(E0 *state) {
  uint64_t lfsr2 = state->lfsr_2_3 & 0x7FFFFFFF;
  printf("[LFSR2] 0x%lx -> \n", lfsr2);
  int i;

  for (i = 0; i < 31; i++) {
    if(i%4 == 0){
      printf(" ");
    }
    //printf("%d:%lu ", i, get_bit(lfsr2, i));
    printf("%lu ", get_bit(lfsr2, i));
  }
  
  printf("\n");

  for (i = 0; i < 31; i++) {
    if(i % 4 == 0){
        printf(" ");
    }
    if(i == 30 || i == 23 || i == 15 || i == 11){

      printf("x ");
    }
    else{
      printf("  ");
    }
  }

  printf("\n");
  
}

void print_lfsr3(E0 *state) {
  uint64_t lfsr3 = state->lfsr_2_3 >> 31;
  printf("[LFSR3] 0x%lx -> \n", lfsr3);
  int i;
  
  for (i = 0; i < 33; i++) {
    if(i%4 == 0){
      printf(" ");
    }
    //printf("%d:%lu ", i, get_bit(lfsr3, i));
    printf("%lu ", get_bit(lfsr3, i));
  }
  
  printf("\n");

  for (i = 0; i < 33; i++) {
    if(i % 4 == 0){
        printf(" ");
    }
    if(i == 32 || i == 27 || i == 23 || i == 11){

      printf("x ");
    }
    else{
      printf("  ");
    }
  }

  printf("\n");
  
}

void print_lfsr4(E0 *state) {
  uint64_t lfsr4 = state->lfsr_1_4 >> 25;
  printf("[LFSR4] 0x%lx -> \n", (uint64_t)lfsr4);

  printf("SizeOf : %lu\n", sizeof(lfsr4));

  int i;
  
  for (i = 0; i < 39; i++) {
    if(i%4 == 0){
      printf(" ");
    }
    //printf("%d:%lu ", i, get_bit((uint64_t)lfsr4, (uint64_t)i));
    printf("%lu ", get_bit(lfsr4, i));
  }

  printf("\n");

  for (i = 0; i < 39; i++) {
    if(i % 4 == 0){
        printf(" ");
    }
    if(i == 38 || i == 35 || i == 27 || i == 3){

      printf("x ");
    }
    else{
      printf("  ");
    }
  }

  printf("\n");
  
}

void cycle_lfsr(E0 *state) {
  uint8_t xor, buffer;

  buffer = 0;

  //LFSR1

  xor = get_xor_lfsr_1((uint64_t)state->lfsr_1_4);

  printf("LFSR1 : %lu %lu %lu %lu\n", 
    get_bit(state->lfsr_1_4, 24),
    get_bit(state->lfsr_1_4, 19),
    get_bit(state->lfsr_1_4, 11),
    get_bit(state->lfsr_1_4, 7)
  );

  printf("XOR LFSR 1 : %d\n", xor);
  set_bit(state->lfsr_1_4, 0, xor);



  //LFSR2

  xor = get_xor_lfsr_2((uint64_t)state->lfsr_2_3);

  printf("LFSR2 : %lu %lu %lu %lu\n", 
    get_bit(state->lfsr_2_3, 30),
    get_bit(state->lfsr_2_3, 23),
    get_bit(state->lfsr_2_3, 15),
    get_bit(state->lfsr_2_3, 11)
  );

  
  printf("XOR LFSR 2 : %d\n", xor);
  set_bit(state->lfsr_2_3, 0, xor);



  //LFSR3

  xor = get_xor_lfsr_3((uint64_t)state->lfsr_2_3);

  printf("LFSR3 : %lu %lu %lu %lu\n", 
    get_bit(state->lfsr_2_3, 31+32),
    get_bit(state->lfsr_2_3, 31+27),
    get_bit(state->lfsr_2_3, 31+23),
    get_bit(state->lfsr_2_3, 31+11)
  );

  printf("XOR LFSR 3 : %d\n", xor);
  set_bit(state->lfsr_2_3, 31, xor);



  //LFSR4

  xor = get_xor_lfsr_4((uint64_t)state->lfsr_1_4);

  printf("LFSR2 : %lu %lu %lu %lu\n", 
    get_bit(state->lfsr_1_4, 25+38),
    get_bit(state->lfsr_1_4, 25+35),
    get_bit(state->lfsr_1_4, 25+27),
    get_bit(state->lfsr_1_4, 25+3)
  );

  
  
  printf("XOR LFSR 4 : %d\n", xor);
  set_bit(state->lfsr_1_4, 25, xor);
}

int test() {

  int i ;
  E0 state;
  uint8_t res = 0;
  uint8_t bit;

  init_lfsr_state_test(&state);

  print_lfsr1(&state);
  print_lfsr2(&state);
  print_lfsr3(&state);
  print_lfsr4(&state);

  /*for (i = 0; i < 4; i++) {
    bit = nextBit(&state);
    printf("%d ", bit);
    res += (bit << i);
  }*/

  printf("\n");

  cycle_lfsr(&state);


  

  print_lfsr1(&state);
  print_lfsr2(&state);
  print_lfsr3(&state);
  print_lfsr4(&state);

  return res == 2;
}



void main()
{
   printf("\n[+] Test LFSR : \n\n");

  test();

}
