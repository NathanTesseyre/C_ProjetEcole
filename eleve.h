#include "date.h"

#ifndef ELEVE_H
#define ELEVE_H

typedef struct eleve {
    char nom[20];
    char prenom[20];
    time_t date_n;
     
}eleve_t;

void AfficherEleve(eleve_t E);

bool Comparer_Eleve(eleve_t E, eleve_t E2);

void CopierEleve (eleve_t *Eorigine, eleve_t *Ecopie);

void JusteNom (char *nom);

void JustePrenom (char *prenom);

void NommerEleveRecherche(char *nom, char *prenom);

void NormaliserNom (char *nom, char *prenom);

void SaisirEleve(eleve_t *E);

#endif
