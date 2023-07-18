/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:19:27 by anaji             #+#    #+#             */
/*   Updated: 2023/07/18 20:23:52 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"
#include "../includes/exec.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int	get_key(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '$' || str[i] == '\'' || str[i] == '"')
			break ;
		i++;
	}
	return (i);
}

char	*var_value(char *name, t_list *env, int *len)
{
	t_env	*values;
	char	*key;		
	int		i;

	i = get_key(name);
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

char	*expand_in_heredoc(char *tmp, int expandable, t_list *env)
{
	int		i;
	char	*res;
	int		start;
	int		len;

	i = 0;
	start = 0;
	res = NULL;
	if (!expandable || !has_dollar(tmp))
		return (tmp);
	while (tmp[i])
	{
		if (tmp[i] == '$')
		{
			res = ft_strjoin(res, ft_substr(tmp, start, i - start));
			res = ft_strjoin(res, var_value(tmp + i + 1, env, &len));
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

int	*read_here_doc(char *lim, int expand, t_list *env)
{
	char	*in;
	int		len;
	int		*pip;

	pip = malloc(2 * sizeof(int));
	pipe(pip);
	if (fork() == 0)
	{
		signal(SIGINT, SIG_DFL);
		len = ft_strlen(lim);
		if ((in = readline("> ")) == NULL)
			exit(0);
		while (ft_strncmp(lim, in, ft_strlen(in) + len))
		{
			in = ft_strjoin(expand_in_heredoc(in, expand, env), ft_strdup("\n"));
			write(pip[1], in, ft_strlen(in));
			free(in);
			if ((in = readline("> ")) == NULL)
				exit(0);
		}
		exit(0);
		free(in);
	}
	wait(0);
	return (pip);
}
