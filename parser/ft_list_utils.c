/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:37:28 by anaji             #+#    #+#             */
/*   Updated: 2023/07/26 11:46:39 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"
#include <readline/readline.h>
#include <unistd.h>

t_buffer	*new_buffer(char *str, int type)
{
	t_buffer	*buff;

	buff = malloc(sizeof(t_buffer));
	buff->str = ft_strdup(str);
	buff->type = type;
	return (buff);
}

void	clear_buffer(void *bf)
{
	t_buffer	*tmp_bf;

	tmp_bf = (t_buffer *)bf;
	free(tmp_bf->str);
	free(tmp_bf);
}

void	replace_node(t_list *lst, char *replace, int type)
{
	t_buffer	*bf;

	while (lst)
	{
		bf = (t_buffer *)lst -> content;
		if (bf -> type == type)
		{
			free(bf -> str);
			bf->str = ft_strdup(replace);
		}
		lst = lst-> next;
	}
}

int	check_redirection(t_list *lst, char *str)
{
	t_buffer	*bf_node;
	int			c;
	t_list		*head;

	c = 0;
	head = lst;
	while (lst)
	{
		bf_node = lst ->content;
		if (bf_node -> type >= 3 && bf_node -> type <= 5)
		{
			remove_quote(&bf_node -> str);
			if (c || !ft_strlen(bf_node -> str))
			{
				write(2, str, ft_strlen(str));
				write(2, ": ambiguous redirect\n", 22);
				replace_node(head, "-1", bf_node -> type);
				return (1);
			}
			c++;
		}
		lst = lst -> next;
	}
	return (0);
}

t_list	*insert_node(t_list **head, t_list *node, t_list *n_node)
{
	t_list	*last;
	t_list	*tmp;

	tmp = *head;
	last = ft_lstlast(n_node);
	if (tmp == node)
	{
		ft_lstadd_front(head, n_node);
		last -> next = node-> next;
		ft_lstdelone(node, clear_buffer);
		fix_types(*head);
		return (n_node);
	}
	while (tmp && tmp -> next)
	{
		if (tmp -> next == node)
		{
			tmp -> next = n_node;
			last -> next = node -> next;
			ft_lstdelone(node, clear_buffer);
			return (n_node);
		}
		tmp = tmp -> next;
	}
	return (n_node);
}
