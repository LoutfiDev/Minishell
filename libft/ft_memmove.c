/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 08:58:35 by anaji             #+#    #+#             */
/*   Updated: 2022/10/30 22:31:37 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*srcs;

	if (dst == src)
		return (dst);
	srcs = (unsigned char *)src;
	dest = (unsigned char *)dst;
	i = 0;
	if (dest < srcs)
	{
		ft_memcpy(dst, src, len);
	}
	else if (dst > src)
	{
		while (i < len)
		{
			dest[len - i - 1] = srcs[len - i - 1];
			i++;
		}
	}
	return (dst);
}
