/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:31:52 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/22 15:04:57 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/buffer.h"

char	*get_path(char *str, t_list *env)
{
	t_env	*env_node;
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		env_node = (t_env *)tmp->content;
		if (!ft_strncmp(env_node->key, str, 0))
			return (env_node->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	print_error(char *cmd, char *delim, char *arg, char *msg, int exit_status)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(delim, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(msg, 2);
	ft_exit(exit_status);
}

int	nbr_options(t_list *_buffer)
{
	t_buffer	*buff_node;
	int			nbr;

	nbr = 0;
	while (_buffer)
	{
		buff_node = (t_buffer *)_buffer->content;
		if (buff_node->type == 7)
			break ;
		else if (buff_node->type == 2)
			nbr++;
		_buffer = _buffer->next;
	}
	return (nbr);
}

char	**fill_options(t_list *_buffer)
{
	char		**options;
	t_buffer	*buff_node;
	int			i;

	options = malloc((nbr_options(_buffer) + 2) * sizeof(char *));
	i = 0;
	while (_buffer)
	{
		buff_node = (t_buffer *)_buffer->content;
		if (buff_node->type == 7)
			break ;
		else if (buff_node->type == 1)
			options[i++] = ft_strdup(buff_node->str);
		else if (buff_node->type == 2)
			options[i++] = ft_strdup(buff_node->str);
		_buffer = _buffer->next;
	}
	options[i] = NULL;
	return (options);
}
