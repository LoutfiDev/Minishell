
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include "includes/buffer.h"
#include "includes/parsing.h"
#include "includes/exec.h"
#include "includes/struct.h"
#include "libft/libft.h"
#include <errno.h>

//int	exit_status;
void	printTree(t_mask *node, int space)
{
	t_pipe	*pipe_node;
	t_exec	*exec_node;

	if (!node)
		return ;
	if (node->mask == PIPE_NODE)
	{
		pipe_node = (t_pipe *)node;
		space += 10;
		printTree(pipe_node->left, space);
		printf("\n");
		for (int i = 10; i < space; i++)
			printf(" ");
		printf("%s", "P");
		printTree(pipe_node->right, space);
	}
	else if (node->mask == EXEC_NODE)
	{
		exec_node = (t_exec *)node;
		space += 10;
		printf("\n");
		for (int i = 10; i < space; i++)
			printf(" ");
		printf("%d", exec_node->last);
	}
}

void	sh(t_list *lst)
{

	t_list *tmp;
	t_buffer *bf;

	tmp = lst;
	while (tmp)
	{
		if (tmp -> content)
			bf = (t_buffer *)tmp -> content;
		printf("str = %s type = %d\n",bf->str, bf->type);
		tmp = tmp -> next;
	}
}

void	close_files(t_list *lst)
{
	t_buffer	*bf;

	while (lst)
	{
		bf = lst -> content;
		if (bf -> type > 2 && bf -> type < 7)
			close(ft_atoi(bf -> str));
		lst = lst -> next;
	}
}

void	print_hello(int action)
{
	exit(1);
	printf("\n");
	//printf("CTR-C\n");
}

int	main(int ac, char **av, char **env)
{
	t_mask	*tree;
	t_list	*buffer;
	t_list	*_env;
	char	*line;

	(void) ac;
	(void) av;
	_env = create_env(env);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = NULL;
		buffer = main_parse(_env, &line);
		if (buffer)
		{
			//add_history(line);
			free(line);
			tree = build_tree(buffer, _env);
			// printTree(tree, 0);
			execution(tree, _env, env);
			free_tree(tree);
			// sh(buffer);
			ft_lstclear(&buffer, clear_buffer);
		}
	}
	ft_lstclear(&_env, clear_env);
	return (0);
}

