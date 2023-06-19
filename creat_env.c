/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:35:22 by anaji             #+#    #+#             */
/*   Updated: 2023/06/18 16:42:19 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

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
