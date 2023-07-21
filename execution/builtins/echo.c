/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:10:31 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/21 10:28:30 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	is_valid_option(char **args, int *index, int *nbr)
{
	int	i;
	int	option;

	option = 0;
	while (!ft_strncmp(args[*index], "-n", 2))
	{
		i = 2;
		while (args[*index][i])
			if (args[*index][i++] != 'n')
				return (option);
		option = 1;
		*index += 1;
		*nbr += 1;
	}
	return (option);
}

void	exec_echo(char **args, int fd)
{
	int	i;
	int	option;
	int	nbr;

	g_exit_status = 0;
	if (!args)
	{
		write(fd, "\n", 1);
		return ;
	}
	i = 0;
	nbr = 0;
	option = is_valid_option(args, &i , &nbr);
	while (args[i])
	{
		if ((option && i > nbr) || (!option && i > 0))
			write(fd, " ", 1);
		ft_putstr_fd(args[i++], fd);
	}
	if (!option)
		write(fd, "\n", 1);
}
