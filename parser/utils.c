/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:39:30 by anaji             #+#    #+#             */
/*   Updated: 2023/07/11 12:26:29 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"


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
		}
		c++;
		lst = lst -> next;
	}
}
