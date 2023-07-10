#	ifndef BUFFER_H
# define BUFFER_H

<<<<<<< HEAD
#include <readline/readline.h>
# include "libft/libft.h"
# include <unistd.h>
=======
# include <readline/readline.h>
# include "libft/libft.h"
# include <unistd.h>
# include "parsing.h"
>>>>>>> AI

# define CMD 1
# define arg 2
# define IN 3
# define OUT_WRITE 4
# define OUT_APP 5
# define HERE_DOC 6
# define PIPE 7

// # include "readline/readline.h"

<<<<<<< HEAD
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

=======
>>>>>>> AI
//send to ft_ylouuuuuuuuuuuuuufi
typedef struct s_buffer
{
	char	*str;
	int		type;
<<<<<<< HEAD
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

void	ft_init_pipe(t_delim *delim);
void	ft_init_redection(t_delim *delimiter);
void	ft_init_quote(t_delim *delim);

//check for delemiter
int	ft_is_heredoc(char c, char c_plus, t_delim *delimiter);
int	ft_is_read(char c, t_delim *delimiter);
int	ft_is_append(char c, char c_plus, t_delim *delimiter);
int	ft_is_write(char c, t_delim *delimiter);
int	ft_ispipe(char c, t_delim *delim);


=======
}	t_buffer;


typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

t_buffer	*new_buffer(char *str, int type);
void		insert_node(t_list **head, t_list *node, t_list *n_node);

//parsing utils
void	ft_skip_space(char *str, int *i);


//expanding utils
//int		get_dollar(char *str, int *index, int *quote);
t_list	*expand(t_buffer *node, t_list *env);
int	has_dollar(char *str);

//check for delemiter
int	ft_is_heredoc(char c, char c_plus, int *type);
int	ft_is_read(char c, int *type);
int	ft_is_append(char c, char c_plus, int *type);
int	ft_is_write(char c, int *type);

//general utils function
char	**split(char const *s, char c);
void	clear_buffer(void *bf);
void	fix_types(t_list *lst);

t_list	*create_env(char **env);

void sh(t_list *lst);

void	ft_strappend(char **s1, char *s2);

//remove quotes
void	handle_quote(t_list *lst);
void	remove_quote(char **str);

//HERE_DOC

int	*read_here_doc(char *lim, int expand, t_list *env);
int is_herdoc_expandable(char *hd_lim);
>>>>>>> AI
#	endif
