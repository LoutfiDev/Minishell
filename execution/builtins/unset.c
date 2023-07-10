/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:13:30 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/10 15:27:59 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	if (!ft_strncmp(env_node->key, arg, ft_strlen(env_node->key)))
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
		if (!ft_strncmp(env_node->key, arg, ft_strlen(env_node->key)))
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

	i = -1;
	while (args[++i])
	{
		if (!env_delhead(args[i], env))
			continue ;
		env_delnode(args[i], env);
	}
}
