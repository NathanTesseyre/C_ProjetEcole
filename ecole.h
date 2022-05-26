#include "classe.h"

#ifndef ECOLE_H
#define ECOLE_H

typedef struct ecole {
    char nom_directeur[20];
    int annee_debut;
    int nb_classes;
    char nom_ecole[20];
    classe_t classes[25];
}ecole_t;


//Fonctions relatives aux fichiers et à la saisie

void VerificationInfosEcole(ecole_t *E, char *nom_fichier);

void RemplirInfosDepuisFichier(ecole_t *E, char *nom);

void EnregistrerInfosDansFichier(ecole_t *E);

void SaisirEcole(ecole_t *E);

void EnregistrerClasseDansFichier(ecole_t E, classe_t C, char *nf);


//Fonctions relatives au menu

void MenuApp (ecole_t *E, int occurrence);

void MenuGestionEcole(ecole_t *E);

void MenuGestionClasse(ecole_t *E);

void MenuGestionEleve(ecole_t *E);

void MenuAfficherEleve(ecole_t E);

void MenuModifierInformationsEleve(ecole_t *E);

void MenuAfficherClasse(ecole_t E);

void MenuAfficherEcole(ecole_t E);

void MenuSaisirEtAffecterEleve(ecole_t *E);

void MenuChercherEleveDansUneClasse(ecole_t *E);

void QuitterApp(ecole_t E);

void RetourMenuApp(ecole_t E);


//Fonctions utilitaires

void AffecterEleve(ecole_t *Ec, eleve_t El);

void AfficherInfosEcole(ecole_t E);

void AfficherListeClasse (ecole_t E);

void RangerEcole(ecole_t *E);

void RechercherClasseEleve(ecole_t E, char *nom, char *prenom, int *classe);

bool VerifierInscription(ecole_t E, char *nom, char *prenom);


//Fonctions supplémentaires

void ExporterClasseExcel(ecole_t E);

void SplitClasse(ecole_t *E, classe_t *C); //WIP

void VerifierEffectifsClasseEcole(ecole_t *E);

//void TrierLesClasses ()

void ModifierEleve(ecole_t *E, int place_classe, int place_eleve);

void FancyMenu();

#endif
