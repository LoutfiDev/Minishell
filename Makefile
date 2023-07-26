# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anaji <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/26 15:17:20 by yloutfi           #+#    #+#              #
#    Updated: 2023/07/26 16:21:28 by anaji            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
DFLAGS = -Llibft -lft -L$(HOME)/Desktop/rdln
RDLFLAGS = -lreadline -lcurses
CC = cc

MAIN_SRCS = ./main.c

PARSE_SRCS = ./parser/creat_env.c ./parser/expand.c ./parser/expanding_utils.c \
			 ./parser/expanding_utils_2.c ./parser/expanding_utils_3.c \
			./parser/ft_check_redirection.c ./parser/ft_exit.c ./parser/ft_list_utils.c \
			 ./parser/handle_quote.c ./parser/here_doc.c ./parser/here_doc_utils.c \
			 ./parser/open_file.c ./parser/parse.c ./parser/parsing_utils.c \
			 ./parser/utils.c

EXEC_SRCS = ./execution/build_tree.c ./execution/execution.c ./execution/exec.c \
	./execution/pipe.c

EXEC_HELPERS = ./execution/helpers.c ./execution/split.c ./execution/ft_argsjoin.c \
		./execution/ft_free.c ./execution/signals.c ./execution/expand_exit.c

EXEC_BUILTINS = ./execution/builtins/echo.c ./execution/builtins/pwd.c	\
		./execution/builtins/cd.c ./execution/builtins/export.c		\
		./execution/builtins/unset.c ./execution/builtins/env.c		\
		./execution/builtins/exit.c ./execution/builtins/exec_builtins.c

MAIN_OBJS = ./main.o

PARSE_OBJS = ${PARSE_SRCS:.c=.o}

EXEC_OBJS = ./execution/build_tree.o ./execution/execution.o ./execution/exec.o \
	./execution/pipe.o

EXEC_OBJS_HELPERS = ./execution/helpers.o ./execution/split.o ./execution/ft_argsjoin.o \
		./execution/ft_free.o ./execution/signals.o ./execution/expand_exit.o

EXEC_OBJS_BUILTINS = ./execution/builtins/echo.o ./execution/builtins/pwd.o	\
		./execution/builtins/cd.o ./execution/builtins/export.o			\
		./execution/builtins/unset.o ./execution/builtins/env.o			\
		./execution/builtins/exit.o ./execution/builtins/exec_builtins.o

all: libft $(NAME)
	@stty -echoctl

libft:
	@$(MAKE) -C libft -s
	@$(MAKE) -C libft bonus -s

$(NAME): $(MAIN_OBJS) $(EXEC_OBJS) $(EXEC_OBJS_HELPERS) $(EXEC_OBJS_BUILTINS) $(PARSE_OBJS)
	$(CC) $(CFLAGS) $(DFLAGS) $(RDLFLAGS) $(OBJS_HELPERS) $(OBJS_BUILTINS) $(EXEC_OBJS) $(MAIN_OBJS) $(PARSE_OBJS) -o $(NAME)

clean:
	@$(MAKE) -C libft clean -s
	-rm -f $(EXEC_OBJS) $(EXEC_OBJS_HELPERS) $(EXEC_OBJS_BUILTINS)

fclean: clean
	@$(MAKE) -C libft fclean -s
	-rm -f $(NAME)

re: fclean all

.PHONY : all libft bonus clean fclean re
