/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:12:25 by anaji             #+#    #+#             */
/*   Updated: 2022/10/30 21:37:38 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	int	get_int_len(long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		len = 1;
		nb = -nb;
	}
	while (nb != 0)
	{
		len ++;
		nb = nb / 10;
	}
	return (len);
}

static	int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

static	void	fill_form(char **s, long nb, int len)
{
	int		i;
	long	n;

	i = 0;
	n = nb;
	while (i < len)
	{
		(*s)[len - i - 1] = ft_abs((nb % 10)) + '0';
		i++;
		nb = nb / 10;
	}	
	if (n < 0)
		(*s)[0] = '-';
	(*s)[i] = '\0';
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = get_int_len((long)n);
	str = malloc(len + 1);
	if (!str)
		return (0);
	fill_form(&str, (long)n, len);
	return (str);
}
