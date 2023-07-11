/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:40:55 by anaji             #+#    #+#             */
/*   Updated: 2023/07/11 13:29:07 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <sys/_types/_null.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../includes/buffer.h"
#include "../includes/parsing.h"
#include "../includes/exec.h"
#include <errno.h>

void	open_heredoc(t_list *head, t_list *_env)
{
	t_buffer	*bf;
	int			*here_doc;

	while (head)
	{
		bf = (t_buffer *)head -> content;
		if (bf ->type == 6)
		{
			here_doc = read_here_doc(bf->str, is_herdoc_expandable(bf->str),
					_env);
			close(here_doc[1]);
			free(bf->str);
			bf->str = ft_itoa(here_doc[0]);
			free(here_doc);
		}
		head = head -> next;
	}
}

t_list	*main_parse(t_list *env)
{
	char	*line;
	t_list	*buffer;
	t_quote	*quotes;
	int		pid;

	quotes = malloc(sizeof(t_quote));
	quotes -> num_dquote = 0;
	quotes -> num_squote = 0;
	buffer = NULL;
	line = ft_strtrim(readline("MINISHELL : "), " \t");
	parsing(line, 1, quotes, &buffer);
	if (buffer)
		add_history(line);
	free(line);
	handle_quote(buffer);
	open_heredoc(buffer, env);
	free(quotes);
	return (buffer);
}

int	main(int ac, char **av, char **env)
{
	t_list	*head;
	t_list	*_env;

	_env = create_env(env);
	while (1)
	{
		head = main_parse(_env);
		ft_lstclear(&head, clear_buffer);
	}
	return (0);
}
