/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:16:21 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/16 09:42:53 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/buffer.h"
#include <sys/wait.h>

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
int	is_builtin(t_exec *node, t_list *_env)
{
	if (!ft_strncmp(node->cmd, "cd", ft_strlen(node->cmd)))
		exec_cd(ft_split(node->opt, ' '), _env);
	else if (!ft_strncmp(node->cmd, "echo", ft_strlen(node->cmd)))
		exec_echo(ft_split(node->opt, ' '));
	else if (!ft_strncmp(node->cmd, "env", ft_strlen(node->cmd)))
		exec_env(_env, 0);
	else if (!ft_strncmp(node->cmd, "exit", ft_strlen(node->cmd)))
		exec_exit(ft_split(node->opt, ' '));
	else if (!ft_strncmp(node->cmd, "export", ft_strlen(node->cmd)))
		exec_export(ft_split(node->opt, ' '), &_env);
	else if (!ft_strncmp(node->cmd, "pwd", ft_strlen(node->cmd)))
		exec_pwd();
	else if (!ft_strncmp(node->cmd, "unset", ft_strlen(node->cmd)))
		exec_unset(ft_split(node->opt, ' '), &_env);
	else
		return (0);
	return (1);
}

void	_exec(t_exec *node, t_list *_env)
{
	char	**array;

	if (!is_builtin(node, _env))
	{
		array = create_array(node->cmd, node->opt);
		if (array[0][0] != '/' && ft_strncmp(array[0], "./", 2))
			node->cmd = join_path(array[0], _env);
		if (!node->cmd)
			ft_exit(print_error("minishell", ": ", array[0],
						": command not found\n", 127));
	}
	if (ft_fork() == 0)
	{
		if (node->infile != 0)
		{
			close(READ_END);
			dup(node->infile);
			close(node -> infile);
		}
		if (node->outfile != 1)
		{	
			close(WRITE_END);
			dup(node->outfile);
			close(node->outfile);
		}
		execve(node->cmd, array, NULL);
		ft_exit(ERROR);	
		exit(1);
	}
	wait(0);
}

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		ft_exit(print_error(NULL, NULL, NULL, "fork failed\n", ERROR));
	return (pid);
}

void	_pipe(t_pipe *node, int *p, t_list *_env)
{
	g_exit_status = 0;
	if (pipe(p) < 0)
		ft_exit(print_error(NULL, NULL, NULL, "pipe failed\n", ERROR));
	if (ft_fork() == 0)
	{
		close(WRITE_END);
		dup(p[WRITE_END]);
		close(p[READ_END]);
		close(p[WRITE_END]);
		execution(node->left, _env);
		exit(0);
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
	int		*p;

	p = _init_pipe();
	if (root->mask == PIPE_NODE)
		_pipe((t_pipe *)root, p, _env);
	else if (root->mask == EXEC_NODE)
		_exec((t_exec *)root, _env);
	free(p);
}
