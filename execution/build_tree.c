/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:25:16 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/15 11:38:18 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

t_exec	*init_exec(void)
{
	t_exec	*exec_node;

	exec_node = malloc(sizeof(t_exec));
	ft_memset(exec_node, 0, sizeof(t_exec));
	exec_node->mask = EXEC_NODE;
	return (exec_node);
}

t_mask	*build_pipe(t_mask *left, t_mask *right)
{
	t_pipe		*pipe_node;

	pipe_node = malloc(sizeof(t_pipe));
	ft_memset(pipe_node, 0, sizeof(t_pipe));
	pipe_node->mask = PIPE_NODE;
	pipe_node->left = left;
	pipe_node->right = right;
	return ((t_mask *)pipe_node);
}

t_mask	*build_exec(t_list *_buffer)
{
	t_exec		*exec_node;
	t_buffer	*buff_node;

	exec_node = init_exec();
	ft_close(_buffer);
	while (_buffer)
	{
		buff_node = (t_buffer *)_buffer->content;
		if (buff_node->type == 7)
			break ;
		else if (buff_node->type == 1)
			exec_node->cmd = ft_strdup(buff_node->str);
		else if (buff_node->type == 2)
			exec_node->opt = ft_argsjoin(exec_node->opt, buff_node->str);
		else if (buff_node->type == 3)
			exec_node->infile = ft_close(ft_atoi(buff_node->str));
		else if (buff_node->type == 4)
			exec_node->outfile = ft_close(ft_atoi(buff_node->str));
		else if (buff_node->type == 5)
			exec_node->outfile = ft_close(ft_atoi(buff_node->str));
		else if (buff_node->type == 6)
			exec_node->infile = ft_close(ft_atoi(buff_node->str));
		_buffer = _buffer->next;
	}
	return ((t_mask *)exec_node);
}

t_list	*pipe_finder(t_list *_buffer)
{
	t_list		*tmp;
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
	return (mask);
}
