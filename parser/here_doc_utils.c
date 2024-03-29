/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:35:39 by anaji             #+#    #+#             */
/*   Updated: 2023/07/26 20:26:10 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"
#include <signal.h>

int	has_dollar(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	is_herdoc_expandable(char *hd_lim)
{
	int	i;

	i = 0;
	while (hd_lim[i])
	{
		if (hd_lim[i] == '\'' || hd_lim[i] == '"')
		{
			remove_quote(&hd_lim);
			return (0);
		}
		i++;
	}
	return (1);
}

int	open_heredoc(t_list *head, t_list *_env)
{
	t_buffer	*bf;
	int			*here_doc;
	int			st;

	st = 0;
	while (head)
	{
		bf = (t_buffer *)head -> content;
		if (bf ->type == 6)
		{
			here_doc = read_here_doc(bf->str, is_herdoc_expandable(bf->str),
					_env, &st);
			close(here_doc[1]);
			free(bf->str);
			bf->str = ft_itoa(here_doc[0]);
			free(here_doc);
			if (st != 0)
				return (-1);
		}
		head = head -> next;
	}
	return (0);
}

void	clear_heredoc(t_list *lst)
{
	t_buffer	*bf;

	while (lst)
	{
		bf = lst -> content;
		if (bf -> type == 6)
			ft_close_fd(bf);
		lst = lst -> next;
	}
}
