/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:02:54 by anaji             #+#    #+#             */
/*   Updated: 2023/06/16 18:29:44 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "libft/libft.h"
#include "expand.h"


int	get_dollar(char *str, int *end)
{
	int	i;

	*end = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
		*end += 1;
	}
	return (0);
}

char	*get_var_value(char **env, char *key)
{
	int		i;
	int		len;
	char	*tmp;

	tmp = ft_strjoin(key + 1, "=");
	len = ft_strlen(tmp);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], tmp, len))
		{
			free(tmp);
			return (env[i] + len);
		}
		i++;
	}
	free(tmp);
	return (NULL);
}

int		check_type(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (MANY_ARG);
		else if (str[i] == '"')
			return (ONE_ARG);
		i++;
	}
	return (NO_ARG);
}

int get_end(int type, char *str)
{
	int		i;
	int		end;
	char	c;

	i = 0;
	if (type == ONE_ARG)
		c = '"';
	else if (type == MANY_ARG)
		c = '$';
	else if (type == NO_ARG)
		c = '\'';
	end = 0;
	while (str[i])
	{
		if (str[i] == c)
			end ++;
		if (end >= 2 || (end && c == '$' && is_expand_delim(str[i])))
			break ;
		i++;
	}
	return (i);
}


