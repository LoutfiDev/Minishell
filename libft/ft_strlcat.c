/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:28:03 by anaji             #+#    #+#             */
/*   Updated: 2022/10/31 13:23:54 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	the_lenght;

	dst_len = 0;
	i = 0;
	if (dst)
		dst_len = ft_strlen((const char *)dst);
	the_lenght = dst_len + ft_strlen(src);
	if (dstsize <= dst_len || dstsize == 0)
		return (ft_strlen(src) + dstsize);
	dstsize -= (dst_len + 1);
	while (src[i] && dstsize > 0)
	{
		dst[dst_len] = src[i];
		i++;
		dst_len++;
		dstsize--;
	}
	dst[dst_len] = '\0';
	return (the_lenght);
}
