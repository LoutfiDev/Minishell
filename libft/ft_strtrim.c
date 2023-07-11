/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 08:57:09 by anaji             #+#    #+#             */
/*   Updated: 2023/07/11 13:34:58 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	start_of_text(const char *s1, const char *set)
{
	size_t	i_start;
	size_t	i;
	size_t	j;

	i = 0;
	i_start = 0;
	while (i < ft_strlen(s1))
	{
		j = 0;
		while (j < ft_strlen(set))
		{
			if (s1[i_start] == set[j])
			{
				i++;
				i_start++;
				j = -1;
			}
			if (i != i_start)
				return (i_start);
			j++;
		}
		i++;
	}
	return (i_start);
}

size_t	end_of_text(const char *s1, const char *set)
{
	size_t	i_end;
	size_t	j;
	size_t	i;

	i = ft_strlen(s1) - 1;
	i_end = i;
	while (i > 0)
	{
		j = 0;
		while (j < ft_strlen(set))
		{
			if (s1[i_end] == set[j])
			{
				i--;
				i_end--;
				j = -1;
			}
			if (i != i_end)
				return (i_end);
			j++;
		}
		i--;
	}
	return (i_end);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*s;
	size_t	start_txt;
	size_t	end_txt;
	size_t	len;

	if (!s1)
		return (free(s1), NULL);
	if (!set)
		return (ft_strdup(s1));
	start_txt = start_of_text(s1, set);
	if (start_txt == ft_strlen(s1))
		return (free(s1), ft_strdup(""));
	end_txt = end_of_text(s1, set);
	len = end_txt - start_txt + 1;
	s = ft_substr(s1, start_txt, len);
	free(s1);
	return (s);
}
