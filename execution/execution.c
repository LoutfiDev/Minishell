/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:16:21 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/26 19:17:47 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/buffer.h"
#include <sys/wait.h>

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		print_error(NULL, NULL, "fork failed\n", ERROR);
	return (pid);
}

void	dup_files(int infile, int outfile)
{
	if (infile == -1 || outfile == -1)
		exit(1);
	if (infile != 0)
		if (dup2(infile, READ_END) == -1)
			printf("infile dup failed\n");
	if (outfile != 1)
		if (dup2(outfile, WRITE_END) == -1)
			printf("dup outfile failed\n");
}

void	_close(int infile, int outfile)
{
	if (infile == -1 || outfile == -1)
		return ;
	if (infile != 0)
		close(infile);
	if (outfile != 1)
		close(outfile);
}

int	*_init_pipe(void)
{
	int	*p;

	p = ft_calloc(sizeof(int *), 2);
	if (!p)
		return (NULL);
	return (p);
}

void	execution(t_mask *root, t_list **_env, char **envp)
{
	int		*p;

	p = _init_pipe();
	if (root->mask == PIPE_NODE)
	{
		g_exit_status = 0;
		_pipe((t_pipe *)root, p, _env, envp);
	}
	else if (root->mask == EXEC_NODE)
		_exec((t_exec *)root, _env, envp);
	free(p);
}
