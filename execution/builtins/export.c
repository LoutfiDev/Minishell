/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:12:49 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/26 21:12:05 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	is_valide(char *str)
{
	int	i;

	if ((str[0] && str[0] == '=') || ft_isdigit(str[0]) || str[0] == '\0')
	{
		print_error("export: ", str, EXP_ERR, 1);
		return (1);
	}
	i = 0;
	while (str[i] && str[i] != '='
		&& !(str[i] == '+' && str[i + 1] == '=' && i > 0))
	{
		if (!ft_isalnum(str[i++]))
		{
			print_error("export: ", str, EXP_ERR, 1);
			return (1);
		}
	}
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
		if (!ft_strncmp(env_node->key, key, 0))
		{
			free(key);
			if (is_join)
				env_node->value = ft_strjoin(env_node->value, value);
			else if ((!env_node->value && value) || (env_node->value && value))
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

void	exec_export(char **args, t_list **env, int fd)
{
	int	i;
	int	exit_code;

	i = 0;
	exit_code = 0;
	if (!args || !args[i])
	{
		exec_env(*env, fd, 1);
		ft_exit(exit_code);
		return ;
	}
	while (args[i])
	{
		exit_code = is_valide(args[i]);
		if (!exit_code)
			new_env(env, args[i]);
		i++;
	}
	ft_exit(exit_code);
}
