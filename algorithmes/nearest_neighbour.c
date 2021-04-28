#include "../voyageur_de_commerce.h"


double		nn(double **array, int **proximity, int *current_config, int nbr, char *already_visited, int pos, int start, int depth)
{
	int		i = -1;
	double	ret;
	already_visited[pos] = 1;
	while (++i < nbr && (already_visited[proximity[pos][i]] || proximity[pos][i] == start));
	if (depth < nbr)
		current_config[depth] = pos;
	if (depth < nbr && i < nbr)
		ret = array[pos][proximity[pos][i]] + nn(array, proximity, current_config, nbr, already_visited, proximity[pos][i], start, depth + 1);
	else
		ret = array[pos][start];
	return (ret);
}

double    call_nn(double **array, int *current_config, int nbr)
{
	int **sorted = get_proximity(array, nbr);
	int		*already_visited = calloc (nbr , 4);
	double min = HUGE_VAL;
	int min_index = -1;
	double tmp;
	for (int i = 0; i < nbr-1; i++)
	{
		tmp = nn(array, sorted, current_config, nbr, already_visited, i, i, 0);
		if (tmp < min)
		{
			min = tmp;
			min_index = i;
		}
		bzero(already_visited, nbr * 4);
	}
	bzero(current_config, nbr);
	nn(array, sorted, current_config, nbr, already_visited, min_index, min_index, 0);
	free(already_visited);
	for (int i = 0; i < nbr; i++)
		free(sorted[i]);
	free(sorted);
	return (min);
}
