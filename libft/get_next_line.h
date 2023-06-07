/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:27:49 by anaji             #+#    #+#             */
/*   Updated: 2023/06/03 08:18:10 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdint.h>

char	*get_next_line(int fd);
void	*ft_mmove(void *dst, void *src, size_t len);
void	*ft_mset(void *b, int c, size_t len);
char	*ft_mcalloc(size_t count, size_t size, char *str);
char	*strjoin(char *s1, char *s2, int len);
int		ft_len(char *s);
int		find_me_next(char *buf);
char	*ft_cpy(char *src, int len);
char	*next_line(int fd, char *buff, char **holder, int *index);
char	*init(int *index, char *holder, char **res);

#	endif
