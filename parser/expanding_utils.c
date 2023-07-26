/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:02:54 by anaji             #+#    #+#             */
/*   Updated: 2023/07/25 13:42:36 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"
#include "../includes/expand.h"

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

void	check_quote_before_ex(char *str, int *i)
{
	int	d_quote;
	int	s_quote;

	d_quote = 0;
	s_quote = 0;
	if (ft_strnstr(str, "$?", 0))
		return ;
	while (str && str[*i])
	{
		if (str[*i] == '$' && ((s_quote % 2 != 0 && d_quote % 2 == 0)
				|| (s_quote % 2 == 0 && d_quote % 2 != 0)
				|| (str[*i] == '$' && s_quote % 2 == 0 && d_quote % 2 == 0)))
		{
			*i = 0;
			return ;
		}
		if (str[*i] == '\'' && d_quote % 2 == 0)
			s_quote++;
		if (str[*i] == '"' && s_quote % 2 == 0)
			d_quote++;
		*i += 1;
	}
}

int	get_expand_type(char *str)
{
	int	i;

	i = 0;
	check_quote_before_ex(str, &i);
	while (str[i])
	{
		if (str[i] == '\'')
			return ('\'');
		else if (str[i] == '"')
			return ('"');
		else if (str[i] == '`')
			return ('`');
		else if (str[i] == '$')
			break ;
		i++;
	}
	return ('$');
}

char	*ft_join(char *str, t_list **lst)
{
	t_buffer	*bf;
	t_list		*tmp;
	char		*res;

	tmp = *lst;
	if (!tmp)
		return (ft_strdup("\0"));
	bf = (t_buffer *)tmp -> content;
	res = ft_strjoin(str, bf -> str);
	*lst = (*lst)-> next;
	free(bf);
	free(tmp);
	return (res);
}

char	*join_str(char *to_join, char *str, t_list **lst)
{
	t_list		*tmp;
	t_buffer	*bf;

	tmp = *lst;
	bf = tmp -> content;
	to_join = ft_strjoin(to_join, str);
	(*lst) = (*lst)-> next;
	free(bf -> str);
	free(bf);
	free(tmp);
	return (to_join);
}
