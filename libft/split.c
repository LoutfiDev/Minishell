/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:03:11 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/11 16:26:04 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static char	*ft_fill_array(char *str, char c, int *j)
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

char	**split(char *s, char c)
{
	char	**big_array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	big_array = ft_calloc(3, sizeof(char *));
	if (!ft_strchr(s, '='))
	{
		big_array[0] = ft_strdup(s);
		return (big_array);
	}
	while (i < 2)
	{
		if (i == 0)
			big_array[i] = ft_fill_array(s, c, &j);
		else if (i == 1)
			big_array[i] = ft_substr(s, j, ft_strlen(s) - j);
		i++;
		if (!big_array[i - 1])
			return (ft_free_tab(big_array));
		j++;
	}
	return (big_array);
}
