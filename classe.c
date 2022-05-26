#include "classe.h"

void AffecterEleveClasse(eleve_t *E, classe_t *C)
{
    CopierEleve (E, &C->liste_eleves[C->nb_eleves]);

    C->nb_eleves++;

    printf("\nL'élève %s %s a été inscrit dans la classe%s.\n", E->nom, E->prenom, C->nom_classe);
}

void AfficherClasse(classe_t C)
{
    int i;
    printf("\n\n\t***** Classe de %s *****\n",C.nom_classe);
    printf("\nMaitresse : %s\tNombre d'eleves : %d\n\n",C.maitresse,C.nb_eleves);
    for (i=0;i<C.nb_eleves;i++)
    {
    printf("Elève %-15d",i+1);
    AfficherEleve(C.liste_eleves[i]);
    }
}

void RangerClasse(classe_t *C)
{
    int permut=1;
    int i=0;
    int j=0;
    char tmp[20]={0};
    time_t tmp_date;
    
    while(permut == 1)
    {
        permut=0; // initialisation et sortie de boucle
        for (i=0;i<C->nb_eleves-1;i++)
        {   //comparaison savoir si i est ou n'est pas plus petit que i+1
            if (strcmp(C->liste_eleves[i].nom,C->liste_eleves[i+1].nom) >0)
            {
            // inversion des noms
            strcpy(tmp,C->liste_eleves[i].nom);
            strcpy(C->liste_eleves[i].nom,C->liste_eleves[i+1].nom);
            strcpy(C->liste_eleves[i+1].nom,tmp);
            //inversion des prenoms
            strcpy(tmp,C->liste_eleves[i].prenom);
            strcpy(C->liste_eleves[i].prenom,C->liste_eleves[i+1].prenom);
            strcpy(C->liste_eleves[i+1].prenom,tmp);
            //inversion des dates
            tmp_date=C->liste_eleves[i].date_n;//trouver le time_date de l'eleve
            C->liste_eleves[i].date_n=C->liste_eleves[i+1].date_n;//pareil
            C->liste_eleves[i+1].date_n=tmp_date;
            
            // ATTENTION ! SI STRUCTURE PARENTS IL FAUT EGALEMENT LA FAIRE SUIVRE
                permut=1;
                }
            }    
    }//verification si il y a eu un changement

}

int RechercherEleveDansClasse(classe_t C, char *nom, char *prenom)
{
    int i=0;
    int occurrence=0;

    for ( i = 0; i < C.nb_eleves; i++)
    {
        if((strcmp(C.liste_eleves[i].nom,nom)==0) && (strcmp(prenom,C.liste_eleves[i].prenom)==0))
        {
            occurrence++;
            return(i);
        }
    }

    if (occurrence==0)
    {
        return(-1);
    }
    
    
}

void SaisirClasse (classe_t *C, int nbc)
{
    int i;
    printf("\n\tSaisir le niveau de la classe N° %d\t\t",nbc);//saisir la classe
    scanf("%s",C->niveau);
    printf("\tSaisir le nom de la Maitresse\t\t");//saisir la maitresse
    scanf("%s",C->maitresse);

    //Création du nom de la classe en concaténant le niveau et le nom de l'enseignant
    strcpy(C->nom_classe, C->niveau);
    strcat(C->nom_classe, C->maitresse);

    printf("\tCombien d'eleve comporte la classe ?\t");//saisir le nombre d'eleve
    scanf("%d",&C->nb_eleves);
    for(i=0;i<C->nb_eleves;i++)
    {
        SaisirEleve(&C->liste_eleves[i]);
    }
    RangerClasse(C);
}

/*void VerificationNiveauClasse (char *niveau)
{



}*/

//NormaliserNiveau(char *niveau)