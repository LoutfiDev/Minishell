/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:02:48 by anaji             #+#    #+#             */
/*   Updated: 2023/07/15 13:36:53 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"
#include <stdlib.h>

void	ft_skip_space(char *str, int *i)
{
	while (str[*i] == ' ')
		(*i)++;
}

int	get_start_delim(char *str, int i, int *type, int *delim)
{
	ft_skip_space(str, &i);
	*delim = 1;
	if (ft_is_heredoc(str[i], str[i + 1], type)
		|| ft_is_append(str[i], str[i + 1], type))
	{
		i += 2;
		ft_skip_space(str, &i);
		return (2);
	}
	if (ft_is_read(str[i], type) || ft_is_write(str[i], type))
	{
		i += 1;
		ft_skip_space(str, &i);
		return (1);
	}
	ft_skip_space(str, &i);
	return (0);
}

int	is_delim(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == ' ');
}

int	get_next_delim(char *str, int i, int *delim, t_quote *quotes)
{
	if ((is_delim(str[i]) && *delim) || !str[i])
	{
		if (str[i])
			write(2, "syntax error near unexpected token\n", 35);
		else
			write(2, "syntax error near unexpected token `newline'\n", 45);
		g_exit_status = 2;
	}
	while (str[i])
	{
		if (is_delim(str[i]) && !(*delim)
			&& quotes->num_squote % 2 == 0 && quotes->num_dquote % 2 == 0)
			break ;
		if (str[i] == '\'' && quotes->num_dquote % 2 == 0)
			quotes->num_squote++;
		if (str[i] == '\"' && quotes->num_squote % 2 == 0)
			quotes->num_dquote++;
		*delim = 0;
		i++;
	}
	return (i);
}

int	get_type(char *str, int type, int i, int *cmd)
{
	if (type)
		return (type);
	else if (str[i] == '|')
		return (PIPE);
	else if (*cmd == 0)
	{
		*cmd = 1;
		return (1);
	}
	return (2);
}
