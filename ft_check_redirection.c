/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:55:40 by anaji             #+#    #+#             */
/*   Updated: 2023/06/22 13:04:12 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include <stdio.h>

int	ft_is_heredoc(char c, char c_plus, int *type)
{
	if (c == '<' && c_plus == '<')
	{
		*type = HERE_DOC;
		return (1);
	}
	return (0);
}

int	ft_is_read(char c, int *type)
{
	if (c == '<')
	{
		*type = IN;
		return (1);
	}
	return (0);
}

int	ft_is_append(char c, char c_plus, int *type)
{
	if (c == '>' && c_plus == '>')
	{
		*type = OUT_APP;
		return (1);
	}
	return (0);
}

int	ft_is_write(char c, int *type)
{
	if (c == '>')
	{
		*type = OUT_WRITE;
		return (1);
	}
	return (0);
}
