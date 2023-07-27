/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:02:16 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/26 21:36:43 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/buffer.h"
#include "includes/exec.h"
#include "includes/parsing.h"
#include "includes/struct.h"
#include "libft/libft.h"
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include <unistd.h>

int	nbr_keys(t_list *env)
{
	int		nbr;
	t_list	*tmp;

	nbr = 0;
	tmp = env;
	while (tmp)
	{
		nbr++;
		tmp = tmp->next;
	}
	return (nbr);
}

char	**shared_env(t_list *env)
{
	char	**envp;
	t_list	*tmp_env;
	t_env	*env_node;
	char	*tmp;
	int		i;

	i = nbr_keys(env);
	envp = malloc (sizeof(char *) * (i + 1));
	tmp_env = env;
	i = 0;
	while (tmp_env)
	{
		env_node = (t_env *)tmp_env->content;
		tmp = ft_strjoin(ft_strdup(env_node->key), ft_strdup("="));
		envp[i++] = ft_strjoin(tmp, ft_strdup(env_node->value));
		tmp_env = tmp_env->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	main(int ac, char **av, char **env)
{
	t_mask	*tree;
	t_list	*buffer;
	t_list	*_env;
	char	**envp;

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
			envp = shared_env(_env);
			tree = build_tree(buffer, _env);
			execution(tree, &_env, env);
			ft_free_array(envp, 0);
			free_tree(tree);
			ft_lstclear(&buffer, clear_buffer);
		}
	}
	ft_lstclear(&_env, clear_env);
	return (0);
}
