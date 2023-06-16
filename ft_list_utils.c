/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:37:28 by anaji             #+#    #+#             */
/*   Updated: 2023/06/16 17:00:21 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "libft/libft.h"
#include <readline/readline.h>

t_buffer	*new_buffer(char *str, int type)
{
	t_buffer	*buff;

	buff = malloc(sizeof(t_buffer));
	buff->str = ft_strdup(str);
	buff->type = type;
	return (buff);
}

void	fix_types(t_list *lst)
{
	t_buffer	*bf;
	int			c;

	c = 1;
	while (lst)
	{
		bf = (t_buffer *)lst->content;
		if (bf -> type == 2)
		{
			bf -> type = c;
			if (c > 1)
				bf -> type = 2;
		}
		c++;
		lst = lst -> next;
	}
}

void	lst_addfront(t_list **head, t_list *n_node)
{
	t_list	*last;

	last = ft_lstlast(n_node);
	last -> next = *head;
	*head = n_node;
}

void	insert_node(t_list **head, t_list *node, t_list *n_node)
{
	t_list	*last;
	t_list	*tmp;

	tmp = *head;
	last = ft_lstlast(n_node);
	if (tmp == node)
	{
		lst_addfront(head, n_node);
		last -> next = node-> next;
		free(node);
		fix_types(*head);
		return ;
	}
	while (tmp && tmp -> next)
	{
		if (tmp -> next == node)
		{
			tmp -> next = n_node;
			last -> next = node -> next;
			free(node);
		}
		tmp = tmp -> next;
	}
}
