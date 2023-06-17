/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:10:31 by yloutfi           #+#    #+#             */
/*   Updated: 2023/06/16 10:18:45 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_echo(char **args, int write_end)
{
	int	i;
	int	j;
	int	option;

	i = 0;
	option = 0;
	if (!ft_strncmp(args[0], "-n", ft_strlen(args[0])))
	{
		option = 1;
		i++;
	}
	while (args[i])
	{
		j = 0;
		if ((option && i > 1) || (!option && i > 0))
			write(write_end, " ", 1);
		while (args[i][j])
			write(write_end, &args[i][j++], 1);
		i++;
	}
	if (!option)
		write(write_end, "\n", 1);
}
