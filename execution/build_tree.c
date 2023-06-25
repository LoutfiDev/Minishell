/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:25:16 by yloutfi           #+#    #+#             */
/*   Updated: 2023/06/24 12:58:28 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_mask	*build_exec(t_list *_buffer)
{
	t_exec		*exec_node;
	t_buffer	*buff_node;
	t_list		*tmp;

	exec_node = malloc(sizeof(t_exec));
	tmp = _buffer;
	while(tmp)
	{
		buff_node = (t_buffer *)tmp->content;
		if (buff_node->type == 7)
			break;
		if (buff_node->type == 1)
			exec_node->cmd = buff_node->str;
		if (buff_node->type == 2)
			exec_node->opt = ft_strjoin(exec_node->opt, buff_node->str);
		if (buff_node->type == 3)
			exec_node->infile = buff_node->str;
		if (buff_node->type == 4)
			exec_node->outfile = buff_node->str;
		if (buff_node->type == 5)
			exec_node->cmd = buff_node->str;
	}
	retrun((t_mask *)exec_node);
}
t_list	*pipe_finder(t_list *_buffer)
{
	t_list	*tmp;
	t_buffer	*buff;
	
	tmp = _buffer;
	while (tmp)
	{
		buff = (t_buffer *)tmp->content;
		if (buff->type == 7)
			return (tmp->next);
		tmp = tmp->next;
	}
	return (NULL);
}
t_mask	*build_tree(t_list *_buffer)
{
	t_list	*tmp;
	t_mask	*mask;

	mask = NULL;
	tmp = pipe_finder(_buffer);
	if (!tmp)
		mask = build_exec(_buffer);
	else
		mask = build_pipe(build_exec(_buffer), build_tree(tmp));
	retrun (mask);
}