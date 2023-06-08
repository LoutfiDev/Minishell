#	ifndef BUFFER_H
# define BUFFER_H

#include <readline/readline.h>
# include "libft/libft.h"
# include <unistd.h>

# define CMD 1
# define arg 2
# define IN 3
# define OUT_WRITE 4
# define OUT_APP 5
# define HERE_DOC 6
# define PIPE 7

// # include "readline/readline.h"

typedef struct s_file
{
	char	*path;
	int		mode;
}			t_file;

//my to mess with
typedef struct s_data
{
	char	*str;
	char	**args;
	t_file	*in_file;
	t_file	*out_file;
}			t_data;

//send to ft_ylouuuuuuuuuuuuuufi
typedef struct s_buffer
{
	char	*str;
	int		type;
	int		is_builtin;
	struct s_buffer *next;
}	t_buffer;

typedef struct s_delim
{
	int	num_squote;
	int	num_dquote;
	int	type;
}	t_delim;

t_buffer	*new_buffer(char *str, int type);
void		add_back(t_buffer **head, t_buffer *n_buffer);


//parsing utils
void	ft_skip_space(char *str, int *i);

void	ft_init_pipe(t_delim *delim);
void	ft_init_redection(t_delim *delimiter);
void	ft_init_quote(t_delim *delim);

//check for delemiter
int	ft_is_heredoc(char c, char c_plus, t_delim *delimiter);
int	ft_is_read(char c, t_delim *delimiter);
int	ft_is_append(char c, char c_plus, t_delim *delimiter);
int	ft_is_write(char c, t_delim *delimiter);
int	ft_ispipe(char c, t_delim *delim);


#	endif
