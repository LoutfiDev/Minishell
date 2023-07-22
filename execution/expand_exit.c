/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:35:50 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/22 21:23:02 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/buffer.h"
#include "../includes/expand.h"

void	quote_remover(char **str)
{
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	tmp = ft_strdup(*str);
	free(*str);
	len = get_tmp_len(tmp);
	ft_cpy_new(tmp, str, len);
	free(tmp);
}

char	*sub_var(char *str, int *i)
{
	int		start;
	int		dolar;
	char	*res;

	dolar = 0;
	while (str[*i])
	{
		if (str[*i] == '$' && dolar == 0)
		{
			dolar++;
			start = *i;
		}
		else if (dolar == 1 && !ft_isalnum(str[*i]) && str[*i] != '?')
			break ;
		*i += 1;
	}
	res = ft_substr(str, start, (*i) - start);
	return (res);
}

char	*get_value(char *str)
{
	if (!ft_strncmp(str, "$?", ft_strlen(str) + 2))
	{
		free(str);
		return (ft_itoa(g_exit_status));
	}
	free(str);
	return (ft_strdup("\0"));
}

char	*get_expanded(char *str)
{
	int		i;
	char	*tmp;
	t_list	*lst;
	char	*res;
	t_list	*head;

	i = 0;
	lst = NULL;
	while (str[i])
	{
		tmp = sub_var(str, &i);
		tmp = get_value(tmp);
		head = ft_lstnew(new_buffer(tmp, 0));
		free(tmp);
		ft_lstadd_back(&lst, head);
	}
	res = join_all(str, lst, 0);
	quote_remover(&res);
	free(str);
	return (res);
}

void	expand_array(t_exec	**node)
{
	int	i;

	i = 0;
	if (ft_strnstr((*node)->cmd, "$?", ft_strlen((*node)->cmd) + 2))
		(*node)->cmd = get_expanded((*node)->cmd);
	while ((*node)->opt && (*node)->opt[i])
	{
		if (ft_strnstr((*node)->opt[i], "$?", ft_strlen((*node)->opt[i]) + 2))
			(*node)->opt[i] = get_expanded((*node)->opt[i]);
		i++;
	}
}

// void	expand_array(t_exec	**node)
// {
// 	int	i;
//
// 	i = 0;
// 	if (!ft_strncmp((*node)->cmd, "$?", 0))
// 	{
// 		free((*node)->cmd);
// 		(*node)->cmd = ft_itoa(g_exit_status);
// 	}
// 	while ((*node)->opt && (*node)->opt[i])
// 	{
// 		if (!ft_strncmp((*node)->opt[i], "$?", 0))
// 		{
// 			free((*node)->opt[i]);
// 			(*node)->opt[i] = ft_itoa(g_exit_status);
// 		}
// 		i++;
// 	}
// }
