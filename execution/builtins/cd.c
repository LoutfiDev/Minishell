/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:08:36 by yloutfi           #+#    #+#             */
/*   Updated: 2023/06/16 10:22:03 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_cd(char **args, t_list *env)
{
	DIR		*directory;

	if (!ft_strncmp(args[0], "~", ft_strlen(args[0])))
	{
		if (!get_path("HOME", env))
			return (print_error("cd: ", "HOME", ": not set\n", 1));
		chdir(get_path("HOME", env));
	}
	else if (!ft_strncmp(args[0], "-", ft_strlen(args[0])))
	{
		if (!get_path("OLDPWD", env))
			return (print_error("cd: ", "OLDPWD", ": not set\n", 1));
		chdir(get_path("OLDPWD", env));
		exec_pwd(1);
	}
	else
	{
		directory = opendir(args[0]);
		if (!directory)
			return (print_error("cd: ", args[0], ": Not a directory\n", 1));
		chdir(args[0]);
	}
	return (0);
}
