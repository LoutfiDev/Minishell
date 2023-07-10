/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 23:45:02 by anaji             #+#    #+#             */
/*   Updated: 2022/10/30 21:38:21 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*n_node;

	if (lst && del)
	{
		tmp = *lst;
		while (tmp != NULL)
		{
			n_node = tmp -> next;
			ft_lstdelone(tmp, del);
			tmp = n_node;
		}
		(*lst) = NULL;
	}
}
