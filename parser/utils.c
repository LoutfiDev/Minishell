/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:39:30 by anaji             #+#    #+#             */
/*   Updated: 2023/07/18 19:44:32 by anaji            ###   ########.fr       */
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
			c++;
		}
		lst = lst -> next;
	}
}

void	open_file(char **file, int type)
{
	int	fd;

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
	char		*tmp;

	prev = NULL;
	if (g_exit_status)
		return ;
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
			open_file(&bf -> str, bf -> type);
			if (prev)
				ft_close(prev -> content);
			prev = lst;
		}
		lst = lst -> next;
	}
}

t_list	*re_arrange_buffer(t_list *lst, int old_type)
{
	t_buffer	*bf;
	t_list		*head;
	t_list		*tmp;
	t_list		*old;

	head = NULL;
	while (lst)
	{
		bf = (t_buffer *)lst -> content;
		if (ft_strlen(bf -> str))
		{
			if (old_type)
				bf -> type = old_type;
			tmp = ft_lstnew(new_buffer(bf -> str, bf -> type));
			ft_lstadd_back(&head, tmp);
			old_type = 0;
		}
		else if (bf -> type == 1)
			old_type = 1;
		old = lst;
		lst = lst -> next;
		ft_lstdelone(old, clear_buffer);
	}
	return (ft_lstclear(&lst, clear_buffer), head);
}
