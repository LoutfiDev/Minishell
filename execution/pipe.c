/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:20:39 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/24 20:20:20 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/buffer.h"
#include <sys/wait.h>

void	_pipe(t_pipe *node, int *p, t_list **_env, char **envp)
{
	int	pid1;
	int	pid2;
	int	status;

	if (pipe(p) < 0)
		print_error(NULL, NULL, "pipe failed\n", ERROR);
	if ((pid1 = ft_fork()) == 0)
	{
		dup2(p[WRITE_END], WRITE_END);
		_close(p[READ_END], p[WRITE_END]);
		execution(node->left, _env, envp);
		exit(g_exit_status);
	}
	if ((pid2 = ft_fork()) == 0)
	{
		dup2(p[READ_END], READ_END);
		_close(p[READ_END], p[WRITE_END]);
		execution(node->right, _env, envp);
		exit(g_exit_status);
	}
	_close(p[READ_END], p[WRITE_END]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}
