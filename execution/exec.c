/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:22:31 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/22 15:02:38 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/buffer.h"
#include <sys/wait.h>

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
	if (!is_builtin(cmd))
		return (ft_strdup(cmd));
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
	return (ft_strdup(cmd));
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
