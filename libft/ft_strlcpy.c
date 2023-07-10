/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <soulang.dev@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:45:49 by yloutfi           #+#    #+#             */
/*   Updated: 2022/10/14 09:08:32 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	lenght;

	i = 0;
	lenght = ft_strlen(src);
	if (!dstsize)
		return (lenght);
	while (src[i] && i < dstsize -1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (lenght);
}
