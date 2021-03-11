#include "../voyageur_de_commerce.h"

double travelling_salesman_bf(double **array, int i, char *already_visited, int depth, int *current_config, double current_value, double *global_min, int nbr)
{
	int j = -1;
	double tmp = -1;
	double min = HUGE_VAL;
	int     min_config[nbr];
	already_visited[i] = 1;
	while (++j < nbr)
	{
		if (!already_visited[j])
		{
			tmp = array[i][j] + travelling_salesman_bf(array, j, already_visited, depth + 1, current_config, array[i][j] + current_value, global_min, nbr);

			if (tmp < min)
			{
				min = tmp;
				current_config[depth + 1] = j;
				memcpy(min_config, current_config, nbr * sizeof(int));
			}
		}
	}
	already_visited[i] = 0;
	memcpy(current_config, min_config,nbr * sizeof(int));
	return (tmp == -1 ? array[i][0] : min);
}

double    call_bf(double **array, int *current_config, int nbr)
{
	double result;
	char    *already_visited;

	double  global_min = HUGE_VAL;

	already_visited = calloc (nbr, 1);
	already_visited[0] = 1;
	current_config[0] = 0;
	result = travelling_salesman_bf(array, 0, already_visited, 0, current_config, 0, &global_min, nbr);
	return result;
}