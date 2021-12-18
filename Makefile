NAME = pipex

SRCS	= main.c utils.c parsing.c leaks.c \
		init.c pipex.c list.c

OBJS	= ${SRCS:.c=.o}

LIBFT	= libft/libft.a

CFLAGS	= -Wall -Werror -Wextra -g

CC		= clang

RM		= rm -f

all:	${NAME}

$(NAME):	${OBJS}
			make -C libft
			@cp libft/*.h ./includes
			@mv libft/libft.a .
			${CC} ${CFLAGS} ${OBJS} libft.a -o ${NAME}

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(LIBFT):
		make -C libft
		@cp libft/*.h ./includes
		@mv libft/libft.a .

bonus:	all

clean:
		${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}
			make fclean -C libft

re:		fclean all

.PHONY:		all clean fclean re bonus libft