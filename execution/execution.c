/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:16:21 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/08 20:23:13 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_array(char **array, int index)
{
	int	i;
	int	len;

	i = index;
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
		path = ft_strjoin(array[i++], ft_strdup("/"));
		path = ft_strjoin(path, ft_strdup(cmd));
		status = access(path, F_OK);
		if (status != -1)
		{
			ft_free_array(array, i);
			return (path);
		}
		free(path);
	}
	ft_free_array(array, i);
	return (NULL);
}

void	_exec(t_exec *node, t_list *_env)
{
	char	**array;

	array = ft_split(ft_argsjoin(node->cmd, node->opt), ' ');
	if (array[0][0] != '/')
		node->cmd = join_path(array[0], _env);
	execve(node->cmd, array, NULL);
	exit (ERROR);
}
int	ft_fork()
{
	int	pid;

	pid = fork();
	if (pid < 0)
		exit(print_error(NULL, NULL, "fork failed\n", ERROR));
	return (pid);
}

void	_pipe(t_pipe *node, int *p, t_list *_env)
{
	if (pipe(p) < 0)
		exit(print_error(NULL, NULL, "pipe failed\n", ERROR));
	if (ft_fork() == 0)
	{
		close(WRITE_END);
		dup(p[WRITE_END]);
		close(p[READ_END]);
		close(p[WRITE_END]);
		execution(node->left, _env);
	}
	if (ft_fork() == 0)
	{
		close(READ_END);
		dup(p[READ_END]);
		close(p[READ_END]);
		close(p[WRITE_END]);
		execution(node->right, _env);
	}
	close(p[READ_END]);
	close(p[WRITE_END]);
	wait(0);
	wait(0);
}

int	*_init_pipe()
{
	int	*p;

	p = ft_calloc(sizeof(int *), 2);
	if (!p)
		return (NULL);
	return (p);
}

void	execution(t_mask *root, t_list *_env)
{
	int *p;

	p = _init_pipe();
	if (root->mask == PIPE_NODE)
		_pipe((t_pipe *)root, p, _env);
	else if (root->mask == EXEC_NODE)
		_exec((t_exec *)root, _env);
	free(p);
}