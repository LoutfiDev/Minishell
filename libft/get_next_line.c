/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:35:48 by anaji             #+#    #+#             */
/*   Updated: 2023/06/03 08:21:00 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_me_next(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*ft_cpy(char *src, int len)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len && src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*next_line(int fd, char *buff, char **holder, int *index)
{
	char	*res;
	char	*str;

	res = NULL;
	*index = find_me_next(buff);
	if (*index)
	{
		res = ft_cpy(buff, *index);
		if (buff + (*index))
			*holder = ft_cpy(buff + (*index), ft_len(buff) - (*index));
		return (res);
	}
	else
		res = get_next_line(fd);
	str = strjoin(buff, res, ft_len(res));
	free(res);
	return (str);
}

char	*init(int *index, char *holder, char **res)
{
	char	*buff;
	int		len;

	*index = ft_len(holder);
	len = BUFFER_SIZE + (*index) + 1;
	*res = NULL;
	buff = ft_mcalloc(len, sizeof(char), holder);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char		*holder;
	char			*res;
	char			*buff;
	int				index;
	int				old_call;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buff = init(&index, holder, &res);
	holder = NULL;
	old_call = read(fd, buff + index, BUFFER_SIZE);
	if (old_call == -1)
	{
		free(buff);
		free(holder);
		return (NULL);
	}
	if (old_call > 0 || ft_len(buff))
	{
		res = next_line(fd, buff, &holder, &index);
		free(buff);
		return (res);
	}
	free(buff);
	return (NULL);
}
