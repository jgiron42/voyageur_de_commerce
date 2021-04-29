
#include "../voyageur_de_commerce.h"
#define A (current_config[i])
#define B (i + 1 == nbr ? current_config[0] : current_config[i + 1])
#define C (current_config[j])
#define D (j + 1 == nbr ? current_config[0] : current_config[j + 1])

void swap_edges(int *current_config, int nbr, int i, int j) {
	int	direction = 1;
	int		l;
	int		tmp_config[nbr];

	l = j == nbr - 1 || i == nbr - 1;
	for (int k = 0; k < nbr; k++)
	{
		if (current_config[l] == A || current_config[l] == B || current_config[l] == C || current_config[l] == D)
		{
			tmp_config[k] = current_config[l];
			k++;
			if (k >= nbr)
				break;
			l = i 								* (current_config[l] == C) +
				(i + 1 == nbr ? 0 : i + 1) 		* (current_config[l] == D) +
				j								* (current_config[l] == A) +
				(j + 1 == nbr ? 0 : j + 1) 		* (current_config[l] == B);
			direction *= -1;
		}
		tmp_config[k] = current_config[l];
		l += direction;
		l = l == -1 ? nbr - 1 : l;
		l = l == nbr ? 0 : l;
	}
	for (int k = 0; k < nbr; k++)
		current_config[k] = tmp_config[k];
}

double edge_length(double **array, int nbr, int edge)
{
	return (array[edge][edge + 1 == nbr ? 0 : edge + 1]);
}

double    call_lk(double **array, int *current_config, int nbr)
{
	double ret = call_nn(array, current_config, nbr);

	for (int i = 0; i < nbr; i++) {
		for (int j = 0; j < nbr; j++)
		{
			if (i - j <= 1 && i - j >= -1)
				continue;
			if (array[A][B] + array[C][D] > array[A][C] + array[B][D])
			{
				swap_edges(current_config, nbr, i, j);
				i = 0;
				break ;
			}
		}
	}
	return (ret);
}

