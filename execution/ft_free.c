/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:32:39 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/26 15:37:16 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	ft_free_array(char **array, int index)
{
	int	i;
	int	len;

	i = index;
	len = 0;
	if (!array)
		return ;
	while (array[len])
		len++;
	while (i <= len)
		free(array[i++]);
	free(array);
	return ;
}

void	free_exec(t_exec *exec_node)
{
	if (exec_node->cmd)
		free(exec_node->cmd);
	if (exec_node->opt)
		ft_free_array(exec_node->opt, 0);
	_close(exec_node->infile, exec_node->outfile);
	free(exec_node);
}

void	free_tree(t_mask *root)
{
	t_pipe	*pipe_node;
	t_exec	*exec_node;

	if (!root)
		return ;
	if (root->mask == PIPE_NODE)
	{
		pipe_node = (t_pipe *)root;
		free_tree((t_mask *)pipe_node->left);
		free_tree((t_mask *)pipe_node->right);
		free(pipe_node);
	}
	else if (root->mask == EXEC_NODE)
	{
		exec_node = (t_exec *)root;
		free_exec(exec_node);
	}
}

// void	clear_buffer(void *content)
// {
// 	t_buffer	*buffer;

// 	buffer = (t_buffer *)content;
// 	free(buffer->str);
// 	free(buffer);
// }
