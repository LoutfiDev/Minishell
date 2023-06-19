/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:43:10 by anaji             #+#    #+#             */
/*   Updated: 2023/06/18 17:02:43 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "expand.h"
#include "libft/libft.h"
#include <sys/_types/_null.h>

void sh(t_list *head)
{
	t_buffer *bf;
	while (head)
	{
		bf = (t_buffer *) head -> content;
		printf("str = %s\t type = %d\n",bf->str, bf->type);
		head = head ->next;
	}
}

char	*ft_join(char *str, t_list *lst)
{
	t_buffer	*bf;
	char		*res;

	bf = (t_buffer *)lst -> content;
	res = ft_strjoin(str, bf -> str);
	free(str);
	return (res);
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
		i++;
	}
	return ('$');
}

void	skip_to_next(char *str, int *i, int delim)
{
	int	num;

	num = 0;
	while (str[*i])
	{
		if (str[*i] == delim)
			num++;
		else if (num >= 2)
			break ;
		if (delim == '$' && num >= 2)
			break ;
		*i += 1;
	}
}

int	to_next(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == '"' || str[*i] == '\'' | str[*i] == ' ')
			return (*i + 1);
		if (str[*i] == '$')
			break ;
		*i +=  1;
	}
	return (*i);
}

char	*join_str(char *str, char type, t_list **lst)
{
	int		start;
	char	*tmp;
	char	*join;
	int		i;

	i = 0;
	join = NULL;
	start = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp = ft_substr(str, start, i - start);
			join = ft_strjoin(join, tmp);
			join = ft_join(join, *lst);
			*lst = (*lst) -> next;
			i++;
			to_next(str, &i);
			join = ft_strjoin(join, join_str(str + i, type, lst));
			return (join);
		}
		i++;
	}
	join = ft_strjoin(join, str);
	return (join);
}

// 1 - check for dollar (get his index) => int d_index
// 2 - check if there is a (' / ") before that dollar (while i < d_index)
// 3 - skip to next delim (' / ")
// 3 - expand based on type

char	*join_all(char *str, t_list *lst)
{
	int		i;
	int		d_index;
	char	*res;
	char	*join;
	char	type;

	i = 0;
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
			join = ft_strjoin(join, join_str(res, type, &lst));
		i += d_index;
	}
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
	buff = new_buffer(ft_substr(str, 0, i), type);
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
	t_list *head;

	i = 0;
	lst = NULL;
	while (node ->str[i])
	{
		tmp = get_var(node->str, &i);
		head = ft_lstnew(new_buffer(get_var_value(env, tmp), 0));
		free(tmp);
		ft_lstadd_back(&lst, head);
	}
	res = join_all(node->str, lst);
	lst = NULL;
	get_splited_parts(ft_strtrim(res, " \t"), &lst, node->type);
	free(res);
	return (lst);
}
