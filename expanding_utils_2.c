/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:51:24 by anaji             #+#    #+#             */
/*   Updated: 2023/06/16 17:13:10 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "expand.h"

char	*get_var(char *str , int *i)
{
	int		start;
	int		dolar;
	char	*res;
	char	*var;

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

int	get_next_var(char *str, char c)
{
	int	i;

	i = 0;
	if (c == 1)
		return (i);
	while (str[i])
	{
		if (str[i] == c)
			return (i + 1);
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

int	is_expand_delim(char c)
{
	return (c == ' ' || c == '"' || c == '$' || c == '\'' || c == '\0');
}

int	is_expandable(char *str, int len)
{
	int i;
	static int	d_quote;
	static int	s_quote;

	i = 0;
	while (i < len)
	{
		if (str[i] == '"' && s_quote % 2 == 0)
		{
			d_quote++;
			return ('"');
		}
		else if (str[i] == '\'' && d_quote % 2 == 0)
		{
			s_quote++;
			return ('\'');
		}
		i++;
	}
	return (1);
}
