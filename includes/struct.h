/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 08:16:08 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/15 07:22:35 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../libft/libft.h"

int	exit_status;

typedef struct s_quote
{
	int	num_squote;
	int	num_dquote;
	int	type;
}	t_quote;

typedef struct s_buffer
{
	char	*str;
	int		type;
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
	char	*infile;
	char	*outfile;
	int		out_mode;
}	t_exec;

#endif
