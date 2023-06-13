/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:39:30 by anaji             #+#    #+#             */
/*   Updated: 2023/06/10 12:54:53 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

// end paramtere for end of expanding
// type to specify if taht str well be expandable or not

int	*create_tab(int end, int type)
{
	int	*tab;

	tab = malloc(2 * sizeof(int));
	tab[0] = end;
	tab[1] = type;
	return (tab);
}
