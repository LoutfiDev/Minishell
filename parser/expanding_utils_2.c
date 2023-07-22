/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:51:24 by anaji             #+#    #+#             */
/*   Updated: 2023/07/22 12:47:50 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"
#include "../includes/expand.h"

char	*get_var(char *str, int *i, int dolar, int check)
{
	int		start;
	char	*res;

	while (str[*i])
	{
		if (dolar == 2)
			break ;
		if (dolar == 1 && check == 1 && !ft_isalnum(str[*i]) && str[*i] != '?')
			break ;
		if (str[*i] == '$')
		{
			check = 0;
			if (!dolar)
				start = *i;
			dolar++;
		}
		else
			check = 1;
		*i += 1;
	}
	res = ft_substr(str, start, (*i) - start);
	return (res);
}

char	*get_var_value(t_list *env, char *key)
{
	int		len;
	char	*tmp;
	t_env	*v_env;

	if (!ft_strncmp(key, "$", ft_strlen(key) + 1))
		return (key);
	if (!ft_strncmp(key, "$?", ft_strlen(key) + 2))
		return (key);
	if (!ft_strncmp(key, "$$", ft_strlen(key) + 2))
		return (key);
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

void	skip_to_next(char *str, int *i, int delim)
{
	int	num;
	int	dolar;

	num = 0;
	dolar = 0;
	while (str[*i])
	{
		if (num == 2)
			break ;
		else if (str[*i] == delim)
		{
			// *i += 1;
			// to_next(str, i, 0);
			// return ;
			if (str[(*i) + 1] == '$')
			{
				*i += 1;
				return ;
			}
			num++;
		}
		else if (delim == '$' && num && !ft_isalnum(str[*i]) && str[*i] != '?')
			break ;
		*i += 1;
	}
}

int	to_next(char *str, int *i, int check)
{
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

int	is_expand_delim(char c)
{
	return (c == ' ' || c == '"' || c == '$' || c == '\'' || c == '\0');
}
