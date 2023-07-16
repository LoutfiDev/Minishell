/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:39:30 by anaji             #+#    #+#             */
/*   Updated: 2023/07/16 07:44:20 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"
#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>

void	fix_types(t_list *lst)
{
	t_buffer	*bf;
	int			c;

	c = 1;
	while (lst)
	{
		bf = (t_buffer *)lst->content;
		if (bf -> type == 1)
		{
			bf -> type = c;
			if (c > 1)
				bf -> type = 2;
		}
		c++;
		lst = lst -> next;
	}
}

void	open_file(char  **file, int type)
{
	int	fd;

	if (type == 3)
		fd = open(file[0], O_RDONLY);
	else if (type == 4)
	{
		if (access(file[0], F_OK) != -1)
			fd = open(file[0], O_WRONLY | O_TRUNC);
		else
			fd = open(file[0], O_CREAT, 0644);
	}
	else if (type == 5)
	{
		if (access(file[0], F_OK) != -1)
			fd = open(file[0], O_APPEND);
		else
			fd = open(file[0], O_CREAT, 0644);
	}
	if (fd == -1)
	{
		perror(file[0]);
		g_exit_status = 1;
	}
	free(*file);
	file[0] = ft_itoa(fd);
}

void	ft_close(t_buffer *node)
{
	close(ft_atoi(node -> str));
}

void	open_files(t_list *lst)
{
	t_buffer	*bf;
	t_list		*prev;

	prev = NULL;
	while (lst)
	{
		bf = (t_buffer *)lst-> content;
		if (bf -> type > 2 && bf -> type < 6)
		{
			open_file(&bf -> str, bf -> type);
			if (prev)
				ft_close(prev -> content);
			prev = lst;
		}
		lst = lst -> next;
	}
}
