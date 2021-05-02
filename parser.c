#include "TSP.h"

double  spherical_distance(coord p1, coord p2)
{
	if (p1.dim != 2 || p2.dim != 2)
		return (0);
	return (acos(sin(degreesToRadians(p1.a[0])) * sin(degreesToRadians(p2.a[0])) + cos(degreesToRadians(p1.a[0])) * cos(degreesToRadians(p2.a[0])) * cos(degreesToRadians(p2.a[1] - p1.a[1]))));
}

double  distance(coord p1, coord p2)
{
    double  sqr_sum = 0;
    double  tmp;
    int     dim = 0;

    while(dim < p1.dim || dim < p2.dim)
    {
        tmp = (dim < p2.dim ? p2.a[dim] : 0) - (dim < p1.dim ? p1.a[dim] : 0);
        sqr_sum += tmp * tmp;
        dim++;
    }
    return (sqrt(sqr_sum));
}

coord   *parse_line(char *line)
{
    char    *ptr = NULL;
    char    *end = line;
    coord   *ret = malloc(sizeof(coord));
    int     i = -1;

    ret->dim = -1;
    ret->next = 0;
    while (ptr != end)
    {
        ptr = end;
        end = NULL;
        strtod(ptr, &end);
        ret->dim++;
    }
    ret->a = malloc(ret->dim * sizeof(double));
    end = line;
    while (++i < ret->dim)
    {
        ptr = end;
        end = NULL;
        ret->a[i] = strtod(ptr, &end);
    }
    free(line);
    return (ret);
}

void    free_coord(coord *list)
{
    free(list->a);
    if (list->next)
        free_coord(list->next);
    free(list);
}

double  **list_to_array(coord *list, int pts_nbr, t_opt options)
{
	int			i = -1;
	int			j;
	coord		*ptr1 = &(coord){.next = list};
	coord		*ptr2;
	double		**ret = malloc(pts_nbr * sizeof(double *));
	double		max = INT_MIN;
	int			precision = 1;

	while ((ptr1 = ptr1->next))
	{
		i++;
		ret[i] = malloc(pts_nbr * sizeof(double));
		ptr2 = &(coord){.next = list};
		j = -1;
		while ((ptr2 = ptr2->next)) {
			ret[i][++j] = options.spherical ? spherical_distance(*ptr1, *ptr2) :  distance(*ptr1, *ptr2);
			max = ret[i][j] > max ? ret[i][j] : max;
        }
    }
    while (max > 9)
	{
    	max /= 10;
    	precision++;
	}
    i = -2;
    while (options.debug && ++i < pts_nbr)
	{
    	j = -1;
    	if (i == -1)
    		printf("%*s ", 3, "");
    	else
			printf("%-3d ", i);
		while (++j < pts_nbr)
		{
			if (i == -1)
    			printf(" %*d ", precision + 2, j);
			else
				printf(" %*.1f ", precision + 2, ret[i][j]);
		}
		printf("\n%s", i + 1 == pts_nbr ? "\n":  "");
	}

	return (ret);
}

double  **parse(char *path, int *pts_nbr, t_opt options, coord **list)
{
    FILE            *file = fopen(path,"r");
    coord           *tmp = &(coord){};
    *list = NULL;
    char            *line = NULL;
    size_t          length = 0;
    *pts_nbr = 0;
	if (!file)
	{
		fprintf(stderr,"%s\n", strerror(errno));
		exit(1);
	}
    while (getline(&line, &length, file)  != -1)
    {
        tmp->next = parse_line(line);
        *list = !*list ? tmp->next : *list;
        tmp = tmp->next;
        line = NULL;
        length = 0;
        (*pts_nbr)++;
    }
    free(line);
    fclose(file);
    return (list_to_array(*list, *pts_nbr, options));
}

double	**random_set(t_opt options, int *nbr, coord **list)
{
	coord   *tmp = &(coord){};
	coord   *tmp2;
	int		x;
	int		y;
	char	line[30];

	*list = NULL;
	srand(time(NULL));
	*nbr = options.random;
	for (int i = 0; i < options.random; i++)
	{
		new_point:;
		x = rand() % 100;
		y = rand() % 100;
		tmp2 = *list;
		while (tmp2)
		{
			if (tmp2->a[0] == x && tmp2->a[1] == y)
				goto new_point;
			tmp2 = tmp2->next;
		}
		bzero(line, 30);
		snprintf(line, 30,"%d %d\n",x, y);
		if (options.debug)
			printf("%d %d\n",x, y);
		tmp->next = parse_line(strdup(line));
		*list = !*list ? tmp->next : *list;
		tmp = tmp->next;
	}
	return (list_to_array(*list, *nbr, options));
}
