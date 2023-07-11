/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:35:25 by anaji             #+#    #+#             */
/*   Updated: 2023/07/11 19:36:04 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	if (!s1)
		return (1);
	while (i < n && (s1[i] || s2[i]))
	{
		c1 = (unsigned char)s1[i];
		c2 = (unsigned char)s2[i];
		if (c2 == c1)
			i++;
		else
			return (c1 - c2);
	}
	return (0);
}
