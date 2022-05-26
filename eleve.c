#include "eleve.h"

void AfficherEleve(eleve_t E)
{
    printf("\t%-20s\t\t%-20s\t\t",E.nom,E.prenom);
    AfficherDate(E.date_n);
}

bool Comparer_Eleve(eleve_t E, eleve_t E2) 
{
    if ((strcmp (E.nom,E2.nom) == 0) && (strcmp (E.prenom,E2.prenom) == 0)) //si les 2 eleves ont le meme nom ET le meme prenom
    return(true);
    else
    return(false);
}

void CopierEleve (eleve_t *Eorigine, eleve_t *Ecopie) //Nathan
{
    struct tm date;
    int nb=0;
    char tmp[20];

    memset(&date,0,sizeof(date));

    strcpy(Ecopie->nom, Eorigine->nom);
    strcpy(Ecopie->prenom, Eorigine->prenom); 

    strftime(tmp, 200, "%d", localtime(&Eorigine->date_n)); 
    nb=atoi(tmp);
    date.tm_mday=nb;
    strftime(tmp, 200, "%m", localtime(&Eorigine->date_n)); 
    nb=atoi(tmp);
    date.tm_mon=nb;
    strftime(tmp, 200, "%G", localtime(&Eorigine->date_n)); 
    nb=atoi(tmp);
    date.tm_year=nb;

    date.tm_mon = date.tm_mon-1;
    date.tm_year = date.tm_year-1900;

    Ecopie->date_n=mktime(&date);

}

void JusteNom (char *nom)   // je peux aussi normaliser le nom ici si pas fin de fonction
{                           // a coder dans la fonction
    printf("Modifier le nom de l'eleve : ");
    scanf("%s",nom);
}

void JustePrenom (char *prenom)     // je peux aussi normaliser le prénom ici si pas fin de fonction
{                                  // a coder dans la fonction
    printf("Modifier le prenom de l'eleve : ");
    scanf("%s",prenom);
}

void NommerEleveRecherche(char *nom, char *prenom) //Adonis
{
    printf ("Entrez le nom et le prénom de l'élève que vous voulez modifier : ");
    scanf("%s %s", nom, prenom);
    NormaliserNom(nom,prenom);
}

void NormaliserNom (char *nom, char *prenom)
{
    int i;
    int nb_lettre;

    nb_lettre = strlen(nom);

        for (i=0;i<nb_lettre;i++)
        nom[i]=toupper(nom[i]);

    nb_lettre = strlen(prenom);
        for(i=0;i<nb_lettre;i++)
        prenom[i]=toupper(prenom[i]);
        for(i=1;i<nb_lettre;i++)
    prenom[i]=tolower(prenom[i]);
}

void SaisirEleve(eleve_t *E)
{
    printf("\nEntrez le nom, le prénom et la date de naissance (jj/mm/aaaa) :\n");
    scanf("%s %s",E->nom, E->prenom);
    NormaliserNom(E->nom,E->prenom);
    SaisirDate(&E->date_n);
}
