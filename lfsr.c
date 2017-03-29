#include "lfsr.h"

void init_lfsr_state_test(E0 *state) {
  
  state->lfsr_1_4 = (uint64_t)0x04B583D;
  state->lfsr_2_3 =  (uint64_t)0x208E1EC1;
  state->lfsr_2_3 +=  ((uint64_t) 0x063C142F0 << 31);
  state->lfsr_1_4 += ((uint64_t) 0x0F7A2A42BB << 25);

  state->fsm = 3;
  state->fsm += (1 << 2);
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

void print_E0(E0 *state){
  /*print_lfsr1(state);
  print_lfsr2(state);
  print_lfsr3(state);
  print_lfsr4(state);*/

  printf("\n\n  X1 X2 X3 X4\n");
  printf("  %lu  %lu  %lu  %lu\n\n", 
    get_bit(state->lfsr_1_4, 23),
    get_bit(state->lfsr_2_3, 23),
    get_bit(state->lfsr_2_3, 31+31),
    get_bit(state->lfsr_1_4, 36+25)
  );

  printf("Yt 0x%x\n" , (state->fsm & 0x70) >> 4);
  printf("Ct 0x%x\n" , state->fsm & 0x03);
  printf("Ct-1 0x%x\n" , (state->fsm & 0x0c) >> 2);
}

void cycle_lfsr(E0 *state) {


  uint8_t xor;

  //LFSR1

  xor = get_xor_lfsr_1((uint64_t)state->lfsr_1_4);

  /*printf("LFSR1 : %lu %lu %lu %lu\n", 
    get_bit(state->lfsr_1_4, 24),
    get_bit(state->lfsr_1_4, 19),
    get_bit(state->lfsr_1_4, 11),
    get_bit(state->lfsr_1_4, 7)
  );

  printf("XOR LFSR 1 : %d\n\n", xor);*/
  set_bit(state->lfsr_1_4, 0, xor);



  //LFSR2

  xor = get_xor_lfsr_2((uint64_t)state->lfsr_2_3);

  /*printf("LFSR2 : %lu %lu %lu %lu\n", 
    get_bit(state->lfsr_2_3, 30),
    get_bit(state->lfsr_2_3, 23),
    get_bit(state->lfsr_2_3, 15),
    get_bit(state->lfsr_2_3, 11)
  );

  
  printf("XOR LFSR 2 : %d\n\n", xor);*/
  set_bit(state->lfsr_2_3, 0, xor);



  //LFSR3

  xor = get_xor_lfsr_3((uint64_t)state->lfsr_2_3);

  /*printf("LFSR3 : %lu %lu %lu %lu\n", 
    get_bit(state->lfsr_2_3, 31+32),
    get_bit(state->lfsr_2_3, 31+27),
    get_bit(state->lfsr_2_3, 31+23),
    get_bit(state->lfsr_2_3, 31+11)
  );

  printf("XOR LFSR 3 : %d\n\n", xor);*/
  set_bit(state->lfsr_2_3, 30, xor);



  //LFSR4

  xor = get_xor_lfsr_4((uint64_t)state->lfsr_1_4);

  /*printf("LFSR4 : %lu %lu %lu %lu\n", 
    get_bit(state->lfsr_1_4, 25+38),
    get_bit(state->lfsr_1_4, 25+35),
    get_bit(state->lfsr_1_4, 25+27),
    get_bit(state->lfsr_1_4, 25+3)
  );

  
  
  printf("XOR LFSR 4 : %d\n", xor);*/
  set_bit(state->lfsr_1_4, 25, xor);

  left_shift(state->lfsr_1_4);
  left_shift(state->lfsr_2_3);


}


void calcul_fsm(E0 *state){
  uint8_t st_1, ct_1, yt;

  st_1 = 0;
  ct_1 = 0;

  yt = get_bit(state->lfsr_1_4, 23) + get_bit(state->lfsr_2_3, 23) + get_bit(state->lfsr_2_3, 31+31) + get_bit(state->lfsr_1_4, 25+37) ;

  printf("yt = %d\n", yt);

  state->out = get_bit(yt, 0);

  st_1 = 2 * get_bit(state->fsm, 6) + get_bit(state->fsm, 5);

  printf("st+1 = %d\n", st_1);

  set_bit(ct_1, 1,
    get_bit(st_1, 1) ^
    get_bit(state->fsm, 1) ^
    get_bit(state->fsm, 2)
  );

  set_bit(ct_1, 0, get_bit(st_1, 0) ^ 
    get_bit(state->fsm, 0) ^
    get_bit(state->fsm, 3) ^
    get_bit(state->fsm, 2)
  );



  // Ct-1 = Ct
  state->fsm <<= 2;

  // Yt = 0 et Ct = 0
  state->fsm &= 0x0C;

  // Ct = Ct+1
  state->fsm += ct_1;

  // maj Yt
  state->fsm += (yt << 4);
}

uint8_t next_bit(E0 *state){
  calcul_fsm(state);
  cycle_lfsr(state);

  return state->out;
}


int test() {

  int i ;
  E0 state;
  uint8_t bit;

  init_lfsr_state_test(&state);

  printf("\n\n========== TOUR 1 =============\n\n");
  print_E0(&state);

  for (i = 2; i < 15; i++) {
  printf("\n\n========== TOUR %d =============\n\n", i);
    bit = next_bit(&state);
    print_E0(&state);
  }

  /*cycle_lfsr(&state);
  print_E0(&state);*/

  printf("\n");


  return 0;
}

uint32_t genere32(E0 *state) {
  int i;
  uint32_t res = 0;
  for (i = 0; i < 32; i++) {
    res += (next_bit(state) << i); 
  }
  return res;
}




int main() {

   printf("\n[+] Test LFSR : \n\n");

  test();

}
