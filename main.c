/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:40:55 by anaji             #+#    #+#             */
/*   Updated: 2023/07/08 15:15:33 by anaji            ###   ########.fr       */
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
#include "buffer.h"
#include "libft/get_next_line.h"
#include "libft/libft.h"
#include "parsing.h"
#include <errno.h>

//1 -> find the start delim 
//1.1 -> no delim go to 1 (pretend that we hav a delim 
//		(with his own type(no delim means a cmd ha sbeen founded)))
//1.2 -> have a delim go to 2
//2 -> skip all spces (that endicar-te end of that argument)
//3 -> get next arg type (find end delim and copy)
//4 -> repeat 1 tell '\0'

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

int	has_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	expanding(t_list **head, t_list *_env)
{
	t_buffer	*tmp;
	t_list		*node;
	t_list		*expanded_node;
	int			index;

	node = *head;
	while (node)
	{
		tmp = (t_buffer *) node -> content;
		if (tmp->type != 6 && has_dollar(tmp->str))
		{
			expanded_node = expand((t_buffer *)node ->content, _env);
			insert_node(head, node, expanded_node);
		}
		node = node -> next;
	}
}

void	write_out(int p, char **env, char **av)
{
	int pid, a;
	char *h;
	//close(p[1]);
	h = malloc(10000);
	a = read(p, h, 10000);
	printf("str = %s\n", h);
	/*while (a > 0)
	{
		free(h);
		h = malloc(100);
		a = read(p, h, 100);
		printf("a = %d",a);
		printf("%s\n",h);
	}*/
}

// 1 - parse
// 2 - expand
// 3 - remove quotes
// 4 - rearange
// 5 - send

int	main(int ac, char *av[], char **env)
{
	char	*trim; 	
	char	*buff;
	t_list *head, *tmp;
	int delim;
	t_buffer *bf;;
	t_quote *n_quote;
	t_list	*_env;
	int		*here_doc;
	char *h;
	int pid;

	_env = create_env(env);
	n_quote = malloc(sizeof(t_quote));
	while (1)
	{
		head = NULL;
		n_quote->num_squote = 0;
		n_quote->num_dquote = 0;
		buff  = readline("token here : ");
		trim  = ft_strtrim(buff, " \t");
		parsing(trim, delim, n_quote, &head);
		free(trim);
		if (head)
			add_history(buff); 
		free(buff);
		expanding(&head, _env);
		handle_quote(head);
		tmp = head;
		while (tmp)
		{
			bf = (t_buffer *)tmp -> content;
			if (bf ->type == 6)
			{
				//here_doc = malloc(2 * sizeof(int));
				//pipe(here_doc);
				here_doc = read_here_doc(bf->str, here_doc, is_herdoc_expandable(bf->str), _env);
				close(here_doc[1]);
				write_out(here_doc[0], env, av+1);
				close(here_doc[0]);
				close(here_doc[1]);
			}
			tmp = tmp-> next;
		}
		/*while (tmp)
		{
			bf = (t_buffer *) tmp -> content;
			printf("str = %s\t type = %d\n",bf->str, bf->type);
			tmp = tmp ->next;
		}*/
		//printf("sQ = %d dQ = %d\n", n_quote->num_squote, n_quote->num_dquote);
		ft_lstclear(&head, clear_buffer);
	}
		
}
