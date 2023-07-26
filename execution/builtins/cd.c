/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:08:36 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/25 16:30:55 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	set_oldpwd(t_list **env)
{
	char	*current_dir;
	t_env	*env_node;
	t_list	*tmp;

	current_dir = ft_strdup(get_path("PWD", *env));
	if (!current_dir)
	{
		current_dir = malloc(128);
		getcwd(current_dir, 128);
	}
	tmp = (*env);
	while (tmp)
	{
		env_node = (t_env *)tmp->content;
		if (!ft_strncmp(env_node->key, "OLDPWD", 0))
		{
			free(env_node->value);
			env_node->value = current_dir;
			return (0);
		}
		tmp = tmp->next;
	}
	env_node = create_node(ft_strdup("OLDPWD"), current_dir);
	ft_lstadd_back(env, ft_lstnew(env_node));
	return (0);
}

int	set_pwd(t_list **env)
{
	char	*current_dir;
	t_env	*env_node;
	t_list	*tmp;

	current_dir = malloc(128);
	getcwd(current_dir, 128);
	tmp = (*env);
	while (tmp)
	{
		env_node = (t_env *)tmp->content;
		if (!ft_strncmp(env_node->key, "PWD", 0))
		{
			free(env_node->value);
			env_node->value = current_dir;
			return (0);
		}
		tmp = tmp->next;
	}
	env_node = create_node(ft_strdup("PWD"), current_dir);
	ft_lstadd_back(env, ft_lstnew(env_node));
	return (0);
}

void	exec_cd(char **args, t_list **env, int fd)
{
	DIR		*directory;

	if (!ft_strncmp(args[0], "~", 0))
	{
		if (!get_path("HOME", *env))
			chdir(getenv("HOME"));
		else
			chdir(get_path("HOME", *env));
	}
	else if (!ft_strncmp(args[0], "-", 0))
	{
		if (!get_path("OLDPWD", *env))
			return (print_error("cd: ", "OLDPWD", ": not set\n", 1));
		chdir(get_path("OLDPWD", *env));
		exec_pwd(fd);
	}
	else
	{
		directory = opendir(args[0]);
		if (!directory)
			return (print_error("cd: ", args[0], ": Not a directory\n", 1));
		chdir(args[0]);
		closedir(directory);
	}
	ft_exit(set_pwd(env));
}
