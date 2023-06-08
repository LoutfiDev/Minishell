all:
	gcc -g -lreadline -lcurses libft/libft.a *.c -o minishell
