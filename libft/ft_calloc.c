/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:13:13 by anaji             #+#    #+#             */
/*   Updated: 2022/10/30 20:06:59 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*temp;
	void	*p;
	size_t	i;

	i = 0;
	if (size && count >= SIZE_MAX / size)
		return (0);
	p = malloc(count * size);
	if (!p)
		return (0);
	temp = (char *)p;
	while (i < count * size)
	{
		temp[i] = 0;
		i++;
	}
	return (p);
}
