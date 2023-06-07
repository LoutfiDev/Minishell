/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:33:47 by anaji             #+#    #+#             */
/*   Updated: 2022/10/30 14:23:08 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isprint(int c)
{
	unsigned char	character;

	character = (unsigned char) c;
	if ((character > 31 && character < 127) && c < 256)
	{
		return (1);
	}
	return (0);
}
