#	ifndef BUFFER_H
# define BUFFER_H

# include <readline/readline.h>
# include "libft/libft.h"
# include <unistd.h>
# include "parsing.h"

# define CMD 1
# define arg 2
# define IN 3
# define OUT_WRITE 4
# define OUT_APP 5
# define HERE_DOC 6
# define PIPE 7

// # include "readline/readline.h"

//send to ft_ylouuuuuuuuuuuuuufi
typedef struct s_buffer
{
	char	*str;
	int		type;
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

int	*read_here_doc(char *lim, int *h_pipe, int expand, t_list *env);
int is_herdoc_expandable(char *hd_lim);
#	endif
