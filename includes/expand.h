/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:53:06 by anaji             #+#    #+#             */
/*   Updated: 2023/07/11 08:50:03 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "struct.h"

char	*get_var(char *str, int *i);
char	*get_var_value(t_list *env, char *key);
void	skip_to_next(char *str, int *i, int delim);
int		to_next(char *str, int *i);
int		is_expand_delim(char c);

int		get_dollar(char *str, int *end);
int		get_expand_type(char *str);
char	*ft_join(char *str, t_list **lst);

char	*join_expanded_str(char *str, char type, t_list **lst);
char	*join_str(char *to_join, char *str, t_list **lst);
char	*join_all(char *str, t_list *lst, int i);
void	get_splited_parts(char *str, t_list **head, int type);
void	get_splited_parts(char *str, t_list **head, int type);

#	endif // !EXPAND_H
