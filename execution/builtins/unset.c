/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:13:30 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/24 13:09:47 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include <stdlib.h>

void	delone(t_list **lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	tmp = (*lst);
	*lst = (*lst)->next;
	free(tmp);
	return ;
}

int	env_delhead(char *arg, t_list **env)
{
	t_env	*env_node;

	env_node = (t_env *)(*env)->content;
	if (!ft_strncmp(env_node->key, arg, 0))
	{
		free(env_node->key);
		if (env_node->value)
			free(env_node->value);
		free(env_node);
		delone(env);
		return (0);
	}
	return (1);
}

int	env_delnode(char *arg, t_list **env)
{
	t_env	*env_node;
	t_list	*tmp_node;
	t_list	*tmp;

	tmp = (*env);
	while (tmp->next)
	{
		env_node = (t_env *)tmp->next->content;
		if (!ft_strncmp(env_node->key, arg, 0))
		{
			free(env_node->key);
			if (env_node->value)
				free(env_node->value);
			free(env_node);
			tmp_node = tmp->next;
			tmp->next = tmp->next->next;
			free(tmp_node);
			break ;
		}
		tmp = tmp->next;
	}
	return (1);
}

void	exec_unset(char **args, t_list **env)
{
	int		i;
	int		exit_code;

	i = -1;
	exit_code = 0;
	while (args[++i])
	{
		exit_code = is_valide(args[i]);
		if (!exit_code)
		{
			if (!env_delhead(args[i], env))
				continue ;
			env_delnode(args[i], env);
		}
	}
	ft_exit(exit_code);
}
