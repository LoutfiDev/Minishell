/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:49:26 by anaji             #+#    #+#             */
/*   Updated: 2023/06/03 08:24:10 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_len(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	*ft_mset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)b;
	while (i < len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void	*ft_mmove(void *dst, void *src, size_t len)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*srcs;

	srcs = (unsigned char *)src;
	dest = (unsigned char *)dst;
	i = 0;
	while (i < len)
	{
		dest[i] = srcs[i];
		i++;
	}
	return (dst);
}

char	*ft_mcalloc(size_t count, size_t size, char *str)
{
	char	*p;

	if (count >= SIZE_MAX || size >= SIZE_MAX)
		return (NULL);
	p = malloc(count * size);
	if (!p)
		return (0);
	ft_mset(p, 0, count * size);
	p = ft_mmove(p, str, ft_len(str));
	free(str);
	return (p);
}

char	*strjoin(char *s1, char *s2, int len)
{
	char	*str;
	int		sl1;
	int		sl2;

	if (!s1)
		s1 = ft_mcalloc(1, 1, "\0");
	sl1 = ft_len(s1);
	sl2 = ft_len(s2);
	if (sl1 == 0 && sl2 == 0)
		return (NULL);
	str = malloc(sl1 + len + 1);
	if (!str)
		return (NULL);
	ft_mmove(str, s1, sl1);
	ft_mmove(str + sl1, s2, len);
	str[sl1 + len] = '\0';
	return (str);
}
