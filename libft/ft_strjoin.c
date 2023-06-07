/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 08:44:25 by anaji             #+#    #+#             */
/*   Updated: 2022/10/30 19:51:51 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str_join;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str_join = malloc(s1_len + s2_len + 1);
	if (!str_join)
		return (0);
	ft_memmove(str_join, s1, s1_len);
	ft_memmove(str_join + s1_len, s2, s2_len);
	str_join[s1_len + s2_len] = '\0';
	return (str_join);
}
