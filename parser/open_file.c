/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:41:52 by anaji             #+#    #+#             */
/*   Updated: 2023/07/27 11:58:36 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"
#include <sys/fcntl.h>

void	close_files(t_list *lst, int type)
{
	t_buffer	*bf;
	t_list		*prev;

	prev = NULL;
	while (lst)
	{
		bf = (t_buffer *)lst -> content;
		if (bf -> type == type)
		{
			if (prev)
			{
				ft_close_fd(prev -> content);
				prev = NULL;
			}
			prev = lst;
		}
		lst = lst -> next;
	}
}

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
			fd = open(file[0], O_WRONLY | O_APPEND);
		else
			fd = open(file[0], O_CREAT | O_APPEND | O_WRONLY, 0644);
	}
	if (fd == -1)
	{
		perror(file[0]);
		g_exit_status = 1;
	}
	free(*file);
	file[0] = ft_itoa(fd);
	return (fd);
}

t_list	*find_next_pipe(t_list *lst)
{
	t_buffer	*bf;

	while (lst)
	{
		bf = lst -> content;
		if (bf -> type == 7)
			break ;
		lst = lst -> next;
	}
	return (lst);
}

int	check_file(char **str, int type, int *exit_code)
{
	char	*tmp;

	if (!ft_strncmp(*str, "$?", 0))
	{
		tmp = ft_itoa(g_exit_status);
		free(*str);
		*str = tmp;
	}
	if (!ft_strncmp(*str, "-1", 0))
	{
		*exit_code = -1;
		return (-1);
	}
	if (open_file(str, type, 0) == -1)
	{
		*exit_code = -1;
		return (-1);
	}
	return (0);
}

int	open_files(t_list *lst)
{
	t_buffer	*bf;
	t_list		*prev;
	int			exit_code;

	prev = NULL;
	exit_code = 0;
	while (lst)
	{
		bf = (t_buffer *)lst-> content;
		if (bf -> type > 2 && bf -> type < 6)
		{
			remove_quote(&bf->str);
			if (check_file(&bf->str, bf->type, &exit_code) == -1)
				break ;
		}
		lst = lst -> next;
	}
	lst = find_next_pipe(lst);
	if (lst)
		exit_code = open_files(lst->next);
	return (exit_code);
}
