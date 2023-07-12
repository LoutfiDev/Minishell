/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:40:55 by anaji             #+#    #+#             */
/*   Updated: 2023/07/11 22:49:39 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <sys/_types/_null.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include "includes/buffer.h"
#include "includes/parsing.h"
#include "includes/exec.h"
#include <errno.h>

int	main(int ac, char **av, char **env)
{
	t_mask	*tree;
	t_list	*buffer;
	t_list	*_env;
	
	_env = create_env(env);
	while (1)
	{
		buffer = main_parse(_env);
		// if (fork() == 0)
		// {
			tree = build_tree(buffer);
			execution(tree, _env);
			free_tree(tree);
		// }
		// wait(0);
		ft_lstclear(&buffer, clear_buffer);
	}
	ft_lstclear(&_env, clear_env);
	return (0);
}
