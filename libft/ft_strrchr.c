/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:12:14 by anaji             #+#    #+#             */
/*   Updated: 2022/10/30 22:36:53 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	size;

	size = (int)ft_strlen(s);
	while (size >= 0)
	{
		if (s[size] == (char)c)
			return ((char *)s + size);
		size--;
	}
	return (0);
}
