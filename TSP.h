#ifndef VOYAGEUR_DE_COMMERCE_H
#define VOYAGEUR_DE_COMMERCE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <limits.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>

#define _OPEN_THREADS

typedef struct      s_coord
{
    int                 dim;
    double              *a;
    struct s_coord      *next;
}                   coord;

typedef struct      s_vect {
	double x;
	double y;
}                   vect;

typedef struct      s_mat2_2 {
	double a;
	double b;
	double c;
	double d;
}                   mat2_2;

typedef struct		s_opt
{
	char			*path;
	char			debug;
	char			graphical;
	char			time;
	double			(*algo)(double**, int*, int);
	int				k;
	int				spherical;
	int				random;
	int				win_x;
	int				win_y;
	sem_t			protection;
}					t_opt;

#define NAME "TSP"
#define HELP "Usage: "NAME" [OPTION]... [FILE]...\n"\
"solve the travelling salesman problem for a given set of point.\n\n"\
"-a [ALGO], select which algorithm should be used (\"all\" for all)\n"\
"-d,        show debug information\n"\
"-g,        display a graphical representation of the solution \n"\
"-h,        display this help and exit\n"\
"-l,        display a list of all algorithm available\n"\
"-r [N],    solve the problem with a random set of N points \n"\
"-s,        tell the program to consider input coordinates as spherical coordinates\n"\
"-t,        show the time taken by each algorithm\n"\
"-w [X:Y],  set the window dimension to X Y \n"\
"\nExamples:\n"                                       \
"   "NAME" -t -a nn file           solve the problem for the file \"file\" with the algorithm \"nearest neighbour\" and display the time\n"
#define DEFAULT_WIN_X 500
#define DEFAULT_WIN_Y 500
#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)

double		**parse(char *path, int *pts_nbr, t_opt options, coord **list);
double		**random_set(t_opt options, int *nbr, coord **list);
double		call_bbnn(double **array, int *current_config, int nbr);
double		call_bb(double **array, int *current_config, int nbr);
double		call_bf(double **array, int *current_config, int nbr);
double		call_nn(double **array, int *current_config, int nbr);
//double		call_lk(double **array, int *current_config, int nbr);
double    call_2opt(double **array, int *current_config, int nbr);
double    call_2optnn(double **array, int *current_config, int nbr);
int			**get_proximity(double **array, int nbr);
void        sort_array_from_ref(int *ret, double *ref, int nbr);
void		render(int *result, coord *list, int pts_nbr, char *name, t_opt options);
void		swap(int *a, int *b);
char		*ft_strjoindf(char const *s1, char const *s2);

#endif
