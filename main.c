#include "voyageur_de_commerce.h"

double travelling_salesman(double **array, int i, char *already_visited, int depth, int *current_config, double current_value, double *global_min, int nbr)
{
    int j = -1;
    double tmp = -1;
    double min = HUGE_VAL;
    int     min_config[nbr];
    already_visited[i] = 1;
    if (current_value > *global_min)
        return (current_value);
    while (++j < nbr)
    {
        if (!already_visited[j])
        {
            tmp = array[i][j] + travelling_salesman(array, j, already_visited, depth + 1, current_config, array[i][j] + current_value, global_min, nbr);
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

int main(int argc, char **argv) {
    char    *path = NULL;
    double  global_min = HUGE_VAL;
    int     nbr;
    double  **array;
    char    *already_visited;
    int     *current_config;
    int     i = 0;
    clock_t start, end;
    double  result;
    double  time;
    int     debug = 0;

    while (++i < argc)
    {
        if (!strcmp(argv[i], "-d"))
            debug = 1;
        else
            path = argv[i];
    }
    if (argc < 2 || !path)
    {
        write(2, "Missing argument\n", 17);
        return (1);
    }
    i = -1;
    array = parse(path, &nbr, debug);
    already_visited = calloc (nbr, 1);
    already_visited[0] = 1;
    current_config = calloc (nbr, sizeof(int));
    current_config[0] = 0;
    start = clock();
    result = travelling_salesman(array, 0, already_visited, 0, current_config, 0, &global_min, nbr);
    end = clock();
    current_config[0] = 0;
    printf("path: ");
    while (++i < nbr)
    {
        printf("%d ", current_config[i]);
    }
    printf("\nlength: %lf\n", result);
    time = ((double) (end - start)) / CLOCKS_PER_SEC;
    if (time < 1)
        printf("time: %.3lfms\n", time * 1000);
    else if (time < 1000)
        printf("time: %.4lfs\n", time);
    else
        printf("time: %lfs\n", time);
}
