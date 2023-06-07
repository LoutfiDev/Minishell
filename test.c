#include <readline/readline.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/_types/_null.h>
#include <sys/unistd.h>
#include <unistd.h>
#include "buffer.h"
#include "libft/get_next_line.h"
#include "libft/libft.h"
#include <errno.h>


int	is_delim(char c, char c_plus, t_delim *delim)
{
	if (ft_is_heredoc(c, c_plus, delim) || ft_is_append(c, c_plus, delim))
		return (2);
	if (ft_ispipe(c, delim) || ft_is_read(c, delim) || ft_is_write(c, delim)
			|| c == ' ')
		return (1);
	return (0);

}

char	*get_arg(char *str, int *index, t_delim *delim)
{
	int		i;
	int		quote= 0;
	int		dquote = 0;
	char	*tmp;

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

void get_parts(char *str, t_delim *delim, t_buffer **head)
{
	int	i,j;
	char	*in_file;
	char	*out_file;
	char	*cmd;
	char	**args;
	char	*tmp;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	while (str[i])
	{
		len = is_delim(str[i], str[i + 1], delim);
		if (len)
		{
			if (i > 0 && !j)
			{
				cmd = ft_substr(str, 0, i);
				printf("cmd = %s\n", cmd);
			}
			else
			{
				i += len;
				tmp = get_arg(str, &i, delim);
				printf("tmp = %s\n",tmp);
				i--;
				free(tmp);
			}
			j = 1;
		}
		i++;
	}
}

void	ft_free(t_buffer *tmp)
{
	t_buffer *prev;

	while (tmp)
	{
		prev = tmp;
		tmp = tmp->next;
		free(prev);
	}
}

int main(int ac, char *av[], char **env)
{
	char	*trim; 	
	char	*buff;
	t_buffer *head;
	t_delim *delim;

	delim = malloc(sizeof(t_delim));
	head = NULL;
	while (1)
	{
		buff  = readline("token here : ");
		trim  = ft_strtrim(buff, " \t\v\f");
		get_parts(trim, delim, &head);
	}
}


