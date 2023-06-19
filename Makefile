all:
	make -C libft bonus
	gcc -g -lreadline -lcurses libft/libft.a *.c -o minishell
