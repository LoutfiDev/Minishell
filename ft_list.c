/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:37:28 by anaji             #+#    #+#             */
/*   Updated: 2023/06/08 15:02:34 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

t_buffer	*new_buffer(char *str, int type)
{
	t_buffer	*buff;

	buff = malloc(sizeof(t_buffer));
	buff->str = str;
	buff->type = type;
	buff-> next = NULL;
	return (buff);
}

void	add_back(t_buffer **head, t_buffer *last)
{
	t_buffer	*prev;

	if (!(*head))
		*head = last;
	else
	{
		prev = *head;
		while (prev->next)
			prev = prev->next;
		prev -> next = last;
	}
}
