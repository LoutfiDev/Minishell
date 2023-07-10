/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:51:24 by anaji             #+#    #+#             */
/*   Updated: 2023/07/08 15:26:19 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "expand.h"

char	*get_var(char *str, int *i)
{
	int		start;
	int		dolar;
	char	*res;

	dolar = 0;
	while (str[*i])
	{
		if (str[*i] == '$' && dolar == 0)
		{
			dolar++;
			start = *i;
		}
		else if (dolar == 1 && is_expand_delim(str[*i]))
			break ;
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

	num = 0;
	while (str[*i])
	{
		if (str[*i] == delim)
			num++;
		else if (num >= 2)
			break ;
		if (delim == '$' && (num >= 2 || str[*i] == '"' || str[*i] == '\''))
			break ;
		*i += 1;
	}
}

int	to_next(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == '"' || str[*i] == '\'' | str[*i] == ' ')
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
