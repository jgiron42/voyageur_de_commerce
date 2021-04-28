NAME    =   voyageur_de_commerce

SRCS    =   main.c \
            parser.c \
            algorithmes/branch_and_bound_proximity.c \
            algorithmes/branch_and_bound.c \
            algorithmes/brute_force.c \
            algorithmes/lin-kernighan.c \
            algorithmes/nearest_neighbour.c \
	    render.c \

OBJS    =   ${SRCS:.c=.o}

CFLAGS  =   -Wall -Wextra -Werror -O3 -Wno-alloc-size-larger-than -w -lSDL2 -pthread

LIBS    =   -lm

CC      =   gcc

.c.o:
	$(CC) ${CFLAGS} -c $< -o $(<:.c=.o)

all:		${NAME}

${NAME}:	${OBJS}
			${CC} -o ${NAME} ${OBJS} $(LIBS) ${CFLAGS}

clean :
			rm -f ${OBJS}

fclean :	clean
			rm -f ${NAME}

re :		fclean all
