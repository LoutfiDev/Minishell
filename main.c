/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:40:55 by anaji             #+#    #+#             */
/*   Updated: 2023/07/15 07:32:58 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
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

int	main(int ac, char **av, char **env)
{
	t_mask	*tree;
	t_list	*buffer;
	t_list	*_env;

	(void) ac;
	(void) av;
	_env = create_env(env);
	while (1)
	{
		buffer = main_parse(_env);
		if (fork() == 0)
		{
			tree = build_tree(buffer);
			execution(tree, _env);
			free_tree(tree);
		}
		wait(0);
		ft_lstclear(&buffer, clear_buffer);
	}
	ft_lstclear(&_env, clear_env);
	return (0);
}
