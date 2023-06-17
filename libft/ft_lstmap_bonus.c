/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <soulang.dev@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 10:38:54 by yloutfi           #+#    #+#             */
/*   Updated: 2022/10/27 14:42:43 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_lstfree(t_list *lst, void (*del)(void *))
{
	ft_lstclear(&lst, del);
	return (lst);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*head;

	if (!lst || !f || !del)
		return (NULL);
	head = NULL;
	while (lst)
	{
		if (head == NULL)
		{
			head = ft_lstnew(f(lst->content));
			if (!head)
				return (ft_lstfree(head, del));
			lst = lst->next;
		}
		else
		{
			new = ft_lstnew(f(lst->content));
			if (!new)
				return (ft_lstfree(head, del));
			ft_lstadd_back(&head, new);
			lst = lst->next;
		}
	}
	return (head);
}
