/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:35:36 by anaji             #+#    #+#             */
/*   Updated: 2023/07/15 08:17:55 by anaji            ###   ########.fr       */
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

void	ft_cpy_new(char *old, char **res, int len)
{
	int		i;
	int		d_quote;
	int		s_quote;
	int		j;

	i = 0;
	j = 0;
	d_quote = 0;
	s_quote = 0;
	res[0] = malloc(len + 1);
	while (old[i])
	{
		if (old[i] == '\'' && d_quote % 2 == 0)
			s_quote++;
		else if (old[i] == '"' && s_quote % 2 == 0)
			d_quote++;
		else
		{
			res[0][j] = old[i];
			j++;
		}
		i++;
	}
	res[0][j] = '\0';
}

void	remove_quote(char **str)
{
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	tmp = ft_strdup(*str);
	free(*str);
	len = get_tmp_len(tmp);
	ft_cpy_new(tmp, str, len);
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

void	check_num_quotes(t_quote *quote)
{
	if (quote -> num_dquote % 2 || quote -> num_squote % 2)
	{
		write(2, "syntax error (unclosed quote)\n", 31);
		free(quote);
		exit(-1);
	}
}
