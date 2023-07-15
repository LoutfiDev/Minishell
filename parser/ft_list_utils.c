/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:37:28 by anaji             #+#    #+#             */
/*   Updated: 2023/07/15 11:28:25 by anaji            ###   ########.fr       */
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

int	check_redirection(t_list **head, t_list *lst, t_list *node)
{
	t_buffer	*bf;
	t_buffer	*bf_node;
	int			size;

	size = ft_lstsize(lst);
	bf = lst -> content;
	bf_node = node ->content;
	if (bf -> type >= 3 && bf -> type <= 5 && size > 1)
	{
		write(2, bf_node->str, ft_strlen(bf_node->str));
		write(2, ": ambiguous redirect\n", 22);
		ft_lstclear(head, clear_buffer);
		return (1);
	}
	return (0);
}

void	insert_node(t_list **head, t_list *node, t_list *n_node)
{
	t_list	*last;
	t_list	*tmp;

	tmp = *head;
	if (check_redirection(head, n_node, node))
		exit(1);
	last = ft_lstlast(n_node);
	if (tmp == node)
	{
		ft_lstadd_front(head, n_node);
		last -> next = node-> next;
		ft_lstdelone(node, clear_buffer);
		fix_types(*head);
		return ;
	}
	while (tmp && tmp -> next)
	{
		if (tmp -> next == node)
		{
			tmp -> next = n_node;
			last -> next = node -> next;
			ft_lstdelone(node, clear_buffer);
		}
		tmp = tmp -> next;
	}
}
