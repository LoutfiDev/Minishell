/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:20:42 by yloutfi           #+#    #+#             */
/*   Updated: 2023/06/11 10:21:16 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	tmp = (*lst);
	*lst = (*lst)->next;
	free(tmp);
	return ;
}
