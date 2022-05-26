#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#ifndef DATE_H
#define DATE_H

void AfficherDate (time_t date_naissance);

//double CalculerDate (time_t date_naissance);

void JusteDate (time_t *D);

int SaisirDate (time_t *date_naissance);

#endif
