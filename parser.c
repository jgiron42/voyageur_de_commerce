#include "voyageur_de_commerce.h"


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

double  **list_to_array(coord *list, int pts_nbr)
{
    int             i = -1;
    int             j;
    coord           *ptr1 = &(coord){.next = list};
    coord           *ptr2;
    double          **ret = malloc(pts_nbr * sizeof(double *));

    while ((ptr1 = ptr1->next))
    {
        i++;
        ret[i] = malloc(pts_nbr * sizeof(double));
        ptr2 = &(coord){.next = list};
        j = -1;
        while ((ptr2 = ptr2->next))
        {
            ret[i][++j] = distance(*ptr1, *ptr2);
            printf(" %4.1f ", ret[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    if (list)
        free_coord(list);
    return (ret);
}

double  **parse(char *path)
{
    FILE            *file = fopen(path,"r");
    coord           *tmp = &(coord){};
    coord           *list = NULL;
    char            *line = NULL;
    size_t          length = 0;
    int             pts_nbr = 0;

    while (getline(&line, &length, file)  != -1)
    {
        tmp->next = parse_line(line);
        list = !list ? tmp->next : list;
        tmp = tmp->next;
        line = NULL;
        length = 0;
        pts_nbr++;
    }
    nbr = pts_nbr;
    return (list_to_array(list, pts_nbr));
}
