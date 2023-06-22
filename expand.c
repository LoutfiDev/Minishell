/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:41:51 by anaji             #+#    #+#             */
/*   Updated: 2023/06/22 11:42:59 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "expand.h"
#include "libft/libft.h"

void	sh(t_list *head)
{
	t_buffer	*bf;

	while (head)
	{
		bf = (t_buffer *) head -> content;
		printf("str = %s\t type = %d\n", bf->str, bf->type);
		head = head ->next;
	}
}

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

char	*join_str(char *str, char type, t_list **lst)
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
			tmp = join_str(str + i, type, lst);
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

	d_index = 0;
	join = NULL;
	while (str[i])
	{
		type = get_expand_type(str + i);
		skip_to_next(str + i, &d_index, type);
		res = ft_substr(str + i, 0, d_index);
		if (type == '\'')
			join = ft_strjoin(join, res);
		else
		{
			tmp = join_str(res, type, &lst);
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

t_list	*expand(t_buffer *node, t_list *env)
{
	int		i;
	char	*tmp;
	t_list	*lst;
	char	*res;
	t_list	*head;

	i = 0;
	lst = NULL;
	while (node ->str[i])
	{
		tmp = get_var(node->str, &i);
		tmp = get_var_value(env, tmp);
		head = ft_lstnew(new_buffer(tmp, 0));
		free(tmp);
		ft_lstadd_back(&lst, head);
	}
	res = join_all(node->str, lst, 0);
	lst = NULL;
	tmp = ft_strtrim(res, " \t");
	free(res);
	get_splited_parts(tmp, &lst, node->type);
	free(tmp);
	return (lst);
}
