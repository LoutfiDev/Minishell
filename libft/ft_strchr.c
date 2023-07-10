/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:17:50 by yloutfi           #+#    #+#             */
/*   Updated: 2023/06/10 14:30:18 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *str, int c)
{
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	if ((char)c == '\0')
		return (str + ft_strlen(str));
	while (str[i])
	{
		if (str[i] == (char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}
