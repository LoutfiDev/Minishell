/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <soulang.dev@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:55:02 by yloutfi           #+#    #+#             */
/*   Updated: 2022/10/28 10:49:07 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	length;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	length = 0;
	if (dst)
		length = ft_strlen(dst);
	if (dstsize == 0 || dstsize <= length)
		return (len + dstsize);
	while (src[i] && i < dstsize - length - 1)
	{
		dst[length + i] = src[i];
		i++;
	}
	dst[length + i] = '\0';
	return (length + len);
}
