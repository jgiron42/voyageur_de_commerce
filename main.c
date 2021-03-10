#include "voyageur_de_commerce.h"

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
//        j = -1;
//        while (++j < nbr)
//            printf("%lf ", array[i][ret[i][j]]);
//        printf("\n");
    }
    return (ret);
}

double travelling_salesman_proximity(double **array, int i, char *already_visited, int depth, int *current_config, double current_value, double *global_min, int nbr, int **proximity_array)
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
        if (!already_visited[proximity_array[i][j]])
        {
            tmp = array[i][proximity_array[i][j]] + travelling_salesman_proximity(array, proximity_array[i][j], already_visited, depth + 1, current_config, array[i][proximity_array[i][j]] + current_value, global_min, nbr, proximity_array);
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

double travelling_salesman_bb(double **array, int i, char *already_visited, int depth, int *current_config, double current_value, double *global_min, int nbr)
{
    int j = -1;
    double tmp = -1;
    double min = HUGE_VAL;
    int     min_config[nbr];
    if (current_value > *global_min)
        return (current_value);
    already_visited[i] = 1;
    while (++j < nbr)
    {
        if (!already_visited[j])
        {
            tmp = array[i][j] + travelling_salesman_bb(array, j, already_visited, depth + 1, current_config, array[i][j] + current_value, global_min, nbr);
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


double    call_proximity(double **array, int *current_config, int nbr)
{
    double result;
    int  **proximity_array;
    char    *already_visited;

    double  global_min = HUGE_VAL;

    proximity_array = get_proximity(array, nbr);
    already_visited = calloc (nbr, 1);
    already_visited[0] = 1;
    current_config[0] = 0;
    result = travelling_salesman_proximity(array, 0, already_visited, 0, current_config, 0, &global_min, nbr, proximity_array);
    return result;
}
double    call_bf(double **array, int *current_config, int nbr)
{
    double result;
    int  **proximity_array;
    char    *already_visited;

    double  global_min = HUGE_VAL;

    already_visited = calloc (nbr, 1);
    already_visited[0] = 1;
    current_config[0] = 0;
    result = travelling_salesman_bf(array, 0, already_visited, 0, current_config, 0, &global_min, nbr);
    return result;
}
double    call_bb(double **array, int *current_config, int nbr)
{
    double result;
    int  **proximity_array;
    char    *already_visited;

    double  global_min = HUGE_VAL;

    already_visited = calloc (nbr, 1);
    already_visited[0] = 1;
    current_config[0] = 0;
    result = travelling_salesman_bb(array, 0, already_visited, 0, current_config, 0, &global_min, nbr);
    return result;
}
void    execute_fonction(double **array, int nbr, int debug, double f(double**, int*, int))
{
    int     i = 0;
    clock_t start, end;
    double  result;
    double  time;
    double  check_length = 0;
    int     *result_path;

    result_path = calloc (nbr, sizeof(int));
    start = clock();
    result = f(array, result_path, nbr);
    end = clock();
    result_path[0] = 0;
    printf("path: ");
    i = -1;
    while (++i < nbr)
    {
        printf("%d ", result_path[i]);
        check_length += array[i][i == nbr - 1 ? 0 : i + 1];
    }
    if (debug)
        printf("\nlength: %lf\ncheck length: %lf\n", result, check_length);
    time = ((double) (end - start)) / CLOCKS_PER_SEC;
    if (time < 1)
        printf("time: %.3lfms\n", time * 1000);
    else if (time < 1000)
        printf("time: %.4lfs\n", time);
    else
        printf("time: %lfs\n", time);

}

int main(int argc, char **argv) {
    char    *path = NULL;
    double  **array;
    int     debug = 0;
    int     i = -1;
    int     nbr;

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
    array = parse(path, &nbr, debug);
	printf("brute force:\n");
	execute_fonction(array, nbr, debug, &call_bf);
    printf("\nwithout proximity:\n");
    execute_fonction(array, nbr, debug, &call_bb);
    printf("\nwith proximity:\n");
    execute_fonction(array, nbr, debug, &call_proximity);
}
