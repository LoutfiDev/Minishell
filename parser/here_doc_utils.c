/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:35:39 by anaji             #+#    #+#             */
/*   Updated: 2023/07/11 08:24:29 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"

int	has_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	is_herdoc_expandable(char *hd_lim)
{
	int	i;

	i = 0;
	while (hd_lim[i])
	{
		if (hd_lim[i] == '\'' || hd_lim[i] == '"')
		{
			remove_quote(&hd_lim);
			return (0);
		}
		i++;
	}
	return (1);
}
