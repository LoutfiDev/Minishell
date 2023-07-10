/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:25:13 by yloutfi           #+#    #+#             */
/*   Updated: 2023/06/16 10:13:45 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
}
