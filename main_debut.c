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

double frequency(int n, int* tab){
	double sobs, pValeur;
	int i, j, sizeWord, bit, res;


	res = 0;
	sizeWord = n / 1024;

	//printf("sizeWord : %d\n", sizeWord);
	//printf("bit : %d\n", get_bit(tab[0], 0));

	for(i=0; i<1024; i++){
		for(j=0; j<sizeWord; j++){


			bit = get_bit(tab[i], j);
			//printf("Bit : %d\n", bit);

			if (bit)
			{
				res++;
			}
			else
			{
				res--;
			}
		}
	}


	//printf("RES : %d\n", res);

	sobs = abs(res)/sqrt(n);
	//printf("SOBS : %f\n", sobs);

	pValeur = erfc(sobs/sqrt(2));
	//printf("pValeur : %f\n", pValeur);

	return pValeur;
}

void generate_vonNeumann(unsigned int nb, char *filename) {
	int i;
	FILE *f = fopen(filename, "w");

	// Init Von Neumann
	word16 x=1664; // nombre entre 1000 et 9999 pour Von Neumann
	word16 output_VN; // sortie pour pour Von Neumann

	int tab[nb];

	
	if (f == NULL) {
		perror("Erreur lors de l'ouverture du fichier dans generate_vonNeumann");
		exit(-1);
	}

	for (i = 0; i < nb; i++) {
		output_VN = Von_Neumann(&x); // Von Neumannc
		fprintf(f, "%u,\n", output_VN);
		tab[i] = (int) output_VN;
	}

	double freq;
	freq = frequency(nb*16, tab);

	printf("Frequency : %f\n", freq);

	printf("Von_Neumann fini\n\n");
	fclose(f);
}

void generate_mersenneTwister(unsigned int nb, char *filename) {
	int i;
	FILE *f = fopen(filename, "w");

	struct mt19937p mt; // Pour Mersenne-Twister
	int tmp = rand(); // Pour Mersenne-Twister
	word32 output_MT; // sortie pour Mersenne-Twister

	int tab[nb];

	srand(rdtsc());  // rand du C 
	sgenrand(time(NULL)+(tmp), &mt); // Mersenne-Twister


	
	if (f == NULL) {
		perror("Erreur lors de l'ouverture du fichier dans generate_mersenneTwister");
		exit(-1);
	}

	for (i = 0; i < nb; i++) {
		output_MT = genrand(&mt); // Von Neumannc
		fprintf(f, "%u,\n", output_MT);
		tab[i] = (int) output_MT;
	}

	double freq;
	freq = frequency(nb*32, tab);

	printf("Frequency : %f\n", freq);

	printf("MersenneTwister fini\n\n");
	fclose(f);
}

void generate_E0(unsigned int nb, char *filename) {
	int i;
	FILE *f = fopen(filename, "w");

	int tab[nb];

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
		tab[i] = (int) val;
	}

	double freq;
	freq = frequency(nb*32, tab);

	printf("Frequency : %f\n", freq);

	printf("E0 fini\n\n");
	fclose(f);
}

int main()
{
	printf("\n");

	generate_vonNeumann(1024, "_VonNeumann.csv");
	generate_mersenneTwister(1024, "_MersenneTwister.csv");
	generate_E0(1024, "_E0.csv");

	//testLFSR();

	return 0;
}
