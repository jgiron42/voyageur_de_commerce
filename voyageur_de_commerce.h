#ifndef VOYAGEUR_DE_COMMERCE_H
#define VOYAGEUR_DE_COMMERCE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include <time.h>


typedef struct      s_coord
{
    int                 dim;
    double              *a;
    struct s_coord      *next;
}                   coord;

double  **parse(char *path, int *pts_nbr, int flag);
double    call_proximity(double **array, int *current_config, int nbr);
double    call_bb(double **array, int *current_config, int nbr);
double    call_bf(double **array, int *current_config, int nbr);

#endif
