/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 10:30:15 by anaji             #+#    #+#             */
/*   Updated: 2023/06/13 11:30:01 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <sys/_types/_null.h>

int get_dollar(char *str, int *index, int *quote)
{
	int	i;

	i = *index;
	while (str[i])
	{
		if (str[i] == '$')
		{
			*index = i;
			return (1);
		}
		if (str[i] == '"')
			*quote += 1;
		i++;
	}
	return (0);
}

void get_next(char *str, int *index, int *quote)
{
	while (str[*index])
	{
		if (str[*index] == '$' || str[*index] == '\''
				|| str[*index] == ' ')
			return ;
		if (str[*index] == '"')
		{
			*quote += 1;
			return ;
		}
		*index += 1;
	}
}
int	ft_skip_toclose(char *str, int i, char delim)
{
	int	dollar;

	dollar = 0;
	if (str[i] == '$')
	{
		i++;
		dollar++;
	}
	while (str[i])
	{
		if (str[i] == '$' || str[i] == '"' || str[i] == ' ')
			break ;
		i++;
	}
	return (i - 1);
}

char	*get_var(char **env, char *key)
{
	int		i;
	int		len;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
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


int	*char_limiter(char *str, int index)
{
	int		i;
	int		quote;
	
	i = 0;
	quote = 0;
	while (i < index)
	{
		if (str[i] == '\'')
			return (create_tab(ft_skip_toclose(str, i + 1, '\''), 0));
		else if (str[i] == '"' && (quote) % 2 == 0)
		{
			quote += 1;
			return (create_tab(ft_skip_toclose(str, i + 1, '"'), 2));
		}
		i++;
	}
	return (create_tab(ft_skip_toclose(str, i + 1, '$'), 1));
}

int	has_space(char *s)
{
	int	i;

	i = 0;
	while (s[i++])
		if (s[i] == ' ')
			return (1);
	return (0);
}


t_list	*get_var_parts(char *str, int type)
{
	int		i;
	t_list	*head;
	char	*tmp;
	int		start;

	head = NULL;
	i = 0;
	ft_skip_space(str, &i);
	start = i;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			tmp = ft_substr(str, start, i - start);
			ft_lstadd_back(&head, ft_lstnew(new_buffer(tmp, type)));
			ft_skip_space(str, &i);
			start = i;
		}
		i++;
	}
	tmp = ft_substr(str, start, i - start);
	ft_lstadd_back(&head, ft_lstnew(new_buffer(tmp, type)));
	return (head);
}

// 1 - get dollar index
// 2 - get next delim (" ' space \0 $)
// 3 - copy to str
// 4 - to 1 untill '\0'


int	is_expandable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			return (ONE_ARG);
		else if (str[i] == '\'')
			return (NO_ARG);
		else if (str[i] == '$')
			return (MANY_ARG);
		i++;
	}
	return (0);
}

char	*expand_to_one(char *str)
{
	char	*res;
	int		i;

	i = 0;
	while (str[i])
	{

	}

}

int		get_str(t_buffer *buff,  int i)
{
	int	squote;
	int	dquote;

	squote = 0;
	dquote = 0;
	while (buff -> str[i])
	{
		if (buff -> str[i] == '"' && squote == 0)
			dquote++;
		if (buff -> str[i] == '\'' && dquote == 0)
			squote++;
		if (squote >= 2 || dquote >= 2)
			break ;
		i++;
	}
	return (i);
}

t_list	*expand(t_list **head, t_list *node, char **env)
{
	t_buffer	*buff;
	int			check;
	char		*tmp;
	int			i;
	int			j;
	char		*join;

	i = 0;
	buff = (t_buffer *)node -> content;
	while (buff -> str[i])
	{
		check = is_expandable(buff -> str + i);
		j = get_str(buff, i);
		tmp = ft_substr(buff -> str + i, 0, j);
		if (check == ONE_ARG)
			//printf("one = %s\n",expand_to_one(tmp));
		//else if (check == MANY_ARG)
			//printf("MANY = %s\n", expand_to_many(tmp));
		i += j;
	}
	return (NULL);
}

