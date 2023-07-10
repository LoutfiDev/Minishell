/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <soulang.dev@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:14:21 by yloutfi           #+#    #+#             */
/*   Updated: 2022/10/22 10:17:43 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	lenght;
	char	*str;

	i = 0;
	if (!haystack && len == 0)
		return (0);
	str = (char *)haystack;
	lenght = ft_strlen(needle);
	if (lenght == 0)
		return (str);
	while (str[i] && i + lenght <= len)
	{
		if (str[i] == needle[0])
		{
			if (!ft_strncmp(str + i, needle, lenght))
				return (str + i);
		}
		i++;
	}
	return (0);
}
