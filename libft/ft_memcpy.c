/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 19:47:35 by anaji             #+#    #+#             */
/*   Updated: 2022/10/30 22:31:19 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*srcs;
	unsigned char	*dest;

	i = 0;
	if (dst == src)
		return (dst);
	srcs = (unsigned char *) src;
	dest = (unsigned char *) dst;
	while (i < n)
	{
		dest[i] = srcs[i];
		i++;
	}
	return (dst);
}
