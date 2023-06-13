#	ifndef BUFFER_H
# define BUFFER_H

#include <readline/readline.h>
# include "libft/libft.h"
# include <unistd.h>

# define CMD 1
# define arg 1
# define IN 3
# define OUT_WRITE 4
# define OUT_APP 5
# define HERE_DOC 6
# define PIPE 7

#define ONE_ARG 1
#define MANY_ARG 2
#define NO_ARG 3

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
}	t_buffer;

typedef struct s_quote
{
	int	num_squote;
	int	num_dquote;
	int	type;
}	t_quote;

t_buffer	*new_buffer(char *str, int type);
void		insert_buffer(t_list **head, t_list *node, t_list *n_node);

//parsing utils
void	ft_skip_space(char *str, int *i);


//expanding utils
int		get_dollar(char *str, int *index, int *quote);
t_list	*expand(t_list **head, t_list *node, char **env);

//check for delemiter
int	ft_is_heredoc(char c, char c_plus, int *type);
int	ft_is_read(char c, int *type);
int	ft_is_append(char c, char c_plus, int *type);
int	ft_is_write(char c, int *type);

//general utils function
int	*create_tab(int end, int type);
#	endif
