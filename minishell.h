/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:22:27 by yloutfi           #+#    #+#             */
/*   Updated: 2023/06/18 11:52:58 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>

# define CMD 1
# define ARGS 2
# define IN 3
# define OUT_WRITE 4
# define OUT_APP 5
# define HERE_DOC 6
# define PIPE 7

# define EXP_ERR ": not a valid identifier\n"

typedef struct s_buffer
{
	char			*str;
	int				type;
}	t_buffer;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

//helpers function
int		print_error(char *cmd, char *arg, char *msg, int exit_status);
char	*get_path(char *str, t_list *env);
t_list	*create_env(char **env);
t_env	*create_env_node(char *content);
void	ft_lstfree(t_list *env);
char	**split(char *s, char c);

//builtins commands
void	exec_echo(char **args, int write_end);
int		exec_cd(char **args, t_list *env);
void	exec_pwd(int fd);
int		exec_export(char **args, t_list **env, int *exit_status);
void	exec_unset(char **args, t_list **env);
void	exec_env(t_list *env, int export);
void	exec_exit(char **args, int *exit_code);

#endif
