/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:54:46 by anaji             #+#    #+#             */
/*   Updated: 2023/07/26 14:30:16 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"
#include "../includes/exec.h"

void	ft_exit(int exit_state)
{
	g_exit_status = exit_state;
}

void	eof_exit(char *tmp)
{
	if (!tmp)
	{
		if (isatty(READ_END))
			write(2, "exit\n", 6);
		exit(g_exit_status);
	}
}
