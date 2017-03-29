#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "von_neumann.h"
#include "mersenne_twister.h"
#include "lfsr.h"

#define ARRAY_MAX_SIZE 1000


//static int next;

int rdtsc()
{
	// cette fonction suivante cree un warning : c'est normal.
	__asm__ __volatile__("rdtsc");
}

void test()
{
	/*word16 x=1111; // nombre entre 1000 et 9999 pour Von Neumann
	struct mt19937p mt; // Pour Mersenne-Twister
	int tmp = rand(), seed; // Pour Mersenne-Twister


	word16 output_VN; // sortie pour pour Von Neumann
	word32 output_MT; // sortie pour Mersenne-Twister

               
	// initialisation des graines des generateurs

	srand(rdtsc());  // rand du C 
	seed = rand();
	sgenrand(time(NULL)+(tmp), &mt); // Mersenne-Twister
	
	// sorties des generateurs	
	output_VN = Von_Neumann(&x); // Von Neumann
	output_MT = genrand(&mt); // Mersenne-Twister

	int i;

	for (i=0; i<10; i++)
	{
		// affichage
		printf("- Generation de nombres aleatoires -\n");
		printf("Von Neumann : %u\n",output_VN);
		printf("Mersenne Twister : %u\n",output_MT);
	}*/
}

void generate_vonNeumann(unsigned int nb, char *filename) {
	int i;
	FILE *f = fopen(filename, "w");

	// Init Von Neumann
	word16 x=1664; // nombre entre 1000 et 9999 pour Von Neumann
	word16 output_VN; // sortie pour pour Von Neumann

	
	if (f == NULL) {
		perror("Erreur lors de l'ouverture du fichier dans generate_vonNeumann");
		exit(-1);
	}

	for (i = 0; i < nb; i++) {
		output_VN = Von_Neumann(&x); // Von Neumannc
		fprintf(f, "%u,\n", output_VN);
	}

	printf("Von_Neumann fini\n");
	fclose(f);
}

void generate_mersenneTwister(unsigned int nb, char *filename) {
	int i;
	FILE *f = fopen(filename, "w");

	struct mt19937p mt; // Pour Mersenne-Twister
	int tmp = rand(); // Pour Mersenne-Twister
	word32 output_MT; // sortie pour Mersenne-Twister

	srand(rdtsc());  // rand du C 
	sgenrand(time(NULL)+(tmp), &mt); // Mersenne-Twister


	
	if (f == NULL) {
		perror("Erreur lors de l'ouverture du fichier dans generate_mersenneTwister");
		exit(-1);
	}

	for (i = 0; i < nb; i++) {
		output_MT = genrand(&mt); // Von Neumannc
		fprintf(f, "%u,\n", output_MT);
	}

	printf("MersenneTwister fini\n");
	fclose(f);
}

void generate_E0(unsigned int nb, char *filename) {
	int i;
	FILE *f = fopen(filename, "w");

	uint32_t val;
	E0 state;
	init_lfsr_state_test(&state);


	if (f == NULL) {
		perror("Erreur lors de l'ouverture du fichier dans generate_E0");
		exit(-1);
	}

	for (i = 0; i < nb; i++) {
		val = genere32(&state);
		fprintf(f, "%u,\n", val);
	}

	printf("E0 fini\n");
	fclose(f);
}

int main()
{
	
	generate_vonNeumann(1024, "VonNeumann.csv");
	generate_mersenneTwister(1024, "MersenneTwister.csv");
	generate_E0(1024, "E0.csv");

	return 0;
}
