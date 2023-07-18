/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:16:21 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/18 19:09:26 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/buffer.h"
#include <sys/wait.h>

int	is_builtin(char	*cmd)
{	
	if (!ft_strncmp(cmd, "cd", 0))
		return(0);
	else if (!ft_strncmp(cmd, "echo", 0))
		return (0);
	else if (!ft_strncmp(cmd, "env", 0))
		return (0);
	else if (!ft_strncmp(cmd, "exit", 0))
		return (0);
	else if (!ft_strncmp(cmd, "export", 0))
		return (0);
	else if (!ft_strncmp(cmd, "pwd", 0))
		return (0);
	else if (!ft_strncmp(cmd, "unset", 0))
		return (0);
	return (1);
}

char	*join_path(char *cmd, t_list *_env)
{
	char	**array;
	char	*path;
	int		status;
	int		i;

	i = 0;
	if (!is_builtin(cmd))
		return (cmd);
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
	return (cmd);
}

void	expand_array(t_exec	**node)
{
	int	i;
	
	i = 0;
	if (!ft_strncmp((*node)->cmd, "$?", 0))
	{
		free((*node)->cmd);
		(*node)->cmd = ft_itoa(g_exit_status);
	}
	while ((*node)->opt && (*node)->opt[i])
	{
		if (!ft_strncmp((*node)->opt[i], "$?", 0))
		{
			free((*node)->opt[i]);
			(*node)->opt[i] = ft_itoa(g_exit_status);
		}
		i++;
	}
}

int	exec_builtin(t_exec *node, t_list *_env)
{
	expand_array(&node);	
	if (!ft_strncmp(node->cmd, "cd", 0))
		exec_cd(node->opt + 1, _env);
	else if (!ft_strncmp(node->cmd, "echo", 0))
		exec_echo(node->opt + 1);
	else if (!ft_strncmp(node->cmd, "env", 0))
		exec_env(_env, 0);
	else if (!ft_strncmp(node->cmd, "exit", 0))
		exec_exit(node->opt + 1);
	else if (!ft_strncmp(node->cmd, "export", 0))
		exec_export(node->opt + 1, &_env);
	else if (!ft_strncmp(node->cmd, "pwd", 0))
		exec_pwd();
	else if (!ft_strncmp(node->cmd, "unset", 0))
		exec_unset(node->opt + 1, &_env);
	else
		return (1);
	return (0);
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

void	_exec(t_exec *node, t_list *_env, char **envp)
{
	int		pid;
	int		status;

	if (exec_builtin(node, _env) && node->cmd)
	{
		expand_array(&node);
		if (node->cmd[0] != '/' && ft_strncmp(node->cmd, "./", 2))
			return (print_error("minishell", ": ", node->cmd,
						": command not found\n", 127));
		if ((pid = ft_fork()) == 0)
		{
			signal(SIGINT, SIG_DFL);
			dup_files(node->infile, node->outfile);
			execve(node->cmd, node->opt, envp);
			exit(1);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else
			g_exit_status = 1;
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

void	_pipe(t_pipe *node, int *p, t_list *_env, char **envp)
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
		execution(node->left, _env, envp);
		exit(0);
	}
	if (ft_fork() == 0)
	{
		close(READ_END);
		dup(p[READ_END]);
		close(p[READ_END]);
		close(p[WRITE_END]);
		execution(node->right, _env, envp);
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

void	execution(t_mask *root, t_list *_env, char **envp)
{
	int		*p;

	p = _init_pipe();
	if (root->mask == PIPE_NODE)
		_pipe((t_pipe *)root, p, _env, envp);
	else if (root->mask == EXEC_NODE)
		_exec((t_exec *)root, _env, envp);
	free(p);
}
