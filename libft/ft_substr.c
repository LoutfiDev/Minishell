/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <soulang.dev@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 09:28:42 by yloutfi           #+#    #+#             */
/*   Updated: 2022/10/27 18:17:17 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*substr;
	size_t	i;

	if (!s)
		return (0);
	str = (char *)s;
	if (start + len > ft_strlen(str))
		len = ft_strlen(str) - start;
	if (start >= ft_strlen(str))
		return (ft_strdup(""));
	i = 0;
	substr = malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (0);
	while (i < len)
	{
		substr[i] = str[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
