/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:12:05 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/16 15:55:40 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	nbr_args(char **args)
{
	int	nbr_args;

	nbr_args = 0;
	while (args[nbr_args])
		nbr_args++;
	return (nbr_args);
}

int	is_digit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

void	exec_exit(char **args)
{	
	if (!args || !args[0])
	{
		ft_putstr_fd("exit\n", 1);
		g_exit_status = 0;
		exit(0);
	}
	else if (is_digit(args[0]))
		print_error("exit\nexit: ", NULL, args[0],
				": numeric argument required\n", 255);
	else if (nbr_args(args) > 1)
		print_error("exit\nexit: ", NULL, NULL,
				"too many arguments\n", 1);
	else
	{
		g_exit_status = ft_atoi(args[0]) % 256;
		ft_putstr_fd("exit\n", 1);
	}
	exit(g_exit_status);
}
