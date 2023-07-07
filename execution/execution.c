/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:16:21 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/07 11:58:04 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_array(char **array)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (array[len])
		len++;
	while (i <= len)
		free(array[i++]);
	free(array);
	return ;
}

char	*join_path(char *cmd, t_list *_env)
{
	char	**array;
	char	*path;
	int		status;
	int		i;

	i = 0;
	if (!cmd)
		return (NULL);
	array = ft_split(get_path("PATH", _env), ':');
	while (array[i])
	{
		path = ft_strjoin(ft_strjoin(array[i++], "/"), cmd);
		status = access(path, F_OK);
		if (status != -1)
		{
			ft_free_array(array);
			return (path);
		}
		free(path);
	}
	ft_free_array(array);
	return (NULL);
}

void	_exec(t_exec *node, t_list *_env)
{
	pid_t	id_ls;
	char	**array;

	id_ls = fork();
	if (id_ls < 0)
		exit (ERROR);
	else if (id_ls == 0)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			exit (ERROR);
		if (dup2(node->outfile, STDOUT_FILENO) == -1)
			exit (ERROR);
		array = ft_split(ft_argsjoin(node->cmd, node->opt), ' ');
		if (array[0][0] != '/')
			node->cmd = join_path(array[0], _env);
		execve(node->cmd, array, NULL);
		exit (ERROR);
	}
}
void	execution(t_mask *root, t_list *_env)
{
	// if (root->mask == PIPE_NODE)
	// 	_pipe((t_pipe *)root, _env);
	// else if (root->mask == EXEC_NODE)
	// 	_exec((t_exec *)root, _env);
	if (root->mask == EXEC_NODE)
		_exec((t_exec *)root, _env);
}