/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:16:21 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/17 12:30:59 by yloutfi          ###   ########.fr       */
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
			free(cmd);
			return (path);
		}
		free(path);
	}
	free(cmd);
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

void	expand_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		if (!ft_strncmp(array[i], "$?", 0))
		{
			free(array[i]);
			array[i] = ft_itoa(g_exit_status);
		}
		i++;
	}
}

int	is_builtin(t_exec *node, t_list *_env)
{
	char	**array;
	
	array = create_array(node->cmd, node->opt);
	expand_array(array);	
	if (!ft_strncmp(array[0], "cd", 0))
		exec_cd(array + 1, _env);
	else if (!ft_strncmp(array[0], "echo", 0))
		exec_echo(array + 1);
	else if (!ft_strncmp(array[0], "env", 0))
		exec_env(_env, 0);
	else if (!ft_strncmp(array[0], "exit", 0))
		exec_exit(array + 1);
	else if (!ft_strncmp(array[0], "export", 0))
		exec_export(array + 1, &_env);
	else if (!ft_strncmp(array[0], "pwd", 0))
		exec_pwd();
	else if (!ft_strncmp(array[0], "unset", 0))
		exec_unset(array + 1, &_env);
	else
	{
		ft_free_array(array, 0);	
		return (0);
	}
	ft_free_array(array, 0);	
	return (1);
}
void	dup_files(int infile, int outfile)
{
	if (infile == -1 || outfile == -1)
		exit(1);
	if (infile != 0)
	{
		close(READ_END);
		dup(infile);
		close(infile);
	}
	if (outfile != 1)
	{	
		close(WRITE_END);
		dup(outfile);
		close(outfile);
	}
}

void	_exec(t_exec *node, t_list *_env)
{
	char	**array;
	int		pid;
	int		status;

	if (!is_builtin(node, _env) && node->cmd)
	{
		array = create_array(node->cmd, node->opt);
		expand_array(array);
		if (array[0] && array[0][0] != '/' && ft_strncmp(array[0], "./", 2))
			node->cmd = join_path(node->cmd, _env);
		if (!node->cmd)
			return (print_error("minishell", ": ", array[0],
						": command not found\n", 127));
		if ((pid = ft_fork()) == 0)
		{
			dup_files(node->infile, node->outfile);
			execve(node->cmd, array, NULL);
			exit(1);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else
			g_exit_status = 1;
		ft_free_array(array, 0);
	}
}

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		print_error(NULL, NULL, NULL, "fork failed\n", ERROR);
	return (pid);
}

void	_pipe(t_pipe *node, int *p, t_list *_env)
{
	if (pipe(p) < 0)
		print_error(NULL, NULL, NULL, "pipe failed\n", ERROR);
	g_exit_status = 0;
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
