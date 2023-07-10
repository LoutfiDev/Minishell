/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 20:04:31 by anaji             #+#    #+#             */
/*   Updated: 2022/10/31 13:29:25 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	lenght;

	i = 0;
	j = 0;
	lenght = 0;
	if (!ft_strlen(needle))
		return ((char *)haystack);
	if (haystack == NULL && len == 0)
		return (NULL);
	lenght = ft_strlen(needle);
	while (haystack[i] && i + j < len)
	{
		if (haystack[i + j] == needle[j])
			j++;
		else
			j = 0;
		if (!j)
			i++;
		if (j == lenght)
			return ((char *)haystack + i);
	}
	return (NULL);
}
