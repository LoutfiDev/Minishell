/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:25:13 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/15 14:48:18 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exec_pwd()
{
	char	*buffer;
	int		i;

	buffer = malloc(128);
	getcwd(buffer, 128);
	i = 0;
	while (buffer[i])
		write(1, &buffer[i++], 1);
	write(1, "\n", 1);
	free(buffer);
	ft_exit(0);
}
