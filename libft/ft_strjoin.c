/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 08:44:25 by anaji             #+#    #+#             */
/*   Updated: 2023/06/21 11:57:54 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str_join;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str_join = malloc(s1_len + s2_len + 1);
	if (!str_join)
		return (0);
	ft_memmove(str_join, s1, s1_len);
	ft_memmove(str_join + s1_len, s2, s2_len);
	str_join[s1_len + s2_len] = '\0';
	free(s1);
	free(s2);
	return (str_join);
}
