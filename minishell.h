/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:22:27 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/08 20:19:54 by yloutfi          ###   ########.fr       */
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

# define PIPE_NODE 124
# define EXEC_NODE 126

# define SUCCESS 0
# define ERROR 1
# define READ_END 0
# define WRITE_END 1

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

typedef struct s_mask
{
	int	mask;
}	t_mask;

typedef struct s_pipe
{
	int		mask;
	t_mask	*left;
	t_mask	*right;
}	t_pipe;

typedef struct s_exec
{
	int		mask;
	char	*cmd;
	char	*opt;
	int		infile;
	int		outfile;
}	t_exec;

//helpers function
int		print_error(char *cmd, char *arg, char *msg, int exit_status);
char	*get_path(char *str, t_list *env);
t_list	*create_env(char **env);
t_env	*create_env_node(char *content);
t_env	*create_node(char *key, char *value);
void	ft_lstfree(t_list *env);
char	**split(char *s, char c);
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
int		ft_fork();
void	execution(t_mask *mask, t_list *_env);

#endif
