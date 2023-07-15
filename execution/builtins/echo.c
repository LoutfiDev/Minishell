/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:10:31 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/15 14:51:36 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	is_valid_option(char **args, int *index)
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
	}
	return (0);
}

void	exec_echo(char **args)
{
	int	i;
	int	j;
	int	option;

	if (!args)
	{
		write(1, "\n", 1);
		return ;
	}
	i = 0;
	option = is_valid_option(args, &i);
	while (args[i])
	{
		j = 0;
		if ((option && i > 1) || (!option && i > 0))
			write(1, " ", 1);
		while (args[i][j])
			write(1, &args[i][j++], 1);
		i++;
	}
	if (!option)
		write(1, "\n", 1);
	ft_exit(0);
}
