/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:11:38 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/22 15:00:12 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	export_print(char *key, char *value, int fd)
{
	if (value)
	{
		write(fd, key, ft_strlen(key));
		write(fd, "=", 1);
		write(fd, value, ft_strlen(value));
	}
	else
		write(fd, key, ft_strlen(key));
}

void	env_print(char *key, char *value, int fd)
{
	if (key && value)
	{
		write(fd, key, ft_strlen(key));
		write(fd, "=", 1);
		write(fd, value, ft_strlen(value));
	}
}

void	exec_env(t_list *env, int fd, int export)
{
	t_env	*node;

	if (export)
	{
		while (env)
		{
			node = (t_env *)env->content;
			export_print(node->key, node->value, fd);
			write(fd, "\n", 1);
			env = env->next;
		}
	}
	else
	{
		while (env)
		{
			node = (t_env *)env->content;
			env_print(node->key, node->value, fd);
			write(fd, "\n", 1);
			env = env->next;
		}
	}
	ft_exit(0);
}
