/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:16:21 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/15 11:38:33 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/buffer.h"

int	ft_close(int fd)
{
	return (fd);
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

char	**create_array(char *cmd, char *opt)
{
	char	**array;
	char	**opts;
	int		i;
	int		j;
	int		nbr;

	i = 0;
	j = 0;
	nbr = 0;
	opts = ft_split(opt, ' ');
	while (opts && opts[nbr])
		nbr++;
	if (cmd)
		nbr += 1;
	array = malloc((nbr + 1) * sizeof(char *));
	if (cmd)
		array[i++] = ft_strdup(cmd);
	while (i < nbr)
		array[i++] = ft_strdup(opts[j++]);
	ft_free_array(opts, 0);
	array[i] = NULL;
	return (array);
}

void	_exec(t_exec *node, t_list *_env)
{
	char	**array;

	if (node->infile)
	{
		close(READ_END);
		dup(node->infile);
		close(node -> infile);
	}
	if (node->outfile)
	{	
		close(WRITE_END);
		dup(node->outfile);
		close(node->outfile);
	}
	array = create_array(node->cmd, node->opt);
	if (array[0][0] != '/' && ft_strncmp(array[0], "./", 2))
		node->cmd = join_path(array[0], _env);
	if (!node->cmd)
		exit(print_error("minishell", ": ", array[0],
				": command not found\n", 127));
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
		g_exit_status = 0;
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
	int		*p;

	p = _init_pipe();
	if (root->mask == PIPE_NODE)
		_pipe((t_pipe *)root, p, _env);
	else if (root->mask == EXEC_NODE)
		_exec((t_exec *)root, _env);
	free(p);
}
