/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:16:21 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/11 22:06:06 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/buffer.h"

char	*join_path(char *cmd, t_list *_env)
{
	char	**array;
	char	*path;
	int		status;
	int		i;

	i = 0;
	if (!cmd)
		return (NULL);
	array = ft_split(get_path("PATH", _env), ':');
	while (array[i])
	{
		path = ft_strjoin(array[i++], ft_strdup("/"));
		path = ft_strjoin(path, ft_strdup(cmd));
		status = access(path, F_OK);
		if (status != -1)
		{
			ft_free_array(array, i);
			return (path);
		}
		free(path);
	}
	ft_free_array(array, i);
	return (NULL);
}

int	open_infile(char *filename, char *cmd)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1 && !access(filename, F_OK))
	{
		close(fd);
		exit(print_error(cmd, ": ", filename, ": permission denied\n", 1));
	}
	else if (fd == -1)
	{
		close(fd);
		exit(print_error(cmd, ": ", filename,
				": No such file or directory\n", 1));
	}
	return (fd);
}

int	open_outfile(char *filename, char *cmd, int mode)
{
	int	fd;

	fd = open(filename, O_CREAT, 0644);
	if (fd == -1)
	{
		perror(filename);
		exit(ERROR);
	}
	close(fd);
	if (!mode)
		fd = open(filename, O_WRONLY | O_TRUNC);
	else
		fd = open(filename, O_WRONLY | O_APPEND);
	if (fd == -1)
		exit(print_error(cmd, ": ", filename, ": permission denied\n", 1));
	return (fd);
}

char	**create_array(char *cmd, char *opt)
{
	char	**array;
	char	**opts;
	int		i;
	int		j;
	int		nbr;

	i = 0;
	j = 0;
	nbr = 0;
	opts = ft_split(opt, ' ');
	while (opts && opts[nbr])
		nbr++;
	if (cmd)
		nbr += 1;
	array = malloc((nbr + 1) * sizeof(char *));
	if (cmd)
	{
		array[i] = ft_strdup(cmd);
		i++;
	}
	while (i < nbr)
		array[i++] = ft_strdup(opts[j++]);
	ft_free_array(opts, 0);
	return (array);
}

void	_exec(t_exec *node, t_list *_env)
{
	char	**array;
	int		fd;

	if (node->outfile)
	{
		fd = open_outfile(node->outfile, node->cmd, node->out_mode);
		close(WRITE_END);
		dup(fd);
	}
	array = create_array(node->cmd, node->opt);
	if (array[0][0] != '/')
		node->cmd = join_path(array[0], _env);
	if (!node->cmd)
		exit(print_error("minishell", ": ", array[0],
				": command not found\n", 127));
	if (node->infile)
	{
		fd = open_infile(node->infile, array[0]);
		close(READ_END);
		dup(fd);
	}
	execve(node->cmd, array, NULL);
	exit (ERROR);
}

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		exit(print_error(NULL, NULL, NULL, "fork failed\n", ERROR));
	return (pid);
}

void	_pipe(t_pipe *node, int *p, t_list *_env)
{
	if (pipe(p) < 0)
		exit(print_error(NULL, NULL, NULL, "pipe failed\n", ERROR));
	if (ft_fork() == 0)
	{
		close(WRITE_END);
		dup(p[WRITE_END]);
		close(p[READ_END]);
		close(p[WRITE_END]);
		execution(node->left, _env);
	}
	if (ft_fork() == 0)
	{
		close(READ_END);
		dup(p[READ_END]);
		close(p[READ_END]);
		close(p[WRITE_END]);
		execution(node->right, _env);
		exit(0);
	}
	close(p[READ_END]);
	close(p[WRITE_END]);
	wait(0);
	wait(0);
}

int	*_init_pipe(void)
{
	int	*p;

	p = ft_calloc(sizeof(int *), 2);
	if (!p)
		return (NULL);
	return (p);
}

char	*ft_update(char *old, char *new)
{
	if (old)
		free(old);
	return (ft_strdup(new));
}

char	*ft_opt_update(char *opt, char *buff)
{
	char	*new_opt;

	if (!opt)
		new_opt = ft_strdup(buff);
	else
		new_opt = ft_argsjoin(opt, buff);
	return (new_opt);
}

void	update_node(t_exec **node, t_list *expanded_buff)
{
	t_buffer	*buff_node;
	
	while (expanded_buff)
	{
		buff_node = (t_buffer *)expanded_buff->content;
		if (buff_node->type == 7)
			break ;
		else if (buff_node->type == 1)
			(*node)->cmd = ft_update((*node)->cmd, buff_node->str);
		else if (buff_node->type == 2)
			(*node)->opt = ft_opt_update((*node)->opt, buff_node->str);
		else if (buff_node->type == 3)
			(*node)->infile = ft_update((*node)->infile, buff_node->str);
		else if (buff_node->type == 4)
			(*node)->outfile = ft_update((*node)->outfile, buff_node->str);
		else if (buff_node->type == 5)
			(*node)->out_mode = 1;
		expanded_buff = expanded_buff->next;
	}
}

void	expanded(t_exec *node, t_list *_env)
{
	// t_exec	*new_node;
	t_list	*expanded_buff;
	
	expanded_buff = NULL;
	if (has_dollar(node->cmd))
	{
		expanded_buff = expanding(node->cmd, _env, 1);
		update_node(&node, expanded_buff);
	}
	if (has_dollar(node->opt))
	{
		expanded_buff = expanding(node->opt, _env, 2);
		update_node(&node, expanded_buff);
	}
	if (has_dollar(node->infile))
	{
		expanded_buff = expanding(node->infile, _env, 3);
		update_node(&node, expanded_buff);
	}
	if (has_dollar(node->outfile))
	{
		expanded_buff = expanding(node->outfile, _env, 4);
		update_node(&node, expanded_buff);
	}
	// return ((t_mask *)new_node);
}

void	execution(t_mask *root, t_list *_env)
{
	int		*p;

	p = _init_pipe();
	if (root->mask == PIPE_NODE)
		_pipe((t_pipe *)root, p, _env);
	else if (root->mask == EXEC_NODE)
	{
		expanded((t_exec *)root, _env);
		_exec((t_exec *)root, _env);
	}
	free(p);
}
