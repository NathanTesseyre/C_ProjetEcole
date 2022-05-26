#include "ecole.h"

//Fonctions relatives aux fichiers et à la saisie

void VerificationInfosEcole(ecole_t *E, char *nom_entre)
{
    char nom_fichier[40];

    strcat(nom_fichier,nom_entre);
    strcat(nom_fichier,".xls");

    FILE *FICH_EXCEL=fopen(nom_fichier,"r");

    if (FICH_EXCEL==NULL)//si le fichier n'existe pas
    {
        SaisirEcole(E);
        EnregistrerInfosDansFichier(E);
    }
    else
    {
        RemplirInfosDepuisFichier(E,nom_fichier);
    }
    
    fclose(FICH_EXCEL);
}

void RemplirInfosDepuisFichier(ecole_t *E, char *nom)
{
    int nb_classes=0;
    int i=0;
    int j=0;
    char ligne[2000];
    char *champ;
    struct tm date;


    FILE *FICH_EXCEL=fopen(nom,"r"); //Ouverture du fichier en mode lecture

        if (FICH_EXCEL==NULL) 
        {
            perror("Erreur durant l'ouverture du fichier");
            exit(EXIT_FAILURE);
        }

        //On récupère sur la  première ligne du tableau les informations relatives à l'école
        
        fgets(ligne,2000,FICH_EXCEL);

        champ=strtok(ligne,";");
        strcpy(E->nom_directeur,champ);

        champ=strtok(NULL,";");
        E->annee_debut=atoi(champ);

        champ=strtok(NULL,";");
        E->nb_classes=atoi(champ);

        champ=strtok(NULL,";");
        strcpy(E->nom_ecole,champ);


        //On utilise une boucle pour récupérer les infos relatives à la classe
        for ( i = 0; i < E->nb_classes; i++)
        {

            fgets(ligne,2000,FICH_EXCEL);

            champ=strtok(ligne,";");
            strcpy(E->classes[i].niveau,champ);

            champ=strtok(NULL,";");
            strcpy(E->classes[i].nom_classe,champ);

            champ=strtok(NULL,";");
            strcpy(E->classes[i].maitresse,champ);

            champ=strtok(NULL,";");
            E->classes[i].nb_eleves=atoi(champ);

            //On utilise ensuite une dernière boucle pour récupérer tous les élèves qui composent la classe
            for ( j = 0; j < E->classes[i].nb_eleves; j++)
            {
                fgets(ligne,2000,FICH_EXCEL);

                champ=strtok(ligne,";");
                strcpy(E->classes[i].liste_eleves[j].nom, champ);
                champ=strtok(NULL,";");
                strcpy(E->classes[i].liste_eleves[j].prenom, champ);

                champ=strtok(NULL,";");
                memset(&date,0,sizeof(date)); //On met notre variable locale date à 0
                sscanf(champ,"%d/%d/%d", &date.tm_mday, &date.tm_mon, &date.tm_year);
                date.tm_mon=date.tm_mon-1;
                date.tm_year=date.tm_year-1900;
                E->classes[i].liste_eleves[j].date_n=mktime(&date);
            }
            
            //Une fois tous les élèves de la classe récupérés on passe à la classe suivante

        }

    //Une fois toutes les classes traitées on referme le fichier

    fclose(FICH_EXCEL);
    RangerEcole(E);
}

void EnregistrerInfosDansFichier(ecole_t *E)
{
    int i=0;
    int j=0;char date[200];
    char nom_fichier[40];

    strcpy(nom_fichier,E->nom_ecole);
    //On ajoute l'extension .xls à la fin du nom de notre fichier
    strcat(nom_fichier,".xls");

    FILE *FICH_EXCEL=fopen(nom_fichier,"w"); //Ouverture du fichier en mode écriture

    if (FICH_EXCEL==NULL)
    {
        perror("Erreur ouverture fichier");
        exit(EXIT_FAILURE);
    }

    //On écrit sur la  première ligne du tableau les informations relatives à l'école
    fprintf(FICH_EXCEL, "%s;%d;%d;%s;\n", E->nom_directeur, E->annee_debut, E->nb_classes,E->nom_ecole);

    for ( i = 0; i < E->nb_classes; i++)
    {
        //On utilise une boucle pour écrire les infos relatives à la classe
        fprintf(FICH_EXCEL, "%s;%s;%s;%d;\n", E->classes[i].niveau, E->classes[i].nom_classe, E->classes[i].maitresse, E->classes[i].nb_eleves);

        for ( j = 0; j < E->classes[i].nb_eleves; j++)
        {
            //On utilise ensuite une dernière boucle pour écrire tous les élèves qui composent la classe
            strftime(date, 200, "%d/%m/%G", localtime(&E->classes[i].liste_eleves[j].date_n)); 
            fprintf(FICH_EXCEL, "%s;%s;%s\n", E->classes[i].liste_eleves[j].nom, E->classes[i].liste_eleves[j].prenom, date );
        }
        
        //Une fois tous les élèves de la classe écrits dans le fichier on passe à la classe suivante

    }

    //Une fois toutes les classes traitées on referme le fichier
    fclose(FICH_EXCEL);
}

void SaisirEcole(ecole_t *E)
{
    int i;
    printf("\n\n\tSaisir le nom de l'ecole :\t");//saisir l'ecole
    scanf("%s",E->nom_ecole);
    printf("\tSaisir le nom du Directeur :\t");//saisir le directeur
    scanf("%s",E->nom_directeur);
    printf("\tSaisir l'année de début :\t");//saisir l'année d'étude
    scanf("%d",&E->annee_debut);
    printf("\tSaisir le nombre de classes :\t");//saisir le nb de classes
    scanf("%d",&E->nb_classes);
    for(i=0;i<E->nb_classes;i++) //boucle pour fonction de saisi des classes
        SaisirClasse(&E->classes[i],i+1);
    RangerEcole(E);
}

void EnregistrerClasseDansFichier(ecole_t E, classe_t C, char *nf)
{
    int i=0;
    char date[200];
    char nom_fichier[40]={"\0"};

    strcpy(nom_fichier,C.nom_classe);
    strcat(nom_fichier,"-");
    strcat(nom_fichier,E.nom_ecole);
    //On ajoute l'extension .xls à la fin du nom de notre fichier
    strcat(nom_fichier,".xls");

    FILE *FICH_EXCEL=fopen(nom_fichier,"w"); //Ouverture du fichier en mode écriture

    if (FICH_EXCEL==NULL)
    {
        perror("Erreur ouverture fichier");
        exit(EXIT_FAILURE);
    }

    //On écrit sur la  première ligne du tableau les informations relatives à la classe
    fprintf(FICH_EXCEL, "%s;%s;\n", E.nom_ecole, C.nom_classe);

        for ( i = 0; i < C.nb_eleves; i++)
        {
            //On utilise ensuite une dernière boucle pour écrire tous les élèves qui composent la classe
            strftime(date, 200, "%d/%m/%G", localtime(&C.liste_eleves[i].date_n)); 
            fprintf(FICH_EXCEL, "%s;%s;%s\n", C.liste_eleves[i].nom, C.liste_eleves[i].prenom, date );
        }
        
    //Une fois tous les eleves traitées on referme le fichier
    fclose(FICH_EXCEL);

    strcpy(nf, nom_fichier);
}

//Fonctions relatives au menu

void MenuApp (ecole_t *E, int occurrence)

{
    int choix = 0;
    //affichage du menu
    do
    {
        if(occurrence==0)
        {
        printf("\n\t\t***** Bienvenue sur l'application Ecole-Logique *****\n\n");
        }
        else
        {
            printf("\t********************************\n");
            printf("\t\tMenu Principal :\n\n");
        }
        occurrence++;


        printf("\nQue voulez vous faire ?\n\n");

        printf("\t1 Accéder au menu de gestion de l'école pour :\n\n"); //=> MenuGestionEcole
        printf("\t\t- Afficher les informations de l'école;\n"); //=>
        printf("\t\t- Afficher toute l'école;\n"); //=>
        printf("\t\t- Charger une nouvelle base de données;\n"); //=>
        //printf("\t\t- Enregistrer les données dans un fichier Excel;\n"); //=>

        printf("\n\t2 Accéder au menu de gestion des classes pour :\n\n"); //=> MenuGestionClasse
        printf("\t\t- Afficher la liste des classes;\n"); //=>
        printf("\t\t- Afficher tous les élèves d'une classe;\n"); //=>
        printf("\t\t- Enregistrer la liste des élèves dans un fichier Excel;\n"); //=>

        printf("\n\t3 Accéder au menu de gestion des élèves pour : \n\n"); //=> MenuGestionEleves
        printf("\t\t- Inscrire un élève;\n"); //=>
        printf("\t\t- Modifier un élève;\n"); //=>
        printf("\t\t- Rechercher un élève;\n"); //=>

        printf("\n\t0 Quitter l'application\n\n");  

        printf("Choix : ");
        scanf("%d", &choix);
        printf("\n");
        
        switch (choix)
            {
            case 0: QuitterApp(*E);
            break;   

            case 1: 
                    MenuGestionEcole(E);
            break;

            case 2: 
                    MenuGestionClasse(E); 
                    //MenuApp (E);
            break;

            case 3: 
                    MenuGestionEleve(E);
                    //MenuApp (E);
            break;
            
            default:
                {
                printf("Nous n'avons pas compris votre choix.\n\n");
                if(occurrence>=5)
                printf("!!!! L'ERREUR EST PROBABLEMENT ENTRE LA CHAISE ET LE CLAVIER !!!!\n\n");
                }
            }
    
    } while (choix!=0&&choix!=1&&choix!=2&&choix!=3&&occurrence<5);

}

void MenuGestionEcole(ecole_t *E)
{
    int choix=0;

    do
    {
        printf("\t************************************\n");
        printf("\t\tMenu Gestion Ecole :\n\n");
        printf("\nQue voulez vous faire ?\n\n");
        printf("\t1 Afficher les informations de l'école;\n"); //=>
        printf("\t2 Afficher toute l'école;\n"); //=>
        printf("\t3 Charger une nouvelle base de données;\n"); //=>
        //printf("\t4 Enregistrer les données dans un nouveau fichier Excel;\n"); //=>
        //printf("\t4 Ouvrir une nouvelle classe;\n"); //=>
        printf("\t4 Retourner au Menu Principal;\n"); //=>
        printf("\t0 Quitter l'application\n\n"); 
        printf("Choix : ");
        scanf("%d", &choix);
        printf("\n");

        switch (choix)
        {
        case 0:QuitterApp(*E);
            break;
        case 1:AfficherInfosEcole(*E); RetourMenuApp(*E);
            break;
        case 2:MenuAfficherEcole(*E); RetourMenuApp(*E);
            break;
        case 3:
                {   
                    char nom_fichier [50];
                    printf("Quel est le nom du fichier depuis lequel vous souhaitez travailler ? "); //extension ??
                    scanf("%s", nom_fichier);
                    RemplirInfosDepuisFichier(E, nom_fichier);
                    RetourMenuApp(*E);
                }
            break;
        //case 4:EnregistrerInfosDansFichier(E);  RetourMenuApp(*E); //A retoucher
            //break;
        case 4:MenuApp(E,1);
            break;
        
        default:printf("Nous n'avons pas compris votre choix.\n\n");
            break;

        }
        
    } while (choix!=0&&choix!=1&&choix!=2&&choix!=3&&choix!=4);
}

void MenuGestionClasse(ecole_t *E)
{
    int choix=0;

    do
    {
        printf("\t************************************\n");
        printf("\t\tMenu Gestion Classe :\n\n");
        printf("\nQue voulez vous faire ?\n\n");
        printf("\t1 Afficher la liste des classes;\n"); //=>
        printf("\t2 Afficher tous les élèves d'une classe;\n"); //=>
        printf("\t3 Enregistrer la liste des élèves dans un fichier Excel;\n");//=>
        //printf("\t4 Ouvrir une nouvelle classe;\n"); //=>
        printf("\t4 Retourner au Menu Principal;\n"); //=>
        printf("\t0 Quitter l'application\n\n"); 
        printf("Choix : ");
        scanf("%d", &choix);
        printf("\n");

        switch (choix)
        {
        case 0:QuitterApp(*E);
            break;
        case 1:AfficherListeClasse(*E); RetourMenuApp(*E);
            break;
        case 2:MenuAfficherClasse(*E); RetourMenuApp(*E);
            break;
        case 3:ExporterClasseExcel(*E); RetourMenuApp(*E); 
            break;
        case 4:MenuApp(E,1);
            break;
        
        default:printf("Nous n'avons pas compris votre choix.\n\n");
            break;
        }
    
    } while (choix!=0&&choix!=1&&choix!=2&&choix!=3&&choix!=4);
}

void MenuGestionEleve(ecole_t *E)
{
    int choix=0;

    do
    {
        printf("\t************************************\n");
        printf("\t\tMenu Gestion Eleve :\n\n");
        printf("\nQue voulez vous faire ?\n\n");
        printf("\t1 Inscrire un élève;\n"); //=>
        printf("\t2 Modifier un élève;\n"); //=>
        printf("\t3 Rechercher un élève;\n"); //=>
        printf("\t4 Retourner au Menu Principal;\n"); //=>
        printf("\t0 Quitter l'application\n\n"); 
        printf("Choix : ");
        scanf("%d", &choix);
        printf("\n");

        switch (choix)
        {
        case 0:QuitterApp(*E);
            break;
        case 1:MenuSaisirEtAffecterEleve(E); RetourMenuApp(*E);
            break;
        case 2:MenuModifierInformationsEleve(E); RetourMenuApp(*E);
            break;
        case 3:MenuChercherEleveDansUneClasse(E); RetourMenuApp(*E);
            break;
        case 4:MenuApp(E,1);
            break;
        
        default:printf("Nous n'avons pas compris votre choix.\n\n");
            break;
        }
    } while (choix!=0&&choix!=1&&choix!=2&&choix!=3&&choix!=4);
}

void MenuAfficherEleve(ecole_t E)
{
    char nom[20];
    char prenom[20];
    int classe=0;
    int index=0;

    printf("Entrez le nom et le prénom de l'élève dont vous souhaitez afficher les informations : ");
    scanf("%s %s", nom, prenom);
    NormaliserNom(nom,prenom);
    printf("\n");

    RechercherClasseEleve(E,nom,prenom,&classe);

    if (classe==-1)
    {
        printf("Cet élève n'est pas inscrit dans l'école.\n");
    }
    else
    {
        index=RechercherEleveDansClasse(E.classes[classe],nom,prenom);
        AfficherEleve(E.classes[classe].liste_eleves[index]);
    }
    

}

void MenuModifierInformationsEleve(ecole_t *E) //Adonis
{
    int placement_eleve =0;
    int placement_classe =0;
    char nom[20];
    char prenom[20];
    char reponse;
        do
        {
            NommerEleveRecherche(nom,prenom);
            RechercherClasseEleve(*E,nom,prenom, &placement_classe);
            if (placement_classe == -1)
                {
                printf("\nCet élève n'est pas inscrit dans l'école.");
                printf("\nDesirez vous refaire une saisie (o/n) ? ");
                getchar();
                scanf("%c",&reponse);
                printf("\n");
                if(reponse != 'o' && reponse != 'O')
                return;// ou MenuApp mais ca devient recursif non ?
                }
        }while(placement_classe == -1);

    placement_eleve = RechercherEleveDansClasse(E->classes[placement_classe],nom,prenom);
    printf("\nModification de  : ");
    AfficherEleve(E->classes[placement_classe].liste_eleves[placement_eleve]);
    ModifierEleve(E,placement_classe,placement_eleve);
    printf("\nLa modification a été effectuée avec succès !\n");
}

void MenuAfficherClasse(ecole_t E) //Enrique
{
    int i;
    int nb;
    
    AfficherListeClasse(E);

    do{

        printf("\n\nQuelle classe souhaitez-vous afficher (1 à %d) ? ",E.nb_classes);
        scanf("%d",&nb);
        
        if(nb>=1 && nb<=E.nb_classes)
        {
            AfficherClasse(E.classes[nb-1]);
            return;
        }
        else
        {
            printf("Le choix entré n'est pas valable.\n");
        }
  
    }while (nb>=1 || nb<=E.nb_classes);
    
}

void MenuAfficherEcole(ecole_t E)
{
    int i;
    printf("\n\tEcole : %s\tDirecteur : %s",E.nom_ecole,E.nom_directeur);
    printf("\nCette ecole comporte %d classes pour l'année %d",E.nb_classes,E.annee_debut);
        for (i=0;i<E.nb_classes;i++) // boucle d'affichage des classes qui elle meme à une boucle d'affichage des eleves
        AfficherClasse(E.classes[i]);
}

void MenuSaisirEtAffecterEleve(ecole_t *E) //Nathan
{
    int classe=0;
    eleve_t Temp;

    SaisirEleve(&Temp);
    //printf("Entrez le nom, le prénom et la date de naissance (jj/mm/aaaa) de l'élève que vous souhaitez inscrire dans l'école : ");
    //scanf("%s %s", Temp.nom, Temp.prenom);
    //SaisirDate(&Temp.date_n);

    RechercherClasseEleve(*E,Temp.nom,Temp.prenom,&classe);

    if (classe!=-1)
    {
        printf("\nCet élève est déjà inscrit dans l'école dans la classe %s.\n", E->classes[classe].nom_classe);
    }
    else
    {
        AffecterEleve(E,Temp);
    }
    
}

void MenuChercherEleveDansUneClasse(ecole_t *E) //Enrique
{

    eleve_t Temp;
    int choix=0;
    int classe=0;
    int reponse=0;
    int tmp=0;
    

    printf("Entrez le nom et le prénom de l'élève que vous souhaitez rechercher : ");
    scanf("%s %s", Temp.nom, Temp.prenom);
    NormaliserNom(Temp.nom, Temp.prenom);
    if (VerifierInscription(*E, Temp.nom,Temp.prenom)==true)
    {
        RechercherClasseEleve(*E,Temp.nom,Temp.prenom, &classe);
        printf("%s %s est dans la classe %s.\n", Temp.nom, Temp.prenom,E->classes[classe].nom_classe);

    }
    else
    {
        printf("\nCet élève n'est pas inscrit dans l'école.");
        printf("\n\nQue voulez-vous faire ?\n");
        printf("\n\t1 Lancer la procédure d'inscription;");
        printf("\n\t0 Retourner au Menu Principal\n\nChoix : ");
        scanf("%d", &reponse);

        if (reponse==1)
        {
            printf("\nEntrez la date de naissance de l'élève : ");
            SaisirDate(&Temp.date_n);
            printf("\nQue voulez-vous faire ?\n");
            printf("\n\t1 L'inscrire manuellement dans une classe;");
            printf("\n\t2 L'inscrire automatiquement dans une classe en fonction de son âge;\n\t0 Annuler l'inscription;\n\nChoix : ");
            scanf("%d", &choix);
            printf("\n");
            switch (choix)
            {
            case 1:
                    {
                        AfficherListeClasse(*E);
                        printf("\n\nDans quelle classe souhaitez-vous inscrire %s %s ? ",Temp.nom, Temp.prenom);
                        scanf("%d", &classe);
                        AffecterEleveClasse(&Temp,&E->classes[classe-1]);

                    }
                break;
            case 2:
                AffecterEleve(E, Temp);
                break;
            case 0:
                break;
            
            default:printf("Nous n'avons pas compris votre choix.\n\n");
                break;
            }
        }
        
    }

}

void QuitterApp(ecole_t E)
{
    int reponse=0;

    printf("Vous êtes sur le point de quitter l'application.\n");
    printf("Souhaitez-vous sauvegarder vos modifications dans le fichier ? \n\n");
    printf("1 Sauvegarder et quitter\t0 Quitter sans sauvegarder\n\nChoix : ");
    scanf("%d", &reponse);

    if (reponse==1)
    {
        EnregistrerInfosDansFichier(&E);
    }
    
}

void RetourMenuApp(ecole_t E)
{
    int choix=0;
    printf("\n\n*****Tâche terminée*****\n\nQue voulez-vous faire ?\n");
    printf("\n\t1 Retourner au Menu Principal\n\t0 Quitter l'application\n\nChoix : ");
    scanf("%d", &choix);
    if (choix==1)
    {
        MenuApp(&E, 1);
    }
    else
    {
        QuitterApp(E);
    }
    
}

//Fonctions utilitaires

void AffecterEleve(ecole_t *Ec, eleve_t El)
{
    int age=0;
    int annee_naissance=0;
    double diff=0;
    char annee[200];

  
    strftime(annee, 200, "%G", localtime(&El.date_n)); //On récupère l'année de naissance sous forme de string dans annee

    annee_naissance=atoi(annee); //On convertit en entier et on stocke dans annee_naissance

    age=Ec->annee_debut-annee_naissance;


    switch (age)
    {
    case 6: AffecterEleveClasse(&El,&Ec->classes[0]);
        
        break;
    case 7: AffecterEleveClasse(&El,&Ec->classes[1]);
        
        break;
    case 8: AffecterEleveClasse(&El,&Ec->classes[2]);
        
        break;
    case 9: AffecterEleveClasse(&El,&Ec->classes[3]);
        
        break;
    case 10: AffecterEleveClasse(&El,&Ec->classes[4]);
        
        break;
    
    default: printf("\nCet élève ne doit pas être inscrit dans une école primaire.\n");
        break;
    }

}

void AfficherInfosEcole(ecole_t E)
{
    printf("\t***********************************\n");
    printf("\t\tInformation Ecole :\n\n");
    printf("\nEcole : %s\tDirecteur : %s",E.nom_ecole,E.nom_directeur);
    printf("\tNombre de classes : %d\tAnnée : %d\n",E.nb_classes,E.annee_debut);
}

void AfficherListeClasse (ecole_t E)
{
    int i;

    printf("Voici la liste des classes :\n");

    for (i=0;i<E.nb_classes;i++)
    {
        printf("%d - %s\t",i+1,E.classes[i].nom_classe);
    }
}

// fait boucler RangerClasse pour mettre chaque eleve de chaque classe dans l'ordre alphabetique
void RangerEcole(ecole_t *E)
{
int i=0;

    for(i=0;i<E->nb_classes;i++)
    RangerClasse(&E->classes[i]);
}

void RechercherClasseEleve(ecole_t E, char *nom, char *prenom, int *classe)
{
    int i=0;
    int j=0;
    int retour=0;
    char reponse;
    
    *classe=-1;

    for ( i = 0; i < E.nb_classes; i++)
    {
        for ( j = 0; j < E.classes[i].nb_eleves; j++)
        {
            if((strcmp(nom,E.classes[i].liste_eleves[j].nom)==0) && (strcmp(prenom,E.classes[i].liste_eleves[j].prenom)==0))
            {
                *classe=i;
            }
        }
        
    }

    
}

bool VerifierInscription(ecole_t E, char *nom, char *prenom) //Enrique
{
    int classe=0;
    

    //printf("Entrez le nom et le prénom de l'élève dont vous souhaitez verifier : ");
    //scanf("%s %s", nom, prenom);
    RechercherClasseEleve(E,nom,prenom,&classe);

    if (classe==-1)
    {
        return(false);
    }
    else
    {
        return(true);
    }

}

//Fonctions supplémentaires

void ExporterClasseExcel(ecole_t E)
{
    int classe=0;
    char nom_fichier[40];

    AfficherListeClasse(E);
    
    printf("\n\nQuelle classe souhaitez-vous exporter ? ");

    scanf("%d", &classe);

    EnregistrerClasseDansFichier(E, E.classes[classe-1], nom_fichier);

    printf("Le fichier %s a bien été créé.");
}
    
void SplitClasse(ecole_t *E, classe_t *C) //WIP
{

}

void VerifierEffectifsClasseEcole(ecole_t *E) 
{
    char reponse;
    int i;
    int occurrence=0;

    for ( i = 0; i < E->nb_classes; i++)
    { 

        if (E->classes[i].nb_eleves>25)
        {
            printf("La classe %s est en sureffectif. Elle contient actuellement %d élèves (25 maximum).\n", E->classes[i].nom_classe, E->classes[i].nb_eleves);
            printf("Souhaitez-vous créer une nouvelle classe afin de désengorger la classe %s ? (y/n) ", E->classes[i].nom_classe);
            scanf("%c", &reponse);
            
            if (reponse=='y')
            {
                SplitClasse(E, &E->classes[i]);
            }
            else
            {
                occurrence++;
            }
            
        }
                
    printf("Il y a actuellement %d classes qui sont en sureffectif.\n", occurrence);

    }
    
}
//void TrierLesClasses ()

void ModifierEleve(ecole_t *E, int place_classe, int place_eleve)
{
    int choix=0;

    printf("\nQue voulez vous faire ?\n\n");
    printf("\t1 Modifier le nom;\n");
    printf("\t2 Modifier le prenom;\n");
    printf("\t3 modifier la date de naissance;\n");
    printf("\t4 Tout modifier;\n");
    //printf("\t5 supprimer l'eleve;\n");
    printf("\t0 Retour menu principal\n\n");

    printf("Choix : ");
    scanf("%d", &choix);
    printf("\n");

    switch (choix)
    {
    case 0:RetourMenuApp(*E);
        break;
    case 1:JusteNom(E->classes[place_classe].liste_eleves[place_eleve].nom);
        break;
    case 2:JustePrenom(E->classes[place_classe].liste_eleves[place_eleve].prenom);
        break;
    case 3:JusteDate(&E->classes[place_classe].liste_eleves[place_eleve].date_n);
        break;
    case 4:SaisirEleve(&E->classes[place_classe].liste_eleves[place_eleve]);
        break;
//    case 5:printf(" RESTE A CODER");
//        break;

    default:printf("Nous n'avons pas compris votre choix.\n\n  ");
        break;
    }
NormaliserNom(E->classes[place_classe].liste_eleves[place_eleve].nom,E->classes[place_classe].liste_eleves[place_eleve].prenom);
}

void FancyMenu()
{
    int choix=0;

    printf ("╔═══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║%79s║", " ");
    printf("\n║%13s%39s%13s║"," ", "*****Bienvenue sur l'application Ecole-Logique ******", " ");
    printf("\n║%79s║", " ");
    printf ("\n╠═══════════════════════════════════════════════════════════════════════════════╣");
    printf("\n║%79s║", " ");
    printf("\n║%26s%53s║", "Que voulez vous faire ?", " ");
    printf("\n║%79s║", " ");
    printf("\n║%55s%26s║", "1 Accéder au menu de gestion de l'école pour :", " ");
    printf("\n║%58s%22s║", "- Afficher toutes les informations de l'école;", " ");
    printf("\n║%51s%29s║", "- Charger une nouvelle base de données;", " ");
    printf("\n║%60s%20s║", "- Enregistrer les données dans un fichier Excel;", " ");
    printf("\n║%40s%39s║", "- Ouvrir une nouvelle classe;", " ");
    printf("\n║%79s║", " ");
    printf("\n║%55s%25s║", "2 Accéder au menu de gestion des classes pour :", " ");
    printf("\n║%43s%36s║", "- Afficher la liste des classes;", " ");
    printf("\n║%53s%28s║", "- Afficher tous les élèves d'une classe;", " ");
    printf("\n║%69s%12s║", "- Enregistrer la liste des élèves dans un fichier Excel;", " ");
    printf("\n║%79s║", " ");
    printf("\n║%56s%26s║", "3 Accéder au menu de gestion des élèves pour :", " ");
    printf("\n║%33s%48s║", "- Inscrire un élève;", " ");
    printf("\n║%33s%48s║", "- Modifier un élève;", " ");
    printf("\n║%35s%46s║", "- Rechercher un élève;", " ");
    printf("\n║%79s║", " ");
    printf("\n║%29s%50s║", "0 Quitter l'aplication", " ");
    printf("\n║%79s║", " ");
    printf ("\n╚═══════════════════════════════════════════════════════════════════════════════╝\n");
    printf("Choix : ");
    scanf("%d", &choix);
    printf("\n");
}
