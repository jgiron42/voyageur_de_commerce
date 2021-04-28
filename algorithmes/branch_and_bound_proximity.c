#include "../voyageur_de_commerce.h"

void    swap(int *a, int *b)
{
	int swap;

	swap = *a;
	*a = *b;
	*b = swap;
}

void        sort_array_from_ref(int *ret, double *ref, int nbr)
{
	int i = 1;

	while (i < nbr)
		if (ref[ret[i]] < ref[ret[i - 1]])
		{
			swap(ret + i, ret + i - 1);
			i = 1;
		}
		else
			i++;
}

int   **get_proximity(double **array, int nbr)
{
	int **ret = malloc(nbr* sizeof(int *));
	int i = -1;
	int j;

	while (++i < nbr)
	{
		ret[i] = malloc(nbr * sizeof(int));
		j = -1;
		while (++j < nbr)
			ret[i][j] = j;
		sort_array_from_ref(ret[i], array[i], nbr);
		j = -1;
//		while (++j < nbr)
//			printf("%2d ", ret[i][j]);
//		printf("\n");
	}
	return (ret);
}


double travelling_salesman_bbnn(double **array, int i, char *already_visited, int depth, int *current_config, double current_value, double *global_min, int nbr, int **proximity_array, int *function_call)
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
		if (!already_visited[proximity_array[i][j]])
		{
			tmp = array[i][proximity_array[i][j]] + travelling_salesman_bbnn(array, proximity_array[i][j], already_visited, depth + 1, current_config, array[i][proximity_array[i][j]] + current_value, global_min, nbr, proximity_array, function_call);
			if (tmp < min)
			{
				min = tmp;
				if (depth == 0)
					*global_min = min;
				current_config[depth + 1] = proximity_array[i][j];
				memcpy(min_config, current_config, nbr * sizeof(int));
			}
		}
	}
	already_visited[i] = 0;
	memcpy(current_config, min_config,nbr * sizeof(int));
	return (tmp == -1 ? array[i][0] : min);
}

double    call_bbnn(double **array, int *current_config, int nbr)
{
	double result;
	int  **proximity_array;
	char    *already_visited;
	int		function_call = 0;
	double  global_min = HUGE_VAL;

	proximity_array = get_proximity(array, nbr);
	already_visited = calloc (nbr, 1);
	already_visited[0] = 1;
	current_config[0] = 0;
	result = travelling_salesman_bbnn(array, 0, already_visited, 0, current_config, 0, &global_min, nbr, proximity_array, &function_call);
//	printf("\nfunction call number: %d\n", function_call);
	current_config[0] = 0;
	for (int i = 0; i < nbr; i++)
		free(proximity_array[i]);
	free(proximity_array);
	free(already_visited);
	return result;
}