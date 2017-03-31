OBJ = mersenne_twister.o von_neumann.o lfsr.o

simu: main_debut.c $(OBJ)
	gcc -Wall -std=c99 -pedantic -o simul main_debut.c -lm $(OBJ)

# Ces 2 lignes définissent la méthode de création d'un .o
.SUFFIXES: .o

.c.o:; gcc -Wall -std=c99 -pedantic -c -o $@ -lm $<

mersenne_twister.o: mersenne_twister.h mersenne_twister.c 

von_neumann.o: von_neumann.h von_neumann.c

lfsr.o : lfsr.h lfsr.c

clean:
	rm *.o simu

