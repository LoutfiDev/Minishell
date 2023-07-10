/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:55:40 by anaji             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/06/07 11:15:56 by anaji            ###   ########.fr       */
=======
/*   Updated: 2023/06/22 13:04:12 by anaji            ###   ########.fr       */
>>>>>>> AI
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include <stdio.h>

<<<<<<< HEAD
int	ft_is_heredoc(char c, char c_plus, t_delim *delimiter)
{
	if (c == '<' && c_plus == '<')
	{
		//ft_init_redection(delimiter);
		delimiter -> type = HERE_DOC;
=======
int	ft_is_heredoc(char c, char c_plus, int *type)
{
	if (c == '<' && c_plus == '<')
	{
		*type = HERE_DOC;
>>>>>>> AI
		return (1);
	}
	return (0);
}

<<<<<<< HEAD
int	ft_is_read(char c, t_delim *delimiter)
{
	if (c == '<')
	{
		//ft_init_redection(delimiter);
		delimiter -> type = IN;
=======
int	ft_is_read(char c, int *type)
{
	if (c == '<')
	{
		*type = IN;
>>>>>>> AI
		return (1);
	}
	return (0);
}

<<<<<<< HEAD
int	ft_is_append(char c, char c_plus, t_delim *delimiter)
{
	if (c == '>' && c_plus == '>')
	{
		// ft_init_redection(delimiter);
		delimiter -> type = OUT_APP;
=======
int	ft_is_append(char c, char c_plus, int *type)
{
	if (c == '>' && c_plus == '>')
	{
		*type = OUT_APP;
>>>>>>> AI
		return (1);
	}
	return (0);
}

<<<<<<< HEAD
int	ft_is_write(char c, t_delim *delimiter)
{
	if (c == '>')
	{
		// ft_init_redection(delimiter);
		delimiter -> type = OUT_WRITE;
=======
int	ft_is_write(char c, int *type)
{
	if (c == '>')
	{
		*type = OUT_WRITE;
>>>>>>> AI
		return (1);
	}
	return (0);
}
