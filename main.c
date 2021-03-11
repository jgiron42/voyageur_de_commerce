#include "voyageur_de_commerce.h"

void    call_fonction(double **array, int nbr, int debug, double f(double**, int*, int))
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
	call_fonction(array, nbr, debug, &call_bf);
    printf("\nwithout proximity:\n");
	call_fonction(array, nbr, debug, &call_bb);
    printf("\nwith proximity:\n");
	call_fonction(array, nbr, debug, &call_proximity);
}
