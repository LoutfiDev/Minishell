/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:22:27 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/15 10:34:57 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H


# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>
# include "struct.h"

# define PIPE_NODE 124
# define EXEC_NODE 126

# define SUCCESS 0
# define ERROR 1
# define READ_END 0
# define WRITE_END 1

# define EXP_ERR ": not a valid identifier\n"

//helpers function
int		print_error(char *cmd, char *lim, char *arg, char *msg, int exit_code);
char	*get_path(char *str, t_list *env);
t_list	*create_env(char **env);
t_env	*create_env_node(char *content);
t_env	*create_node(char *key, char *value);
char	*ft_argsjoin(char *s1, char	*s2);

//builtins commands
void	exec_echo(char **args, int write_end);
int		exec_cd(char **args, t_list *env);
void	exec_pwd(int fd);
int		exec_export(char **args, t_list **env, int *exit_status);
void	exec_unset(char **args, t_list **env);
void	exec_env(t_list *env, int export);
void	exec_exit(char **args, int *exit_code);

//execution functions
t_mask	*build_tree(t_list *_buffer);
int		ft_fork(void);
void	execution(t_mask *mask, t_list *_env);

//free functions
void	ft_free_array(char **array, int index);
void	clear_env(void *content);
void	clear_buffer(void *content);
void	free_tree(t_mask *root);
int		ft_close(int fd);
#endif
