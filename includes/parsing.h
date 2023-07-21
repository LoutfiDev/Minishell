/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:56:49 by anaji             #+#    #+#             */
/*   Updated: 2023/07/19 13:35:17 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PARSING_H
# define PARSING_H

# include "struct.h"

void	ft_skip_space(char *str, int *i);
int		get_start_delim(char *str, int *i, int *type, int *delim);
int		is_delim(char c);
int		get_next_delim(char *str, int i, int *delim, t_quote *quotes);
int		get_type(char *str, int type, int i, int *cmd);
int		create_pipe(char *str, int type, t_quote *quote, t_list **lst);
int		parsing(char *str, int delim, t_quote *quote, t_list **head);

#	endif // !PARSING_H
