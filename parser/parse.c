/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:06:42 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/14 20:32:19 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"
#include <unistd.h>

int	add_history(const char *str);

// 1 - parse
// 2 - send
// 3 - build tree
// 4 - expand
// 5 - remove quotes
// 6 - execute

/*
 * parsing algorithm
 * */
//1 -> find the start delim
//1.1 -> no delim go to 1 (pretend that we hav a delim
//		(with his own type(no delim means a cmd ha sbeen found)))
//1.2 -> have a delim go to 2
//2 -> skip all spces (that endicate end of that argument)
//3 -> get next arg type (find end delim and copy)
//4 -> repeat 1 tell '\0'

void	check_pipe_node(t_list *lst)
{
	t_buffer	*bf_start;
	t_buffer	*bf_last;

	bf_start = lst -> content;
	bf_last = ft_lstlast(lst) -> content;
	if (bf_start -> type == 7 || bf_last ->type == 7)
	{
		write(2, "syntax error near unexpected token `|'\n", 39);
		ft_exit(2);
	}
}

t_list	*main_parse(t_list *env)
{
	char	*line;
	t_list	*buffer;
	t_quote	*quotes;
	//int		pid;

	quotes = malloc(sizeof(t_quote));
	quotes -> num_dquote = 0;
	quotes -> num_squote = 0;
	buffer = NULL;
	line = ft_strtrim(readline("MINISHELL : "), " \t");
	parsing(line, 0, quotes, &buffer);
	if (buffer)
		add_history(line);
	free(line);
	check_pipe_node(buffer);
	open_heredoc(buffer, env);
	check_quotes(quotes);
	free(quotes);
	return (buffer);
}

void	create_pipe(char *str, int type, t_quote *quote, t_list **lst)
{
	char	*tmp;
	t_list	*buf;

	tmp = ft_strdup("|");
	buf = ft_lstnew(new_buffer(tmp, type));
	free(tmp);
	ft_lstadd_back(lst, buf);
	parsing(str, 1, quote, lst);
}

void	parsing(char *str, int delim, t_quote *quote, t_list **head)
{
	int		i[2];
	int		cmd;
	int		type;
	char	*tmp;
	t_list	*buf;

	i[0] = 0;
	cmd = 0;
	while (str && str[i[0]])
	{
		type = 0;
		ft_skip_space(str, &i[0]);
		i[0] += get_start_delim(str, i[0], &type, &delim);
		ft_skip_space(str, &i[0]);
		type = get_type(str, type, i[0], &cmd);
		if (type == PIPE)
			return (create_pipe(str + i[0] + 1, type, quote, head));
		i[1] = i[0];
		i[0] = get_next_delim(str, i[0], &delim, quote);
		tmp = ft_substr(str, i[1], i[0] - i[1]);
		buf = ft_lstnew(new_buffer(tmp, type));
		free(tmp);
		ft_lstadd_back(head, buf);
	}
}
