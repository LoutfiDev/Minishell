/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <soulang.dev@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:34:20 by yloutfi           #+#    #+#             */
/*   Updated: 2022/10/17 09:27:33 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isexist(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (str[i])
	{
		if ((unsigned char)str[i] == (unsigned char)c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static unsigned int	ft_get_start(const char *s1, const char *set)
{
	unsigned int	start;
	int				i;

	start = 0;
	i = 0;
	while (s1[i])
	{
		start = ft_isexist(set, s1[i]);
		if (start)
			i++;
		else
			return (i);
	}
	return (-1);
}

static int	ft_get_end(const char *s1, const char *set)
{
	int	end;
	int	i;
	int	j;

	end = 0;
	j = 0;
	i = ft_strlen(s1) - 1;
	while (i >= 0)
	{
		end = ft_isexist(set, s1[i]);
		if (end)
		{
			i--;
			j++;
		}
		else
			return (j);
	}
	return (-1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*res;
	unsigned int	start;
	int				end;
	int				len;

	if (!s1 || !set)
		return (0);
	start = ft_get_start(s1, set);
	end = ft_get_end(s1, set);
	if (start == (unsigned int)-1 || end == -1)
		return (ft_strdup(""));
	len = ft_strlen(s1) - start - end;
	res = ft_substr(s1, start, len);
	return (res);
}
