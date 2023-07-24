/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:29:19 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/24 13:37:12 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/buffer.h"
#include <sys/wait.h>

int	exec_builtin(t_exec *node, t_list *_env)
{
	expand_array(&node);
	if (!ft_strncmp(node->cmd, "cd", 0))
	{
		set_oldpwd(&_env);
		exec_cd(node->opt + 1, _env, node->outfile);
	}
	else if (!ft_strncmp(node->cmd, "echo", 0))
		exec_echo(node->opt + 1, node->outfile);
	else if (!ft_strncmp(node->cmd, "env", 0))
		exec_env(_env, node->outfile, 0);
	else if (!ft_strncmp(node->cmd, "exit", 0))
		exec_exit(node->opt + 1);
	else if (!ft_strncmp(node->cmd, "export", 0))
		exec_export(node->opt + 1, &_env, node->outfile);
	else if (!ft_strncmp(node->cmd, "pwd", 0))
		exec_pwd(node->outfile);
	else if (!ft_strncmp(node->cmd, "unset", 0))
		exec_unset(node->opt + 1, &_env);
	else
		return (1);
	_close(node->infile, node->outfile);
	return (0);
}
