/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:54:54 by anaji             #+#    #+#             */
/*   Updated: 2022/10/30 22:33:35 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	int	w_len(const char *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] && s[i] != c)
	{	
		len++;
		i++;
	}
	return (len);
}

static	int	word_num(const char *s, char c)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			num ++;
			i = i + w_len(s, c, i);
		}
		else
			i++;
	}
	return (num);
}

static	void	free_str(char ***s, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free((*s)[i]);
		i++;
	}
	free (*s);
}

static	char	**initiate(const char *s, char c, int *i, int *j)
{
	char	**str;

	if (!s)
		return (NULL);
	str = malloc((word_num(s, c) + 1) * sizeof (char *));
	*i = 0;
	*j = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;

	str = initiate(s, c, &i, &j);
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			str[j] = ft_substr(s, i, w_len(s, c, i));
			if (!str[j])
			{
				free_str(&str, j);
				return (NULL);
			}
			i = i + w_len(s, c, i);
			j++;
		}
		else
			i++;
	}
	str[j] = NULL;
	return (str);
}
