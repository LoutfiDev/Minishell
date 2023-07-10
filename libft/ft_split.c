/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <soulang.dev@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:15:11 by yloutfi           #+#    #+#             */
/*   Updated: 2022/10/23 09:37:11 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbr_array(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str == 0)
		return (0);
	if (str[0] != c && str[0])
		count++;
	while (i < (int)ft_strlen(str))
	{
		if (str[i] == c && str[i + 1] != c && str[i + 1])
			count++;
		i++;
	}
	return (count);
}

static char	*ft_fill_array(const char *str, char c, int *j)
{
	int		start;
	int		length;

	start = *j;
	length = 0;
	while (str[*j] != c && str[*j])
	{
		(*j)++;
		length++;
	}
	return (ft_substr(str, start, length));
}

static char	**ft_free_tab(char **big_array)
{
	int	i;

	i = 0;
	while (big_array[i])
	{
		free(big_array[i]);
		i++;
	}
	free(big_array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**big_array;
	int		i;
	int		j;
	int		nbr;

	i = 0;
	j = 0;
	nbr = ft_nbr_array(s, c);
	big_array = ft_calloc((nbr + 1), sizeof(char *));
	if (big_array == NULL)
		return (0);
	while (s && i < nbr)
	{
		while (s[j] && s[j] == c)
			j++;
		big_array[i++] = ft_fill_array(s, c, &j);
		if (!big_array[i - 1])
			return (ft_free_tab(big_array));
		j++;
	}
	return (big_array);
}
