#include "voyageur_de_commerce.h"

double travelling_salesman(double **array, int i, char *already_visited, int depth, int *current_config, double current_value)
{
    int j = -1;
    double tmp = -1;
    double min = HUGE_VAL;
    int     min_config[nbr];
    already_visited[i] = 1;
    if (current_value > global_min)
        return (current_value);
    while (++j < nbr)
    {
        if (!already_visited[j])
        {
            tmp = array[i][j] + travelling_salesman(array, j, already_visited, depth + 1, current_config, array[i][j] + current_value);
            if (tmp < min)
            {
                min = tmp;
                if (depth == 0)
                    global_min = min;
                current_config[depth + 1] = j;
                memcpy(min_config, current_config, nbr * sizeof(int));
            }
        }
    }
    already_visited[i] = 0;
    memcpy(current_config, min_config,nbr * sizeof(int));
    return (tmp == -1 ? array[i][0] : min);
}

int main(int argc, char **argv) {
    double  **array;
    char    *already_visited;
    int     *current_config;
    int     i = -1;

    if (argc == 2)
    {
        array = parse(argv[1]);
        already_visited = calloc (nbr, 1);
        already_visited[0] = 1;
        current_config = calloc (nbr, sizeof(int));
        current_config[0] = 0;
        printf("%lf\n", travelling_salesman(array, 0, already_visited, 0, current_config, 0));
        current_config[0] = 0;
        while (++i < nbr)
        {
            printf("%d ", current_config[i]);
        }
    }
}
