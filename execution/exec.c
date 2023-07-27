/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:22:31 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/27 12:41:55 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/buffer.h"
#include <sys/unistd.h>
#include <sys/wait.h>

int	is_dir(char **path)
{
	DIR		*directory;

	if (!path && !path[0])
		return (0);
	directory = opendir(path[0]);
	if (directory)
	{
		if (!ft_strncmp(path[0], ".", 0))
		{
			print_error("minishell: ", path[0],
				": filename argument required\n", 2);
			ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		}
		else if (!ft_strncmp(path[0], "..", 0))
			print_error("minishell: ", path[0],
				": command not found\n", 127);
		else
			print_error("minishell: ", path[0], ": is a directory\n", 126);
		closedir(directory);
		return (1);
	}
	return (0);
}

int	is_builtin(char	*cmd)
{	
	if (!ft_strncmp(cmd, "cd", 0))
		return (0);
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
	if (!is_builtin(cmd) || cmd[0] == '\0' || !_env)
		return (ft_strdup(cmd));
	array = ft_split(get_path("PATH", _env), ':');
	while (array && array[i])
	{
		path = ft_strjoin(array[i++], ft_strdup("/"));
		path = ft_strjoin(path, ft_strdup(cmd));
		status = access(path, F_OK | X_OK);
		if (status != -1)
		{
			ft_free_array(array, i);
			return (path);
		}
		free(path);
	}
	ft_free_array(array, i);
	return (ft_strdup(cmd));
}

void	_exec(t_exec *node, t_list **_env, char **envp)
{
	int		pid;
	int		status;

	if (exec_builtin(node, _env) && node->cmd && !is_dir(node->opt))
	{
		if (node->cmd[0] != '/' && ft_strncmp(node->cmd, "./", 2))
			return (print_error("minishell:",
					node->cmd, " : command not found\n", 127));
		pid = ft_fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			dup_files(node->infile, node->outfile);
			execve(node->cmd, node->opt, envp);
			exit(ERROR);
		}
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
		else
			g_exit_status = WEXITSTATUS(status);
	}
}
