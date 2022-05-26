#include "date.h"

void AfficherDate (time_t date_naissance)
{
    char date[200];
  
    strftime(date, 200, "%d/%m/%G", localtime(&date_naissance));//date

    printf("%20s\n",date);
}

/*
double CalculerDate (time_t date_naissance)
{
    double age = 0;
    time_t today;
    char date[200];

    today = time(NULL);
  
    strftime(date, 200, "%d/%m/%G", localtime(&today));
    age = difftime(today, date_naissance);
    age = age/24.0/60.0/60.0/365.0;

return (age);
}
*/

void JusteDate (time_t *D)
{
    /*struct tm tmp_date2;
    time_t tmp_date;
    int age=0;
    int annee_naissance=0;
    double diff=0;
    char annee[200];
    char jour[10];
    char mois[10];
    char an[10];*/

    printf("Modifier la date de naissance de l'eleve (jj/mm/aaaa) : ");
    SaisirDate(D);

    /*strftime(annee, 200, "%G", localtime(&tmp_date)); //On récupère l'année de naissance sous forme de string dans annee
    annee_naissance=atoi(annee); //On convertit en entier et on stocke dans annee_naissance

    age=2021-annee_naissance;

    if(age<6 && age>10)
    printf("\nCet élève n'a pas sa place dans une école primaire.\n");
        else
        {
        strftime(jour,10, "%d", localtime(&tmp_date));
        strftime(mois,10, "%m", localtime(&tmp_date));
        strftime(an,10, "%G", localtime(&tmp_date));

        memset(&tmp_date2,0,sizeof(tmp_date2));

        tmp_date2.tm_mday=atoi(jour);
        tmp_date2.tm_mon=atoi(mois);
        tmp_date2.tm_year=atoi(an);

        tmp_date2.tm_mon = tmp_date2.tm_mon-1;
        tmp_date2.tm_year = tmp_date2.tm_year-1900;

        *D=mktime(&tmp_date2);
        }


    AfficherDate (*D);*/
}

int SaisirDate (time_t *date_naissance)
{
    struct tm date_eleve;
    memset(&date_eleve,0,sizeof(date_eleve));

    scanf("%d/%d/%d", &date_eleve.tm_mday, &date_eleve.tm_mon, &date_eleve.tm_year);

    date_eleve.tm_mon = date_eleve.tm_mon-1;
    date_eleve.tm_year = date_eleve.tm_year-1900;

    *date_naissance=mktime(&date_eleve);
}
