/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:35:36 by anaji             #+#    #+#             */
/*   Updated: 2023/07/11 08:51:05 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"

#include <stdio.h>

int	get_tmp_len(char *str)
{
	int	i;
	int	s_quote;
	int	d_quote;
	int	len;

	s_quote = 0;
	d_quote = 0;
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\'' && d_quote % 2 == 0)
			s_quote++;
		else if (str[i] == '"' && s_quote % 2 == 0)
			d_quote++;
		else
			len ++;
		i++;
	}
	return (len);
}

char	*ft_cpy_new(char *old, int len)
{
	int		i;
	char	*res;
	int		d_quote;
	int		s_quote;
	int		j;

	i = 0;
	j = 0;
	d_quote = 0;
	s_quote = 0;
	res = malloc(len);
	while (old[i])
	{
		if (old[i] == '\'' && d_quote % 2 == 0)
			s_quote++;
		else if (old[i] == '"' && s_quote % 2 == 0)
			d_quote++;
		else
		{
			res[j] = old[i];
			j++;
		}
		i++;
	}
	return (res);
}

void	remove_quote(char **str)
{
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	tmp = ft_strdup(*str);
	free(*str);
	ft_memset(*str, 0, ft_strlen(tmp));
	len = get_tmp_len(tmp);
	str[0] = ft_cpy_new(tmp, len);
	free(tmp);
}

void	handle_quote(t_list *lst)
{
	t_buffer	*bf;

	while (lst)
	{
		bf = lst -> content;
		if (bf -> type != 6)
			remove_quote(&bf -> str);
		lst = lst -> next;
	}
}
