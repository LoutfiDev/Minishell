/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:41:51 by anaji             #+#    #+#             */
/*   Updated: 2023/07/15 15:09:37 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"
#include "../includes/expand.h"
#include "../includes/exec.h"
#include <stdint.h>

/*	algorithm	*/

// 1 - expand all the strings that have a dollar in a new listw list
// 2 - join the original str with the data (content) based on type:
// 2 - 1 - if (') is before dollar then skip
// 2 - 2 - if (" / $) then join one str (before '$') with the item in list
//		eg :"$USER" => "anaji"
// 3 - split that resault in a new list based on type
// 3 - 1 - if (' / ") is found nothing to be done
// 3 - 2 - if nothing is found then split that resault str based on space
//		eg (a="abcd     efgh") $a => |abcd| -> |efgh| -> |NULL|

void	expanding(t_list **head, t_list *_env)
{
	t_buffer	*tmp;
	t_list		*node;
	t_list		*expanded_node;
	char		*var;
	int			index;

	expanded_node = NULL;
	node = *head;
	while (node)
	{
		tmp = (t_buffer *) node -> content;
		var = ft_strdup(tmp -> str);
		if (tmp->type != 6 && has_dollar(tmp->str))
		{
			expanded_node = expand(tmp, _env);
			node = insert_node(head, node, expanded_node);
			if (check_redirection(expanded_node, var))
			{
				ft_lstclear(head, clear_buffer);
				g_exit_status = 1;
			}
		}
		else
			node = node -> next;
		free(var);
	}
}

char	*join_expanded_str(char *str, char type, t_list **lst)
{
	char	*tmp;
	char	*join;
	int		i;

	i = 0;
	join = NULL;
	while (str && str[i])
	{
		if (str[i] == '$')
		{
			tmp = ft_substr(str, 0, i);
			join = ft_strjoin(join, tmp);
			join = ft_join(join, lst);
			i++;
			to_next(str, &i);
			tmp = join_expanded_str(str + i, type, lst);
			join = ft_strjoin(join, tmp);
			return (join);
		}
		i++;
	}
	return (ft_strdup(str));
}

char	*join_all(char *str, t_list *lst, int i)
{
	int		d_index;
	char	*res;
	char	*join;
	char	type;
	char	*tmp;

	join = NULL;
	while (i < ft_strlen (str) && str[i])
	{
		d_index = 0;
		type = get_expand_type(str + i);
		skip_to_next(str + i, &d_index, type);
		res = ft_substr(str + i, 0, d_index);
		if (type == '\'')
			join = join_str(join, res, &lst);
		else
		{
			tmp = join_expanded_str(res, type, &lst);
			join = ft_strjoin(join, tmp);
			free(res);
		}
		i += d_index;
	}
	ft_lstclear(&lst, clear_buffer);
	return (join);
}

void	get_splited_parts(char *str, t_list **head, int type)
{
	t_buffer	*buff;
	int			i;
	static int	d_quotes;
	static int	s_quotes;
	char		*tmp;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' && d_quotes % 2 == 0 && s_quotes % 2 == 0)
			break ;
		if (str[i] == '"' && s_quotes % 2 == 0)
			d_quotes++;
		if (str[i] == '\'' && d_quotes % 2 == 0)
			s_quotes++;
		i++;
	}
	tmp = ft_substr(str, 0, i);
	buff = new_buffer(tmp, type);
	free(tmp);
	ft_lstadd_back(head, ft_lstnew(buff));
	ft_skip_space(str, &i);
	if (!str[i])
		return ;
	return (get_splited_parts(str + i, head, type));
}

t_list	*expand(t_buffer *bf, t_list *env)
{
	int		i;
	char	*tmp;
	t_list	*lst;
	char	*res;
	t_list	*head;

	i = 0;
	lst = NULL;
	while (bf -> str[i])
	{
		tmp = get_var(bf -> str, &i);
		tmp = get_var_value(env, tmp);
		head = ft_lstnew(new_buffer(tmp, 0));
		free(tmp);
		ft_lstadd_back(&lst, head);
	}
	res = join_all(bf -> str, lst, 0);
	lst = NULL;
	tmp = ft_strtrim(res, " \t");
	get_splited_parts(tmp, &lst, bf  -> type);
	free(tmp);
	return (lst);
}
