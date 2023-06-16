#	ifndef BUFFER_H
# define BUFFER_H

# include <readline/readline.h>
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
}	t_buffer;

typedef struct s_quote
{
	int	num_squote;
	int	num_dquote;
	int	type;
}	t_quote;

t_buffer	*new_buffer(char *str, int type);
void		insert_node(t_list **head, t_list *node, t_list *n_node);

//parsing utils
void	ft_skip_space(char *str, int *i);


//expanding utils
//int		get_dollar(char *str, int *index, int *quote);
t_list	*expand(t_buffer *node, char **env);

//check for delemiter
int	ft_is_heredoc(char c, char c_plus, int *type);
int	ft_is_read(char c, int *type);
int	ft_is_append(char c, char c_plus, int *type);
int	ft_is_write(char c, int *type);

//general utils function
int	*create_tab(int end, int type);
#	endif
