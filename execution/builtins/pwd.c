/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:25:13 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/26 12:06:05 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exec_pwd(int fd)
{
	char	*buffer;
	int		i;

	i = 0;
	buffer = malloc(128);
	getcwd(buffer, 128);
	if (!buffer || buffer[0] == '\0')
	{
		print_error("minishell:", " getcwd:",
			" cannot access parent directories", 0);
		free(buffer);
	}
	else
	{
		i = 0;
		while (buffer[i])
			write(fd, &buffer[i++], 1);
		free(buffer);
	}
	write(fd, "\n", 1);
	ft_exit(0);
}
