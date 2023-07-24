/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:06:42 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/23 21:47:57 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"
#include "../includes/exec.h"
#include <stdlib.h>

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

// void	remove_normal_quote(t_list *lst, t_quote *quote)
// {
// 	t_buffer	*bf;
//
// 	while (lst)
// 	{
// 		bf = (t_buffer *)lst -> content;
// 		if (!has_dollar(bf -> str) && (quote->num_dquote
// 				|| quote -> num_squote))
// 			remove_quote(&bf -> str);
// 		lst = lst -> next;
// 	}
// }

int	check_pipe_node(t_list *lst)
{
	t_buffer	*bf_start;
	t_buffer	*bf_last;
	int			check;

	check = 0;
	if (!lst)
		return (-1);
	bf_start = lst -> content;
	bf_last = ft_lstlast(lst)-> content;
	if (bf_start -> type == 7 || bf_last ->type == 7)
		check = 1;
	while (lst && lst -> next)
	{
		bf_start = lst->content;
		bf_last = lst -> next->content;
		if (bf_start -> type == bf_last -> type && bf_start -> type == 7)
			check = 1;
		lst = lst -> next;
	}
	if (!check)
		return (0);
	write(2, "syntax error near unexpected token `|'\n", 39);
	g_exit_status = 2;
	return (-1);
}

int	check_parse(t_list **buffer, t_list *env, t_quote *quotes)
{
	if (check_pipe_node(*buffer) == -1)
		return (error_protocol(buffer, quotes));
	else if (open_heredoc(*buffer, env) == -1)
	{
		g_exit_status = 1;
		return (error_protocol(buffer, quotes));
	}
	else if (check_num_quotes(quotes) == -1)
		return (error_protocol(buffer, quotes));
	open_files(*buffer);
	handle_quote(*buffer);
	free(quotes);
	return (0);
}

t_list	*main_parse(t_list *env)
{
	t_list	*buffer;
	t_quote	*quotes;
	char	*tmp;
	char	*line;

	tmp = readline("MINISHELL : ");
	eof_exit(tmp);
	signal(SIGINT, SIG_IGN);
	if (!tmp)
		exit(g_exit_status);
	line = ft_strtrim(ft_strdup(tmp), " \t");
	quotes = malloc(sizeof(t_quote));
	quotes -> num_dquote = 0;
	quotes -> num_squote = 0;
	buffer = NULL;
	if (parsing(line, 0, quotes, &buffer) == -1)
		return (free(tmp), free(line), NULL);
	free(line);
	expanding(&buffer, env);
	if (buffer)
		add_history(tmp);
	free(tmp);
	if (check_parse(&buffer, env, quotes) == -1)
		return (NULL);
	return (re_arrange_buffer(buffer, 0));
}

int	create_pipe(char *str, int type, t_quote *quote, t_list **lst)
{
	char	*tmp;
	t_list	*buf;

	tmp = ft_strdup("|");
	buf = ft_lstnew(new_buffer(tmp, type));
	free(tmp);
	ft_lstadd_back(lst, buf);
	parsing(str, 1, quote, lst);
	return (0);
}

int	parsing(char *str, int delim, t_quote *quote, t_list **head)
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
		get_start_delim(str, &i[0], &type, &delim);
		type = get_type(str, type, i[0], &cmd);
		if (type == PIPE)
			return (create_pipe(str + i[0] + 1, type, quote, head));
		i[1] = i[0];
		i[0] = get_next_delim(str, i[0], &delim, quote);
		if (i[0] == -1)
			return (error_protocol(head, quote));
		tmp = ft_substr(str, i[1], i[0] - i[1]);
		buf = ft_lstnew(new_buffer(tmp, type));
		free(tmp);
		ft_lstadd_back(head, buf);
	}
	return (0);
}
