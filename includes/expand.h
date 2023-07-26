/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:53:06 by anaji             #+#    #+#             */
/*   Updated: 2023/07/26 14:18:01 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "struct.h"

char	*get_var(char *str, int *i, t_quote *q);
char	*get_var_value(t_list *env, char *key);
void	skip_to_next(char *str, int *i, int delim);
int		to_next(char *str, int *i, int check, char type);
int		is_expand_delim(char c);

int		get_dollar(char *str, int *end);
int		get_expand_type(char *str);
char	*ft_join(char *str, t_list **lst);

char	*join_expanded_str(char *str, t_list **lst, char *join, char type);
char	*join_str(char *to_join, char *str, t_list **lst);
char	*join_all(char *str, t_list *lst, int i);
void	get_splited_parts(char *str, t_list **head, int type);
void	get_splited_parts(char *str, t_list **head, int type);

#	endif // !EXPAND_H
