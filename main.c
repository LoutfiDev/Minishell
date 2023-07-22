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

int	main(int ac, char **av, char **env)
{
	t_mask	*tree;
	t_list	*buffer;
	t_list	*_env;

	(void) ac;
	(void) av;
	_env = create_env(env);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, sig_handler);
		buffer = main_parse(_env);
		if (buffer)
		{
			sh(buffer);
			// tree = build_tree(buffer, _env);
			// execution(tree, _env, env);
			// free_tree(tree);
			// sh(buffer);
			ft_lstclear(&buffer, clear_buffer);
		}
	}
	ft_lstclear(&_env, clear_env);
	return (0);
}
