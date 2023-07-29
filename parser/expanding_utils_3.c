/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:19:16 by anaji             #+#    #+#             */
/*   Updated: 2023/07/28 16:00:16 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"
#include "../includes/expand.h"

int	check_var_quote(char c, t_quote *q, int check)
{
	if (c == '\'')
	{
		if (q->num_squote == 0 && !check)
		{
			q->num_squote += 1;
			return (-1);
		}
	}
	else if (c == '"' && !check)
	{
		if (q->num_dquote == 0)
		{
			q->num_dquote += 1;
			return (-1);
		}
	}
	return (0);
}

int	go_to_next_var(char *str, int i, t_quote *q)
{
	int	c;

	c = 0;
	if (str[i] == '$')
		return (i + 1);
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '?')
		{
			if (str[i] == '?')
				return (i + 1);
			i++;
			c++;
		}
		else if (str[i] == '\'' || str[i] == '"')
		{
			if (check_var_quote(str[i], q, c) == -1)
				return (-i);
			return (i);
		}
		else
			break ;
	}
	return (i);
}

void	modifiy_quote(int *add, int *zero)
{
	*add += 1;
	if (*add % 2 == 0)
		*add = 0;
	*zero = 0;
}

char	*ret_res(char *str, int end, int *track, int i)
{
	char	*res;

	if (end < 0)
	{
		*track += -end;
		return (ft_strdup("\0"));
	}
	if (!end)
	{
		*track += i;
		return (ft_strdup(str));
	}
	res = ft_substr(str, i, end - i);
	*track += end;
	return (res);
}

char	*get_var(char *str, int *j, t_quote *q)
{
	int		i;
	int		end;
	char	*res;

	i = 0;
	end = 0;
	while (str[i])
	{
		if (str[i] == '"' && q->num_squote % 2 == 0)
			modifiy_quote(&q->num_dquote, &q->num_squote);
		if (str[i] == '\'' && q->num_dquote % 2 == 0)
			modifiy_quote(&q->num_squote, &q->num_dquote);
		if (str[i] == '$')
		{
			end = go_to_next_var(str, i + 1, q);
			break ;
		}
		i++;
	}
	res = ret_res(str, end, j, i);
	return (res);
}
