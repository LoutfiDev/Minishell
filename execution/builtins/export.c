/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:12:49 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/11 08:27:34 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	is_valide(char *str)
{
	int	i;

	if (str[0] && str[0] == '=')
		return (print_error("export: ", NULL, str, EXP_ERR, 1));
	i = 0;
	while (str[i] && str[i] != '=' && !(str[i] == '+' && str[i + 1] == '='))
		if (!ft_isalnum(str[i++]))
			return (print_error("export: ", NULL, str, EXP_ERR, 1));
	return (0);
}

t_env	*create_node(char *key, char *value)
{
	t_env	*env_node;

	env_node = malloc(sizeof(t_env));
	env_node->key = key;
	env_node->value = value;
	return (env_node);
}

void	_joined(t_list **env, char *key, char *value, int is_join)
{
	t_env	*env_node;
	t_list	*tmp;

	tmp = (*env);
	while (tmp)
	{
		env_node = (t_env *)tmp->content;
		if (!ft_strncmp(env_node->key, key, ft_strlen(key)))
		{
			free(key);
			if (is_join)
				env_node->value = ft_strjoin(env_node->value, value);
			else
			{
				free(env_node->value);
				env_node->value = value;
			}
			return ;
		}
		tmp = tmp->next;
	}
	env_node = create_node(key, value);
	ft_lstadd_back(env, ft_lstnew(env_node));
}

int	new_env(t_list **env, char *new_var)
{
	char	**array;

	if (ft_strchr(new_var, '+'))
	{
		array = split(new_var, '+');
		if (ft_strchr(new_var, '=') && ft_strlen(array[1]) == 1)
			_joined(env, array[0], ft_strdup(""), 1);
		else
			_joined(env, array[0], ft_strdup(array[1] + 1), 1);
		free(array[1]);
	}
	else
	{
		array = split(new_var, '=');
		if (ft_strchr(new_var, '=') && !array[1])
		{
			free(array[1]);
			array[1] = ft_strdup("");
		}
		_joined(env, array[0], array[1], 0);
	}
	free(array);
	return (0);
}

int	exec_export(char **args, t_list **env, int *exit_status)
{
	int	i;

	i = 0;
	while (args[i])
	{
		*exit_status = is_valide(args[i]);
		if (!(*exit_status))
			new_env(env, args[i]);
		i++;
	}
	return (*exit_status);
}
