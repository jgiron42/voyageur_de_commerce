NAME    =   voyageur_de_commerce

SRCS    =   main.c \
            parser.c \
            algorithmes/branch_and_bound_proximity.c \
            algorithmes/branch_and_bound.c \
            algorithmes/brute_force.c

OBJS    =   ${SRCS:.c=.o}

CFLAGS  =   -Wall -Wextra -Werror -O3 -Wno-alloc-size-larger-than

LIBS    =   -lm

CC      =   gcc

.c.o:
	$(CC) ${CFLAGS} -c $< -o $(<:.c=.o)

all:		${NAME}

${NAME}:	${OBJS}
			${CC} -o ${NAME} ${OBJS} $(LIBS)

clean :
			rm -f ${OBJS}

fclean :	clean
			rm -f ${NAME}

re :		fclean all