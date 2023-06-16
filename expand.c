/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:43:10 by anaji             #+#    #+#             */
/*   Updated: 2023/06/16 14:57:39 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "expand.h"
#include "libft/libft.h"

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

t_list	*expand(t_buffer *node, char **env)
{
	int		i;
	char	*tmp;
	char	*var;
	t_list	*lst;
	char	*res;
	t_list *head;
	t_buffer *bf;

	i = 0;
	lst = NULL;
	while (node ->str[i])
	{
		tmp = get_var(node->str, &i);
		head = ft_lstnew(new_buffer(get_var_value(env, tmp), 0));
		//bf = (t_buffer *) head ->content;
		//printf("str = %s\n",bf->str);
		ft_lstadd_back(&lst, head);
	}
	res = join_all(node->str, lst);
	lst = NULL;
	get_splited_parts(res, &lst, node->type);
	return (lst);
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

char	*join_all(char *str, t_list *data)
{
	char	*tmp;
	int		i;
	int		end;
	char	*join;
	char	delim;

	join = NULL;
	i = 0;
	while (str[i])
	{
		end = get_dollar(str + i);
		tmp = ft_substr(str + i, 0, end);
		delim = is_expandable(str + i, end);
		if (delim == '"' || delim == 1)
		{
			join = ft_strjoin(join, ft_join(tmp, data));
			data = data -> next;
			get_var(str, &i);
		}
		else
			join = ft_strjoin(join, ft_strjoin(tmp,  get_var(str, &i)));
		end = get_next_var(str + i, delim);
		tmp = ft_substr(str + i, 0, end);
		join = ft_strjoin(join, tmp);
		i += end;
	}
	return (join);
}

void	get_splited_parts(char *str, t_list **head, int type)
{
	t_buffer	*buff;
	int			i;
	static int	d_quotes = 0;
	static int	s_quotes = 0;
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
	if (i)
	{
		buff = new_buffer(ft_substr(str, 0, i), type);
		ft_lstadd_back(head, ft_lstnew(buff));
		ft_skip_space(str, &i);
		return (get_splited_parts(str + i, head, type));
	}
}

