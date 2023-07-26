/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:20:39 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/26 14:22:15 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/buffer.h"
#include <sys/wait.h>

void	exec_left(t_pipe *node, int *p, t_list **_env, char **envp)
{
	dup2(p[WRITE_END], WRITE_END);
	_close(p[READ_END], p[WRITE_END]);
	execution(node->left, _env, envp);
	exit(g_exit_status);
}

void	exec_right(t_pipe *node, int *p, t_list **_env, char **envp)
{
	dup2(p[READ_END], READ_END);
	_close(p[READ_END], p[WRITE_END]);
	execution(node->right, _env, envp);
	exit(g_exit_status);
}

void	_pipe(t_pipe *node, int *p, t_list **_env, char **envp)
{
	int	pid1;
	int	pid2;
	int	status;

	if (pipe(p) < 0)
		print_error(NULL, NULL, "pipe failed\n", ERROR);
	pid1 = ft_fork();
	if (pid1 == 0)
		exec_left(node, p, _env, envp);
	pid2 = ft_fork();
	if (pid2 == 0)
		exec_right(node, p, _env, envp);
	_close(p[READ_END], p[WRITE_END]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}
