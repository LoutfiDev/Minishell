# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anaji <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/17 10:44:25 by yloutfi           #+#    #+#              #
#    Updated: 2023/07/14 20:42:27 by anaji            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
CFLAGS = -fsanitize=address -g
DFLAGS = -Llibft -lft
RDLFLAGS = -lreadline -lcurses
CC = gcc -g #cc

SRCS = ./execution/build_tree.c ./execution/execution.c

HELPERS = ./execution/helpers.c ./execution/split.c ./execution/ft_argsjoin.c \
		./execution/ft_free.c

BUILTINS = ./execution/builtins/echo.c ./execution/builtins/pwd.c	\
		./execution/builtins/cd.c ./execution/builtins/export.c		\
		./execution/builtins/unset.c ./execution/builtins/env.c		\
		./execution/builtins/exit.c

OBJS = exec_test.o ./execution/build_tree.o ./execution/execution.o

OBJS_HELPERS = ./execution/helpers.o ./execution/split.o ./execution/ft_argsjoin.o \
		./execution/ft_free.o

OBJS_BUILTINS = ./execution/builtins/echo.o ./execution/builtins/pwd.o	\
		./execution/builtins/cd.o ./execution/builtins/export.o			\
		./execution/builtins/unset.o ./execution/builtins/env.o			\
		./execution/builtins/exit.o

# all: libft $(NAME)
all: libft
	$(CC) parser/*.c $(SRCS) $(HELPERS) main.c $(CFLAGS) $(RDLFLAGS) $(DFLAGS) -o minishell

libft:
	@$(MAKE) -C libft -s
	@$(MAKE) -C libft bonus -s

$(NAME): $(OBJS) $(OBJS_HELPERS) $(OBJS_BUILTINS)
	$(CC) $(CFLAGS) $(DFLAGS) $(RDLFLAGS) $(OBJS_HELPERS) $(OBJS_BUILTINS) $(OBJS) -o $(NAME)

clean:
	@$(MAKE) -C libft clean -s
	-rm -f $(OBJS) $(OBJS_HELPERS) $(OBJS_BUILTINS)

fclean: clean
	@$(MAKE) -C libft fclean -s
	-rm -f $(NAME)

re: fclean all

.PHONY : all libft bonus clean fclean re
