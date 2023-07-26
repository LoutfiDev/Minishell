/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:51:24 by anaji             #+#    #+#             */
/*   Updated: 2023/07/26 16:38:39 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"
#include "../includes/expand.h"

char	*get_var_value(t_list *env, char *key)
{
	int		len;
	char	*tmp;
	t_env	*v_env;

	if (!ft_strncmp(key, "$", ft_strlen(key) + 1))
		return (ft_strjoin(key, ft_strdup("\0")));
	if (!ft_strncmp(key, "$?", ft_strlen(key) + 2))
		return (ft_strjoin(key, ft_strdup("\0")));
	if (!ft_strncmp(key, "$$", ft_strlen(key) + 2))
		return (ft_strjoin(key, ft_strdup("\0")));
	tmp = ft_strdup(key + 1);
	len = ft_strlen(tmp);
	free(key);
	while (env)
	{
		v_env = env -> content;
		if (!ft_strncmp(v_env -> key, tmp, len + ft_strlen(v_env -> key)))
		{
			free(tmp);
			return (ft_strdup(v_env -> value));
		}
		env = env -> next;
	}
	free(tmp);
	return (ft_strdup("\0"));
}

void	go_to_next(char *str, int *i, int delim)
{
	if (delim == '$' && str[*i] == '$')
	{
		*i += 1;
		return ;
	}
	while (str[*i])
	{
		if (delim == '$' && !ft_isalnum(str[*i]) && str[*i] != '?')
			break ;
		if (str[*i] == delim)
		{
			if (delim == '$')
				break ;
			*i += 1;
			break ;
		}
		*i += 1;
	}
}

void	skip_to_next(char *str, int *i, int delim)
{
	while (str[*i])
	{
		if (str[*i] == delim)
		{
			*i += 1;
			if (delim == '$' && str[*i] == '$')
			{
				*i += 1;
				break ;
			}
			go_to_next(str, i, delim);
			break ;
		}
		*i += 1;
	}
}

int	to_next(char *str, int *i, int check)
{
	*i += 1;
	if (str[*i] == '$')
		return (*i += 1);
	while (str[*i])
	{
		if (check == 2)
		{
			*i += 1;
			return (*i);
		}
		if (!ft_isalnum(str[*i]) && str[*i] != '$' && str[*i] != '?')
			return (*i + 1);
		if (str[*i] == '$')
			break ;
		*i += 1;
	}
	return (*i);
}
