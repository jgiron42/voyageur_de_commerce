#include <sys/wait.h>
#include "voyageur_de_commerce.h"

char	*name_list[] = { "bb", "bf", "bbnn", "nn", "lk", "all", NULL};
char	*full_name_list[] = { "branch and bound", "brute force", "branch and bound with nearest neighbours", "nearest neighbour", "Lin-Kernighan", NULL};
double	(*algo_list[])(double**, int*, int) = {&call_bb, &call_bf, &call_bbnn, &call_nn, &call_lk, NULL, &call_bbnn};

void    call_fonction(double **array, int nbr, t_opt options, double f(double**, int*, int), char *name, coord *list)
{
	int i;
    clock_t start, end;
    double  result;
    double  time;
    double  check_length = 0;
    int     *result_path;

	result_path = calloc(nbr, sizeof(int));
	start = clock();
	result = f(array, result_path, nbr);
	end = clock();
//    result_path[0] = 0;
//    pthread_mutex_lock(&options.protection);

	sem_wait(options.protection);
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
    if (options.time)
    {
		if (time < 1)
			printf("time: %.3lfms\n", time * 1000);
		else if (time < 1000)
			printf("time: %.4lfs\n", time);
		else
			printf("time: %lfs\n", time);
	}
	sem_post(options.protection);
	if (options.graphical)
		render(result_path, list, nbr, name);
	free(result_path);
//	pthread_mutex_unlock(&options.protection);
}

double	(*get_function(char *name))(double**, int*, int)
{
	int		i = -1;
	while (name_list[++i] && !!strcmp(name_list[i], name));
	return (algo_list[i]);
}

t_opt parse_argv(int argc, char **argv)
{
	t_opt	ret = (t_opt){0,0, 0, 0, 0, 0, 0, 0};
	int		c;
	char	*algo_name = strdup("default");
	while ((c = getopt(argc, argv, "gdhlta:r:")) != -1)
	{
		switch (c)
		{
			case 'g':
				ret.graphical = 1;
				break;
			case 'd':
				ret.debug = 1;
				break;
			case 't':
				ret.time = 1;
				break;
			case 'k':
				ret.k = atoi(optarg);
				break;
			case 'r':
				ret.random = atoi(optarg);
				break;
			case 'a':
				free(algo_name);
				algo_name = strdup(optarg);
				break;
			case 'h':
				printf(HELP);
				free(algo_name);
				exit(0);
			case 'l':
				for (int i = 0; full_name_list[i]; i++)
					printf("%s (%s)\n", full_name_list[i], name_list[i]);
				free(algo_name);
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

int main(int argc, char **argv) {
	double **array;
	coord *coords;
	int nbr;
	t_opt options;
	int status = 0;
	pid_t	pid[10];

	bzero(pid, 10 * sizeof(pid_t));
	options = parse_argv(argc, argv);
    if (!options.path && !options.random)
	{
    	fprintf(stderr, "Missing argument\n");
    	return (1);
	}
	sem_unlink(NAME);
	options.protection = sem_open(NAME, O_CREAT | O_EXCL, 0644, 1);
	array = options.random ? random_set(options, &nbr, &coords)
						   : parse(options.path, &nbr, options, &coords);
	if (!options.algo)
	{
    	int i = -1;
		while (full_name_list[++i])
		{
				if (algo_list[i] && !(pid[i] = fork())) {
					call_fonction(array, nbr, options, algo_list[i], full_name_list[i], coords);
					if (coords)
						free_coord(coords);
					for (int i = 0; i < nbr; i++)
						free(array[i]);
					free(array);
					sem_close(options.protection);
					exit(0);
				}
		}
		for (i = 0; i < nbr; i++)
			waitpid(pid[i], &status, 0);
	}
	else
    	call_fonction(array, nbr, options, options.algo, NULL, coords);
	if (coords)
		free_coord(coords);
	for (int i = 0; i < nbr; i++)
		free(array[i]);
	free(array);
	sem_close(options.protection);
}
