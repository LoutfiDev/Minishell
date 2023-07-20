/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:25:13 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/19 20:16:08 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exec_pwd(int fd)
{
	char	*buffer;
	int		i;

	buffer = malloc(128);
	getcwd(buffer, 128);
	i = 0;
	while (buffer[i])
		write(fd, &buffer[i++], 1);
	write(fd, "\n", 1);
	free(buffer);
	ft_exit(0);
}
