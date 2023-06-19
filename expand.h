/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:53:06 by anaji             #+#    #+#             */
/*   Updated: 2023/06/18 16:44:42 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef EXPAND_H
# define EXPAND_H

#include "buffer.h"

# define ONE_ARG 1
# define MANY_ARG 2
# define NO_ARG 3

int		get_end(int type, char *str);
int		check_type(char *str);
char	*get_var_value(t_list *env, char *key);
int		get_dollar(char *str, int *end);

char	*join_all(char *str, t_list *data);
void	get_splited_parts(char *str, t_list **head, int type);

int		is_expand_delim(char c);
char	*get_var(char *str, int *i);
int		get_next_var(char *str);
int		is_expandable(char *str, int len);

void sh(t_list *lst);
#	endif // !EXPAND_H
