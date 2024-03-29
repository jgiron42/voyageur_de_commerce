#include "../TSP.h"

double travelling_salesman_bb(double **array, int i, char *already_visited, int depth, int *current_config, double current_value, double *global_min, int nbr, int *function_call)
{
	int j = -1;
	double tmp = -1;
	double min = HUGE_VAL;
	int     min_config[nbr];
	(*function_call)++;
	if (current_value > *global_min)
		return (current_value);
	already_visited[i] = 1;
	while (++j < nbr)
	{
		if (!already_visited[j])
		{
			tmp = array[i][j] + travelling_salesman_bb(array, j, already_visited, depth + 1, current_config, array[i][j] + current_value, global_min, nbr, function_call);
			if (tmp < min)
			{
				min = tmp;
				if (depth == 0)
					*global_min = min;
				current_config[depth + 1] = j;
				memcpy(min_config, current_config, nbr * sizeof(int));
			}
		}
	}
	already_visited[i] = 0;
	memcpy(current_config, min_config,nbr * sizeof(int));
	return (tmp == -1 ? array[i][0] : min);
}


double    call_bb(double **array, int *current_config, int nbr)
{
	double result;
	char    *already_visited;
	int		function_call = 0;
	double  global_min = HUGE_VAL;

	already_visited = calloc (nbr, 1);
	already_visited[0] = 1;
	current_config[0] = 0;
	result = travelling_salesman_bb(array, 0, already_visited, 0, current_config, 0, &global_min, nbr, &function_call);
	current_config[0] = 0;
	free(already_visited);
//	printf("\nfunction call number: %d\n", function_call);
	return result;
}