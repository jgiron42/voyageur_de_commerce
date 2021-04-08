#include <sys/wait.h>
#include "voyageur_de_commerce.h"

char	*name_list[] = { "bb", "bf", "proximity", "all", NULL};
char	*full_name_list[] = { "branch and bound", "brute force", "branch and bound with nearest neighbours", NULL};
double	(*algo_list[])(double**, int*, int) = {&call_bb, &call_bf, &call_bbnn, NULL, &call_bbnn};

void    call_fonction(double **array, int nbr, t_opt options, double f(double**, int*, int), char *name)
{
    int     i = 0;
    clock_t start, end;
    double  result;
    double  time;
    double  check_length = 0;
    int     *result_path;

    result_path = calloc(nbr, sizeof(int));
    start = clock();
    result = f(array, result_path, nbr);
    end = clock();
    result_path[0] = 0;
    pthread_mutex_lock(&options.protection);
    if (name)
		printf("\n%s:\n",name);
    if (options.debug)
		printf("pid: %d\n", getpid());
    printf("path: ");
    i = -1;
    while (++i < nbr)
    {
        printf("%d ", result_path[i]);
        check_length += array[result_path[i]][result_path[i == nbr - 1 ? 0 : i + 1]];
    }
    printf("\n");
    if (options.debug)
        printf("length: %lf\ncheck length: %lf\n", result, check_length);
    time = ((double) (end - start)) / CLOCKS_PER_SEC;
    if (options.time) {
		if (time < 1)
			printf("time: %.3lfms\n", time * 1000);
		else if (time < 1000)
			printf("time: %.4lfs\n", time);
		else
			printf("time: %lfs\n", time);
	}
	pthread_mutex_unlock(&options.protection);
}

double	(*get_function(char *name))(double**, int*, int)
{
	int		i = -1;
	while (name_list[++i] && !!strcmp(name_list[i], name));
	return (algo_list[i]);
}

t_opt parse_argv(int argc, char **argv)
{
	t_opt	ret = (t_opt){0,0, 0, 0, {{0}}};
	int		c;
	char	*algo_name = strdup("default");
	while ((c = getopt(argc, argv, "dhta:")) != -1)
	{
		switch (c)
		{
			case 'd':
				ret.debug = 1;
				break;
			case 't':
				ret.time = 1;
				break;
			case 'a':
				free(algo_name);
				algo_name = strdup(optarg);
				break;
			case 'h':
				printf(HELP);
				exit(0);
			case '?':
				exit (1);
			default:
				exit (1);
		}
	}
	if (optind < argc)
		ret.path = argv[optind++];
	ret.algo = get_function(algo_name);
	free(algo_name);
	return (ret);
}

int main(int argc, char **argv)
{
    double  **array;
    int     nbr;
    t_opt 	options;
    int status;

    options = parse_argv(argc, argv);
    if (!options.path)
	{
    	fprintf(stderr, "Missing argument\n");
    	return (1);
	}
    pthread_mutex_init(&options.protection, NULL);
    array = parse(options.path, &nbr, options);
    if (!options.algo)
	{
    	int i = -1;
		while (full_name_list[++i])
		{
				if (algo_list[i] && !fork()) {
					call_fonction(array, nbr, options, algo_list[i], full_name_list[i]);
					exit(0);
				}
		}
		while ((wait(&status)) > 0);
	}
    else
		call_fonction(array, nbr, options, options.algo, NULL);
}
