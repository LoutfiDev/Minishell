/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:56:26 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/26 20:30:36 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef BUFFER_H
# define BUFFER_H

# include <unistd.h>
# include "parsing.h"
# include "struct.h"

# define CMD 1
# define ARGS 2
# define IN 3
# define OUT_WRITE 4
# define OUT_APP 5
# define HERE_DOC 6
# define PIPE 7

void		sh(t_list *lst);

t_buffer	*new_buffer(char *str, int type);
t_list		*insert_node(t_list **head, t_list *node, t_list *n_node);

//parsing utils
char		*ft_readline(void);
t_list		*main_parse(t_list *env);
void		ft_skip_space(char *str, int *i);
t_list		*re_arrange_buffer(t_list *lst, int old_type);

//expanding utils
void		expanding(t_list **lst, t_list *_env);
t_list		*expand(t_buffer *bf, t_list *env, int i);
int			has_dollar(char *str);
int			ft_is_heredoc(char c, char c_plus, int *type);
int			ft_is_read(char c, int *type);
int			ft_is_append(char c, char c_plus, int *type);
int			ft_is_write(char c, int *type);

//general utils function
void		ft_exit(int exit_state);
void		eof_exit(char *str);
void		clear_buffer(void *bf);
void		fix_types(t_list *lst);
int			error_protocol(t_list **lst, t_quote *quote);
t_list		*create_env(char **env);
void		clear_env(void *content);

//remove quotes
int			check_num_quotes(t_quote *quote);
void		handle_quote(t_list *lst);
void		remove_quote(char **str);
void		ft_cpy_new(char *old, char **res, int len);
int			get_tmp_len(char *str);

//open files
int			open_files(t_list *lst);
int			check_redirection(t_list *head, char *str);
void		close_files(t_list *lst, int type);
void		ft_close_fd(t_buffer *bf);

//HERE_DOC
int			*read_here_doc(char *lim, int expand, t_list *env, int *st);
int			is_herdoc_expandable(char *hd_lim);
int			open_heredoc(t_list *lst, t_list *env);
void		clear_heredoc(t_list *lst);
#	endif
