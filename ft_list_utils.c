/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:37:28 by anaji             #+#    #+#             */
/*   Updated: 2023/06/15 18:19:13 by anaji            ###   ########.fr       */
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

void	insert_node(t_list **head, t_list *node, t_list *n_node)
{
	t_list	*last;
	t_list	*tmp;

	tmp = *head;
	last = ft_lstlast(n_node);
	if (tmp == node)
	{
		*head = node;
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
