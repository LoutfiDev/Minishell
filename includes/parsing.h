/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:56:49 by anaji             #+#    #+#             */
/*   Updated: 2023/07/11 08:50:09 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PARSING_H
# define PARSING_H

# include "struct.h"

void	ft_skip_space(char *str, int *i);
int		get_start_delim(char *str, int i, int *type, int *delim);
int		is_delim(char c);
int		get_next_delim(char *str, int i, int *delim, t_quote *quotes);
int		get_type(char *str, int type, int i, int *cmd);
void	create_pipe(char *str, int type, t_quote *quote, t_list **lst);
void	parsing(char *str, int delim, t_quote *quote, t_list **head);

#	endif // !PARSING_H
