/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:06:42 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/11 22:06:51 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buffer.h"


// 1 - parse
// 2 - expand
// 3 - remove quotes
// 4 - rearange
// 5 - send

//1 -> find the start delim 
//1.1 -> no delim go to 1 (pretend that we hav a delim 
//		(with his own type(no delim means a cmd ha sbeen founded)))
//1.2 -> have a delim go to 2
//2 -> skip all spces (that endicar-te end of that argument)
//3 -> get next arg type (find end delim and copy)
//4 -> repeat 1 tell '\0'
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
	open_heredoc(buffer, env);
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
