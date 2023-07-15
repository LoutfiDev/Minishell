/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:37:28 by anaji             #+#    #+#             */
/*   Updated: 2023/07/15 15:07:33 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"
#include <readline/readline.h>
#include <unistd.h>

t_buffer	*new_buffer(char *str, int type)
{
	t_buffer	*buff;

	buff = malloc(sizeof(t_buffer));
	buff->str = ft_strdup(str);
	buff->type = type;
	return (buff);
}

void	clear_buffer(void *bf)
{
	t_buffer	*tmp_bf;

	tmp_bf = (t_buffer *)bf;
	free(tmp_bf->str);
	free(tmp_bf);
}

int	check_redirection(t_list *lst, char *str)
{
	t_buffer	*bf_node;
	int			c;

	c = 0;
	while (lst)
	{
		bf_node = lst ->content;
		if (bf_node -> type >= 3 && bf_node -> type <= 5)
		{
			if (c)
			{
				write(2, str, ft_strlen(str));
				write(2, ": ambiguous redirect\n", 22);
				free(str);
				return (1);
			}
			c++;
		}
		lst = lst -> next;
	}
	return (0);
}

t_list	*insert_node(t_list **head, t_list *node, t_list *n_node)
{
	t_list	*last;
	t_list	*tmp;

	tmp = *head;
	last = ft_lstlast(n_node);
	if (tmp == node)
	{
		ft_lstadd_front(head, n_node);
		last -> next = node-> next;
		ft_lstdelone(node, clear_buffer);
		fix_types(*head);
		return (n_node);
	}
	while (tmp && tmp -> next)
	{
		if (tmp -> next == node)
		{
			tmp -> next = n_node;
			last -> next = node -> next;
			ft_lstdelone(node, clear_buffer);
			return (*head);
		}
		tmp = tmp -> next;
	}
	return (*head);
}
