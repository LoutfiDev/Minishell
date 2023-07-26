/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:39:30 by anaji             #+#    #+#             */
/*   Updated: 2023/07/26 16:30:24 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"
#include "../includes/exec.h"

void	fix_types(t_list *lst)
{
	t_buffer	*bf;
	int			c;

	c = 1;
	while (lst)
	{
		bf = (t_buffer *)lst->content;
		if (bf -> type == 1)
		{
			bf -> type = c;
			if (c > 1)
				bf -> type = 2;
			c++;
		}
		lst = lst -> next;
	}
}

char	*ft_readline(void)
{
	char	*line;

	if (!isatty(READ_END))
		line = ft_strtrim(get_next_line(READ_END), "\n");
	else
		line = readline("MINISHELL : ");
	return (line);
}

int	error_protocol(t_list **lst, t_quote *quotes)
{
	ft_lstclear(lst, clear_buffer);
	free(quotes);
	return (-1);
}

t_list	*re_arrange_buffer(t_list *lst, int old_type)
{
	t_buffer	*bf;
	t_list		*head;
	t_list		*tmp;
	t_list		*old;

	head = NULL;
	while (lst)
	{
		bf = (t_buffer *)lst -> content;
		if (ft_strlen(bf -> str))
		{
			if (old_type)
				bf -> type = old_type;
			tmp = ft_lstnew(new_buffer(bf -> str, bf -> type));
			ft_lstadd_back(&head, tmp);
			old_type = 0;
		}
		else if (bf -> type == 1)
			old_type = 1;
		old = lst;
		lst = lst -> next;
		ft_lstdelone(old, clear_buffer);
	}
	return (ft_lstclear(&lst, clear_buffer), head);
}

void	ft_close_fd(t_buffer *fd)
{
	close(ft_atoi(fd -> str));
}
