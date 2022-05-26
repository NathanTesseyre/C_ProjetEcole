#include "eleve.h"

#ifndef CLASSE_H
#define CLASSE_H

typedef struct classe{
    char niveau[10];
    char nom_classe[30];
    char maitresse[20];
    int nb_eleves;
    eleve_t liste_eleves[25];
 
}classe_t;

void AffecterEleveClasse(eleve_t *E, classe_t *C);

void AfficherClasse(classe_t C);

void RangerClasse(classe_t *C);

int RechercherEleveDansClasse(classe_t C, char *nom, char *prenom);

void SaisirClasse (classe_t *C, int nbc);

void VerifierEffectifClasse(classe_t *C); //WIP

#endif
