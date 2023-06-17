/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <soulang.dev@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:48:58 by yloutfi           #+#    #+#             */
/*   Updated: 2022/10/27 17:28:48 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_get_lengh(int nb)
{
	int	i;

	if (nb < 0)
		i = 1;
	else
		i = 0;
	while (nb != 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

static char	*ft_putnbr(long n, char *nbr)
{
	int		len;
	int		i;

	len = ft_get_lengh(n);
	i = 0;
	if (n < 0)
	{
		nbr[0] = '-';
		n *= -1;
	}
	while (i < len && n > 0)
	{
		nbr[(len - 1) - i] = (n % 10) + '0';
		n = (n - (n % 10)) / 10;
		i++;
	}
	nbr[len] = '\0';
	return (nbr);
}

char	*ft_itoa(int n)
{
	char	*nbr;

	if (n == 0)
		return (ft_strdup("0"));
	nbr = malloc((ft_get_lengh(n) + 1) * sizeof(char));
	if (nbr == NULL)
		return (0);
	nbr = ft_putnbr(n, nbr);
	return (nbr);
}
