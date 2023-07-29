/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:35:50 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/29 16:24:16 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/buffer.h"
#include "../includes/expand.h"
#include "../includes/struct.h"

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

char	*get_value(char *str)
{
	if (!ft_strncmp(str, "$$", ft_strlen(str) + 2))
		return (ft_strjoin(str, ft_strdup("\0")));
	if (!ft_strncmp(str, "$?", ft_strlen(str) + 2))
	{
		free(str);
		return (ft_itoa(g_exit_status));
	}
	else
		return (str);
	free(str);
	return (ft_strdup("\0"));
}

char	*get_expanded(char *str, int i)
{
	char	*tmp;
	t_list	*lst;
	char	*res;
	t_list	*head;
	t_quote	q;

	q.num_dquote = 0;
	q.num_squote = 0;
	lst = NULL;
	while (str[i])
	{
		tmp = get_var(str + i, &i, &q);
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
	if ((*node)->cmd && ft_strnstr((*node)->cmd, "$?",
			ft_strlen((*node)->cmd) + 2))
		(*node)->cmd = get_expanded((*node)->cmd, 0);
	while ((*node)->opt && (*node)->opt[i])
	{
		if (ft_strnstr((*node)->opt[i], "$?", ft_strlen((*node)->opt[i]) + 2))
			(*node)->opt[i] = get_expanded((*node)->opt[i], 0);
		i++;
	}
}
