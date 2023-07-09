/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:19:27 by anaji             #+#    #+#             */
/*   Updated: 2023/07/08 18:31:40 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "libft/libft.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char	*var_value(char *name, t_list *env, int *len)
{
	t_env	*values;
	char	*key;		
	int		i;

	i = 0;
	while (name[i])
	{
		if (name[i] == ' ' || name[i] == '$'
				|| name[i] == '"' || name[i] == '\'')
			break ;
		i++;
	}
	key = ft_substr(name, 0, i);
	*len = i;
	while (env)
	{
		values = env -> content;
		if (!ft_strncmp(key, values -> key, ft_strlen(key)
			+ ft_strlen(values->key)))
		{
			free(key);
			return (ft_strdup(values -> value));
		}
		env = env -> next;
	}
	free(key);
	return (ft_strdup("\0"));
}

char	*expand_in_heredoc(char *str, int expandable, t_list *env)
{
	int		i;
	char	*tmp;
	char	*res;
	char	*var;
	int		start;
	int		len;

	i = 0;
	res = NULL;
	start = 0;
	if (!expandable)
		return (str);
	tmp = ft_strdup(str);
	free(str);
	while (tmp[i])
	{
		if (tmp[i] == '$')
		{
			res = ft_strjoin(res, ft_substr(tmp, start, i - start));
			var = var_value(tmp + i + 1, env, &len);
			res = ft_strjoin(res, var);
			i += len + 1;
			start = i;
		}
		else
			i++;
	}
	res = ft_strjoin(res, ft_substr(tmp, start, i - start));
	free(tmp);
	return (res);
}

int	*read_here_doc(char *lim, int *h_pipe, int expand, t_list *env)
{
	char	*in;
	int		len;
	int		pid;
	int		*pip;

	pip = malloc(2 * sizeof(int));
	pipe(pip);
	pid = fork();
	if (pid == 0)
	{
		len = ft_strlen(lim);
		in = readline("> ");
		while (ft_strncmp(lim, in, ft_strlen(in) + len))
		{
			in = expand_in_heredoc(in, expand, env);
			write(pip[1], in, ft_strlen(in));
			free(in);
			in = readline("> ");
		}
		free(in);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	return (pip);
}

int is_herdoc_expandable(char *hd_lim)
{
	int	i;

	i = 0;
	while (hd_lim[i])
	{
		if (hd_lim[i] == '\'' || hd_lim[i] == '"')
		{
			remove_quote(&hd_lim);
			return (0);
		}
		i++;
	}
	remove_quote(&hd_lim);
	return (1);
}
