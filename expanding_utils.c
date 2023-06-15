/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:02:54 by anaji             #+#    #+#             */
/*   Updated: 2023/06/15 18:06:19 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "libft/libft.h"

int	is_expand_delim(char c)
{
	return (c == ' ' || c == '"' || c == '$' || c == '\'' || c == '\0');
}

char	*get_var(char *str , int *i)
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
		else if (dolar == 1 && is_expand_delim(str[*i]))
			break ;
		*i += 1;
	}
	res = ft_substr(str, start, (*i) - start);
	return (res);
}

int	get_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			break ;
		i++;
	}
	return (i);
}

char	*get_var_value(char **env, char *key)
{
	int		i;
	int		len;
	char	*tmp;

	tmp = ft_strjoin(key + 1, "=");
	len = ft_strlen(tmp);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], tmp, len))
		{
			free(tmp);
			return (env[i] + len);
		}
		i++;
	}
	free(tmp);
	return (NULL);
}

int		check_type(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (MANY_ARG);
		else if (str[i] == '"')
			return (ONE_ARG);
		i++;
	}
	return (NO_ARG);
}

int get_end(int type, char *str)
{
	int		i;
	int		end;
	char	c;

	i = 0;
	if (type == ONE_ARG)
		c = '"';
	else if (type == MANY_ARG)
		c = '$';
	else if (type == NO_ARG)
		c = '\'';
	end = 0;
	while (str[i])
	{
		if (str[i] == c)
			end ++;
		if (end >= 2 || (end && c == '$' && is_expand_delim(str[i])))
			break ;
		i++;
	}
	return (i);
}

int	is_expandable(char *str, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (str[i] == '"')
			return ('"');
		else if (str[i] == '\'')
			return ('\'');
		i++;
	}
	return (1);
}

int	get_next_var(char *str, char c)
{
	int	i;

	i = 0;
	if (c == 1)
		return (i);
	while (str[i])
	{
		if (str[i] == c)
			return (i + 1);
		i++;
	}
	return (i);
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
			join = ft_strjoin(join, ft_strjoin(tmp, (char *)data->content));
			data = data -> next;
			get_var(str, &i);
		}
		else
			join = ft_strjoin(join, ft_strjoin(tmp,  get_var(str, &i)));
		end  = get_next_var(str + i, delim);
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
t_list	*expand(t_buffer *node, char **env)
{
	int		i;
	char	*tmp;
	char	*var;
	t_list	*lst;
	char	*res;
	t_buffer *bf; 

	i = 0;
	lst = NULL;
	while (node ->str[i])
	{
		tmp = get_var(node->str, &i);
		ft_lstadd_back(&lst, ft_lstnew(get_var_value(env, tmp)));
	}
	res = join_all(node->str, lst);
	lst = NULL;
	get_splited_parts(res, &lst, node->type);
	return (lst);	

}

