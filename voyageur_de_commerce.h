#ifndef VOYAGEUR_DE_COMMERCE_H
#define VOYAGEUR_DE_COMMERCE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <errno.h>

typedef struct      s_coord
{
    int                 dim;
    double              *a;
    struct s_coord      *next;
}                   coord;

typedef struct		s_opt
{
	char	*path;
	char	debug;
	char	time;
	double	(*algo)(double**, int*, int);
}					t_opt;

#define NAME "voyageur_de_commerce"
#define HELP "Usage: "NAME" [OPTION]... [FILE]...\n"\
"solve the travelling salesman problem for a given set of point.\n\n"\
"-a=[ALGO], select which algorithm should be used (\"all\" for all)\n"\
"-d,        show debug informations\n"\
"-t,        show the time taken by each algorithm\n"\
"-h,        display this help and exit\n\n"\
"Examples:\n"                                       \
"   "NAME" -t -a proximity file           solve the problem for the file \"file\" with the algorithm \"proximity\" and display the time\n"

double  **parse(char *path, int *pts_nbr, t_opt options);
double    call_proximity(double **array, int *current_config, int nbr);
double    call_bb(double **array, int *current_config, int nbr);
double    call_bf(double **array, int *current_config, int nbr);

#endif
