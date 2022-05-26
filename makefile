
EcoleLogique: date.o eleve.o classe.o ecole.o main.c
	gcc date.o eleve.o classe.o ecole.o main.c -o EcoleLogique
date.o: date.c date.h
	gcc -c date.c
eleve.o: eleve.c eleve.h date.o
	gcc -c eleve.c
classe.o: classe.c classe.h eleve.o
	gcc -c classe.c
ecole.o: ecole.h ecole.c classe.o eleve.o date.o
	gcc -c ecole.c

MrProper:
	rm -f *.o