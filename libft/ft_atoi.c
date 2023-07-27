/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:51:45 by anaji             #+#    #+#             */
/*   Updated: 2023/07/27 16:18:12 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	pas_spaces(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	return (i);
}

static	int	get_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-')
	{	
		sign = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
	{
		sign = 1;
		(*i)++;
	}
	return (sign);
}

static	int	ft_init(const char *s, unsigned long long *res, int i)
{
	int	num_len;

	num_len = 0;
	*res = 0;
	while (s[i] && s[i] == '0')
		i++;
	while (s[i])
	{
		if (ft_isdigit(s[i]))
		{
			num_len++;
		}
		else
			break ;
		i++;
	}
	return (num_len);
}

long long	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	res;
	int					sign;
	int					len;

	i = pas_spaces(str);
	sign = get_sign(str, &i);
	len = ft_init(str, &res, i);
	if (len > 19 && sign == 1)
		return ((long)INT_MAX + 1);
	if (len > 19 && sign == -1)
		return ((long)INT_MIN - 1);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			res = res * 10;
			res = res + (str[i] - '0');
		}
		else
			return (-1);
		i++;
	}
	return (res * sign);
}
