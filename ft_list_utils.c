/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:37:28 by anaji             #+#    #+#             */
/*   Updated: 2023/06/12 09:09:57 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "libft/libft.h"
#include <readline/readline.h>

t_buffer	*new_buffer(char *str, int type)
{
	t_buffer	*buff;

	buff = malloc(sizeof(t_buffer));
	buff->str = ft_strdup(str);
	buff->type = type;
	return (buff);
}

void	insert_buffer(t_list **head, t_list *node, t_list *n_node)
{

	t_list	*last;

	last = ft_lstlast(n_node);
	last -> next = node -> next;
	node -> next = n_node;
	// t_list		*tmp;
	// t_buffer	*buff;
	// t_buffer	*b_node;
	//
	// tmp = *head;
	// buff = (t_buffer *)tmp -> content;
	// b_node = (t_buffer *)node -> content;
	// if (!ft_strncmp(buff->str, b_node->str, ft_strlen(b_node->str)))
	// {
	// 	free(node);
	// 	head = NULL;
	// 	return (ft_lstadd_front(head, n_node));
	// }
	// while (tmp && tmp -> next)
	// {
	// 	buff = (t_buffer *)tmp -> next -> content;
	// 	if (!ft_strncmp(buff->str, b_node->str, ft_strlen(b_node->str)))
	// 	{
	// 		tmp -> next = n_node;
	// 		n_node -> next = node -> next;
	// 		free(node);
	// 		return ;
	// 	}
	// 	tmp = tmp -> next;
	// }
}

// int main(int argc, char *argv[])
// {
// 	t_list* lst,*tmp;
// 	int i = 0;
// 	char *in;
//
// 	lst = NULL;
// 	while (i < argc)
// 	{
// 		tmp = ft_lstnew(argv[i]);
// 		ft_lstadd_front(&lst, tmp);
// 		i++;
// 	}
// 	i = 0;
// 	tmp = lst;
// 	while (tmp)
// 	{
// 		printf("arg i = %d => %s\n", i, (char *)tmp->content);
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	in = readline("to insert :");
// 	insert_buffer(&lst, t_list *node, t_list *n_node)
// }
