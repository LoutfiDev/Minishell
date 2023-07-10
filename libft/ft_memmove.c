/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <soulang.dev@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:22:37 by yloutfi           #+#    #+#             */
/*   Updated: 2022/10/28 10:48:56 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{	
	char	*d;
	char	*s;
	size_t	i;

	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return (dst);
	d = (char *)dst;
	s = (char *)src;
	i = 0;
	if (d > s)
	{
		while (len > 0)
		{
			len --;
			d[len] = s[len];
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
