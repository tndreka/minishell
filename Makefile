CC = cc

CFLAGS = -Wall -Wextra -Werror -g

LIBFTDIR = libft/

NAME = minishell

SRC = shell_main.c init.c enviroment.c start_shell.c prompt.c

INCLUDE = -L ./libft -lft 

OBJS = ${SRC:.c=.o}

LIBS =-lreadline

all: ${NAME}

${NAME}: ${OBJS}
	@make -sC ${LIBFTDIR}
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${INCLUDE} ${LIBS} -g

clean:

	@rm -f ${OBJS}
	@cd ${LIBFTDIR} && ${MAKE} clean

fclean:

	${MAKE} clean
	@rm -f ${NAME}
	@cd ${LIBFTDIR} && ${MAKE} fclean

re: fclean all

.PHONY: all clean fclean re