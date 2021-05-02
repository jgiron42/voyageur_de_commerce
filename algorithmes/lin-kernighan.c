#include "../TSP.h"
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

double		lk(double **array, int *current_config, int nbr, int i, int t1, int t2im1, double current_cost, double new_cost)
{
	for (int t2ip1 = 0; t2ip1 < nbr; t2ip1++) {
		if (array[t2im1 + 1][t2ip1] + new_cost < current_cost) {    //do flip
			i++; //step 5
			if (i == nbr - 1)
				return (HUGE_VAL);
			for (int j = 0; j < nbr; j++) {
				if (i - j <= 1 && i - j >= -1)
					continue;
				if (array[A][B] > array[A][C]) {
					// lk()
				}
			}
		}
	}
}


double    call_lk(double **array, int *T, int nbr)
{
	double ret = call_nn(array, current_config, nbr);

	for (int t1 = 0; t1 < nbr; t1++) {
		lk(array, T, nbr, 1, t1, t1, edge_length(array, nbr, t1), 0);
	}
	return (ret);
}

