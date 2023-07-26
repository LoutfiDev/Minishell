/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:54:46 by anaji             #+#    #+#             */
/*   Updated: 2023/07/25 13:18:29 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"
#include <readline/history.h>

void	ft_exit(int exit_state)
{
	g_exit_status = exit_state;
}

void	eof_exit(char *tmp)
{
	if (!tmp)
	{
		write(2, "exit\n", 5);
		exit(g_exit_status);
	}
}
