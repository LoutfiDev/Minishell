/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:02:48 by anaji             #+#    #+#             */
/*   Updated: 2023/07/11 08:25:42 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"

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
		printf("syntax error");
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
