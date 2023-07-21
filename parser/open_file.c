/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:41:52 by anaji             #+#    #+#             */
/*   Updated: 2023/07/19 18:44:28 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"

int	open_file(char **file, int type, int fd)
{
	if (type == 3)
		fd = open(file[0], O_RDONLY);
	else if (type == 4)
	{
		if (access(file[0], F_OK) != -1)
			fd = open(file[0], O_WRONLY | O_TRUNC);
		else
			fd = open(file[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else if (type == 5)
	{
		if (access(file[0], F_OK) != -1)
			fd = open(file[0], O_APPEND);
		else
			fd = open(file[0], O_CREAT | O_APPEND, 0644);
	}
	if (fd == -1)
	{
		perror(file[0]);
		g_exit_status = 1;
		return (-1);
	}
	free(*file);
	file[0] = ft_itoa(fd);
	return (0);
}

void	ft_close(t_buffer *node)
{
	close(ft_atoi(node -> str));
}

int	open_files(t_list *lst)
{
	t_buffer	*bf;
	t_list		*prev;
	char		*tmp;

	prev = NULL;
	while (lst)
	{
		bf = (t_buffer *)lst-> content;
		if (bf -> type > 2 && bf -> type < 6)
		{
			if (!ft_strncmp(bf -> str, "$?", 2))
			{
				tmp = ft_itoa(g_exit_status);
				free(bf->str);
				bf -> str = tmp;
			}
			if (open_file(&bf -> str, bf -> type, 0) == -1)
				return (-1);
			if (prev)
				ft_close(prev -> content);
			prev = lst;
		}
		lst = lst -> next;
	}
	return (0);
}
