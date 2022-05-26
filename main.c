#include "ecole.h"

int main (int n, char *nom_fichier[])

{
    ecole_t MonEcole;

    VerificationInfosEcole(&MonEcole,nom_fichier[1]);
    MenuApp(&MonEcole,0);
}
