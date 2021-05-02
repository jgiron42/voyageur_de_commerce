
#include "TSP.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	char			*j;
	char			*tab;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (strdup((char *)s2));
	if (!s2)
		return (strdup((char *)s1));
	i = strlen(s1) + strlen(s2);
	if (!(tab = malloc((i + 1) * (sizeof(char)))))
		exit(1);
	j = tab;
	while (*s1 != '\0')
		*j++ = *s1++;
	while (*s2 != '\0')
		*j++ = *s2++;
	*j = '\0';
	return (tab);
}

char			*ft_strjoindf(char const *s1, char const *s2)
{
	char *ret = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (ret);
}


//void	put_text(SDL_Renderer *renderer, char *text, int x, int y)
//{
//	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);
//	SDL_Color White = {255, 255, 255};
//	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text, White);
//	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
//	SDL_Rect Message_rect;
//	Message_rect.x = 200;
//	Message_rect.y = 200;
//	Message_rect.w = 30;
//	Message_rect.h = 30;
//	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
//	SDL_FreeSurface(surfaceMessage);
//	SDL_DestroyTexture(Message);
//}

int get_scale(int winx, int winy, vect *pos, mat2_2 *app, coord *list)
{
	double xmax = -HUGE_VAL;
	double xmin = HUGE_VAL;
	double ymax = -HUGE_VAL;
	double ymin = HUGE_VAL;
	while (list)
	{
		if (list->dim != 2)
			return (-1);
		xmax = list->a[0] > xmax ? list->a[0] : xmax;
		ymax = list->a[1] > ymax ? list->a[1] : ymax;
		xmin = list->a[0] < xmin ? list->a[0] : xmin;
		ymin = list->a[1] < ymin ? list->a[1] : ymin;
		list = list->next;
	}
	winx = (winx * 9) / 10;
	winy = (winy * 9) / 10;
	pos->x = xmin;
	pos->y = ymin;
	app->a = (winx / (xmax - xmin));
	app->d = (winy / (ymax - ymin));
}

vect	get_pt_pos(coord *list, int index)
{
	return (index == 0 ? (vect){list->a[0], list->a[1]} : get_pt_pos(list->next, index - 1));
}

void	render(int *result, coord *list, int pts_nbr, char *name, t_opt options)
{
	SDL_Event events;
	vect	pos;
	mat2_2	app;
	char *title;

	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		exit(1);
	SDL_Window *win = SDL_CreateWindow(title = ft_strjoin(NAME " - " , name), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, options.win_x, options.win_y, 0);
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	get_scale(options.win_x, options.win_y, &pos, &app, list);
	for (int i = 0; i < pts_nbr; i++)
	{
		vect p1 = get_pt_pos(list, result[i]);
		vect p2 = get_pt_pos(list, result[(i + 1) == pts_nbr ? 0 : i + 1]);
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderDrawLine(ren, (int)((p1.x - pos.x) * app.a) + options.win_x / 20, (int)((p1.y - pos.y) * app.d) + options.win_y  / 20,
		(int)((p2.x - pos.x) * app.a) + options.win_x / 20, (int)((p2.y - pos.y) * app.d) + options.win_y / 20);
//		put_text(ren, "test", (int)((p1.x - pos.x) * app.a) - DEFAULT_WIN_X / 20, (int)((p1.y - pos.y) * app.d) - DEFAULT_WIN_Y  / 20);
		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		SDL_RenderDrawPoint(ren, (int)((p1.x - pos.x) * app.a) + options.win_x / 20, (int)((p1.y - pos.y) * app.d) + options.win_y / 20);
	}
	SDL_RenderPresent(ren);
	while (1)
		if (SDL_PollEvent(&events) && events.type == SDL_WINDOWEVENT && events.window.event == SDL_WINDOWEVENT_CLOSE)
			break;
	free(title);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
