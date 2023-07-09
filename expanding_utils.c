/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:02:54 by anaji             #+#    #+#             */
/*   Updated: 2023/06/24 15:27:39 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "libft/libft.h"
#include "expand.h"

int	get_dollar(char *str, int *end)
{
	int	i;

	*end = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
		*end += 1;
	}
	return (0);
}

int	get_expand_type(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return ('\'');
		else if (str[i] == '"')
			return ('"');
		else if (str[i] == '$')
			break ;
		i++;
	}
	return ('$');
}

char	*ft_join(char *str, t_list **lst)
{
	t_buffer	*bf;
	t_list		*tmp;
	char		*res;

	tmp = *lst;
	bf = (t_buffer *)tmp -> content;
	res = ft_strjoin(str, bf -> str);
	*lst = (*lst)-> next;
	free(bf);
	free(tmp);
	return (res);
}

char	*join_str(char *to_join, char *str, t_list **lst)
{
	t_list		*tmp;
	t_buffer	*bf;

	tmp = *lst;
	bf = tmp -> content;
	to_join = ft_strjoin(to_join, str);
	(*lst) = (*lst) -> next;
	free(bf -> str);
	free(bf);
	free(tmp);
	return (to_join);
}
