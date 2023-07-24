/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:22:27 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/24 20:22:43 by yloutfi          ###   ########.fr       */
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
# include "buffer.h"
# include <sys/wait.h>

# define PIPE_NODE 124
# define EXEC_NODE 126

# define SUCCESS 0
# define ERROR 1
# define READ_END 0
# define WRITE_END 1

# define EXP_ERR ": not a valid identifier\n"

//helpers function
void	print_error(char *cmd, char *arg, char *msg, int exit_code);
char	*get_path(char *str, t_list *env);
t_list	*create_env(char **env);
t_env	*create_env_node(char *content);
t_env	*create_node(char *key, char *value);
char	*ft_argsjoin(char *s1, char	*s2);
char	*join_path(char *cmd, t_list *_env);
int		is_builtin(char	*cmd);
int		nbr_options(t_list *_buffer);
char	**fill_options(t_list *_buffer);
int		is_valide(char *str);
int		set_oldpwd(t_list **env);

//exec_expand function
void	expand_array(t_exec	**node);

//builtins commands
void	exec_echo(char **args, int fd);
void	exec_cd(char **args, t_list **env, int fd);
void	exec_pwd(int fd);
void	exec_export(char **args, t_list **env, int fd);
void	exec_unset(char **args, t_list **env);
void	exec_env(t_list *env, int fd, int export);
void	exec_exit(char **args);
int		exec_builtin(t_exec *node, t_list **_env);

//exec functions
int		ft_fork(void);
char	*join_path(char *cmd, t_list *_env);
void	_exec(t_exec *node, t_list **_env, char **envp);
void	dup_files(int infile, int outfile);
void	_close(int infile, int outfile);

//pipe function
void	_pipe(t_pipe *node, int *p, t_list **_env, char **envp);

//execution function
void	execution(t_mask *mask, t_list **_env, char **envp);

//build_tree function
t_mask	*build_tree(t_list *_buffer, t_list *_env);

//free functions
void	ft_free_array(char **array, int index);
void	clear_env(void *content);
void	clear_buffer(void *content);
void	free_tree(t_mask *root);
void	free_exec(t_exec *exec_node);

//signals handling
void	sig_handler(int signum);
void	rl_replace_line(const char *text, int clear_undo);

#endif
