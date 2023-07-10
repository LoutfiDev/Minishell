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
#include <errno.h>


//1 -> find the start delim 
//1.1 -> no delim go to 1 (pretend that we hav a delim (with his own type(no delim means a cmd ha sbeen founded)))
//1.2 -> have a delim go to 2
//2 -> skip all spces (that endicar-te end of that argument)
//3 -> get next arg type (find end delim and copy)
//4 -> repeat 1 tell '\0'


int	get_start_delim(char *str, int i, int *type, int *delim)
{
	*delim = 1;
	if (ft_is_heredoc(str[i], str[i + 1], type) || ft_is_append(str[i], str[i + 1], type))
		return (2);
	if (ft_is_read(str[i], type) || ft_is_write(str[i], type))
		return (1);
	else
		return (0);
}

/*
char	*get_arg(char *str, int *index, t_delim *delim)
{
	int		i;
	int		quote;
	int		dquote;
	int		skip;
	char	*tmp;

	skip = 0;
	quote = 0;
	dquote = 0;
	i = (*index);
	while (str[i])
	{
		if ((is_delim(str[i], str[i + 1], delim) && quote % 2 == 0
					&& dquote % 2  == 0))
			break ;
		if (str[i] == '\'' && dquote % 2 == 0)
			quote++;
		if (str[i] == '\"' && quote % 2 == 0)
			dquote++;
		i++;
	}
	tmp = ft_substr(str, *index, i - (*index));
	*index = i;
	return (tmp);
}
*/

int	is_delim(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == ' ');
}

int	get_next_delim(char *str, int i, int *delim, t_quote *quotes)
{
	if ((is_delim(str[i]) && *delim) || !str[i])
	{
		printf("syntax error");
		//exit(1);
	}
	while (str[i])
	{
		if (is_delim(str[i]) && !(*delim)
				&& quotes->num_squote % 2 == 0 && quotes->num_dquote % 2  == 0)
			break ;
		if (str[i] == '\'' && quotes->num_dquote % 2 == 0)
			quotes->num_squote++;
		if (str[i] == '\"' && quotes->num_squote % 2 == 0)
			quotes->num_dquote++;
		*delim = 0;
		i++;
	}
	return (i);
}

int	get_type(char *str, int type, int i, int *cmd)
{
	if (type)
		return (type);
	else if (str[i] == '|')
		return (PIPE);
	else if (*cmd == 0)
	{
		*cmd = 1;
		return (1);
	}
	return (2);
}

void	parsing(char *str, int delim, t_quote *quote, t_list **head)
{
	int	i;
	int	cmd;
	int	type;
	char *tmp;
	t_list *buf;
	int j;

	cmd = 0;
	i = 0;
	while (str[i])
	{
		type = 0;
		ft_skip_space(str, &i);
		i += get_start_delim(str, i, &type, &delim);
		ft_skip_space(str, &i);
		type = get_type(str, type, i, &cmd);
		if (type == PIPE)
		{
			tmp = ft_strdup("|");
			buf = ft_lstnew(new_buffer(tmp, type));
			ft_lstadd_back(head, buf);
			return (parsing(str + i + 1, 1, quote, head));
		}
		j = i;
		i = get_next_delim(str, i, &delim, quote);
		tmp = ft_substr(str, j, i - j);
		buf = ft_lstnew(new_buffer(tmp, type));
		ft_lstadd_back(head, buf);
	}
}

void	expanding(t_list *head, char **env)
{
	t_buffer	*tmp;
	t_list		*node;
	t_list		*expanded_node;
	int			index;

	node = head;
	while (node)
	{
		tmp = (t_buffer *) node -> content;
		if (tmp->type != 6)
			expanded_node = expand(&head, node, env);
		node = node -> next;
	}
}

int main(int ac, char *av[], char **env)
{
	char	*trim; 	
	char	*buff;
	t_list *head;
	int delim;
	t_buffer *bf;;
	t_quote *n_quote;

	n_quote = malloc(sizeof(t_quote));
	while (1)
	{
		head = NULL;
		n_quote->num_squote = 0;
		n_quote->num_dquote = 0;
		buff  = readline("token here : ");
		trim  = ft_strtrim(buff, " \t\v\f");
		parsing(trim, delim, n_quote, &head);
		//expanding(head, env);
		if (head)
			add_history(buff); 
		while (head)
		{
			bf = (t_buffer *) head -> content;
			printf("str = %s\t type = %d\n",bf->str, bf->type);
			head = head ->next;

		}
		//printf("sQ = %d dQ = %d\n", n_quote->num_squote, n_quote->num_dquote);
	}

}


