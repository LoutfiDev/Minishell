/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:16:21 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/11 08:27:34 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

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

int	open_infile(char *filename, char *cmd)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1 && !access(filename, F_OK))
	{
		close(fd);
		exit(print_error(cmd, ": ", filename, ": permission denied\n", 1));
	}
	else if (fd == -1)
	{
		close(fd);
		exit(print_error(cmd, ": ", filename,
				": No such file or directory\n", 1));
	}
	return (fd);
}

int	open_outfile(char *filename, char *cmd, int mode)
{
	int	fd;

	fd = open(filename, O_CREAT, 0644);
	if (fd == -1)
	{
		perror(filename);
		exit(ERROR);
	}
	close(fd);
	if (!mode)
		fd = open(filename, O_WRONLY | O_TRUNC);
	else
		fd = open(filename, O_WRONLY | O_APPEND);
	if (fd == -1)
		exit(print_error(cmd, ": ", filename, ": permission denied\n", 1));
	return (fd);
}

void	_exec(t_exec *node, t_list *_env)
{
	char	**array;
	int		fd;

	if (node->outfile)
	{
		fd = open_outfile(node->outfile, node->cmd, node->out_mode);
		close(WRITE_END);
		dup(fd);
	}
	array = ft_split(ft_argsjoin(node->cmd, node->opt), ' ');
	if (array[0][0] != '/')
		node->cmd = join_path(array[0], _env);
	if (!node->cmd)
		exit(print_error("minishell", ": ", array[0],
				": command not found\n", 127));
	if (node->infile)
	{
		fd = open_infile(node->infile, array[0]);
		close(READ_END);
		dup(fd);
	}
	execve(node->cmd, array, NULL);
	exit (ERROR);
}

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		exit(print_error(NULL, NULL, NULL, "fork failed\n", ERROR));
	return (pid);
}

void	_pipe(t_pipe *node, int *p, t_list *_env)
{
	if (pipe(p) < 0)
		exit(print_error(NULL, NULL, NULL, "pipe failed\n", ERROR));
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
		exit(0);
	}
	close(p[READ_END]);
	close(p[WRITE_END]);
	wait(0);
	wait(0);
}

int	*_init_pipe(void)
{
	int	*p;

	p = ft_calloc(sizeof(int *), 2);
	if (!p)
		return (NULL);
	return (p);
}

void	execution(t_mask *root, t_list *_env)
{
	int	*p;

	p = _init_pipe();
	if (root->mask == PIPE_NODE)
		_pipe((t_pipe *)root, p, _env);
	else if (root->mask == EXEC_NODE)
		_exec((t_exec *)root, _env);
	free(p);
}
