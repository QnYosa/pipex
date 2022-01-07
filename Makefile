NAME = pipex

NAME_BNS = pipex_bonus

LIBFT	= libft/libft.a

SRCS	= main.c utils.c parsing.c leaks.c \
		init.c pipex.c list.c get_path.c \

BONUS	= bonus/pipex_bonus.c bonus/main_bonus.c \
		bonus/parsing_bonus.c bonus/list_bonus.c \
		bonus/leaks_bonus.c bonus/init_bonus.c \
		bonus/utils_bonus.c bonus/hdc_or_not_bonus.c \

OBJS	= ${SRCS:.c=.o}

O_BNS	= ${BONUS:.c=.o}


CFLAGS	= -Wall -Werror -Wextra

CC		= clang

RM		= rm -f

all:	$(NAME)
bonus:	$(NAME_BNS)

$(NAME_BNS):	${O_BNS}
			make -C libft
			@cp libft/*.h ./includes
			@mv libft/libft.a .
			${CC} ${CFLAGS} ${O_BNS} libft.a -o ${NAME_BNS}

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

clean:
		${RM} ${OBJS}
		${RM} ${O_BNS}

fclean:		clean
			${RM} ${NAME}
			${RM} ${NAME_BNS}
			make fclean -C libft
			rm libft.a

re:		fclean all

.PHONY:		all clean fclean re bonus libft bonus