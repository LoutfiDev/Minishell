/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:31:52 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/10 15:51:02 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path(char *str, t_list *env)
{
	t_env	*env_node;
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		env_node = (t_env *)tmp->content;
		if (!ft_strncmp(env_node->key, str, ft_strlen(env_node->key)))
			return (env_node->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	print_error(char *cmd, char *delim, char *arg, char *msg, int exit_status)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(delim, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(msg, 2);
	return (exit_status);
}

t_env	*create_env_node(char *content)
{
	t_env	*env_node;
	char	**array;

	env_node = malloc(sizeof(t_env));
	array = split(content, '=');
	env_node->key = array[0];
	if (ft_strchr(content, '=') && !array[1])
	{
		free(array[1]);
		env_node->value = ft_strdup("");
	}
	else
		env_node->value = array[1];
	free(array);
	return (env_node);
}

t_list	*create_env(char **env)
{
	t_list	*_env;
	t_env	*env_node;
	int		i;

	_env = NULL;
	i = 0;
	while (env && env[i])
		i++;
	i -= 1;
	while (i >= 0)
	{
		env_node = create_env_node(env[i]);
		ft_lstadd_front(&_env, ft_lstnew(env_node));
		i--;
	}
	return (_env);
}
