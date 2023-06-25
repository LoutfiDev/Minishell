/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 09:01:39 by yloutfi           #+#    #+#             */
/*   Updated: 2023/06/24 11:24:05 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_buffer *buff_node(char *str, int type)
{
	t_buffer	*buff_node;

	buff_node = malloc(sizeof(t_buffer));
	buff_node->str = ft_strdup(str);
	buff_node->type = type;
	return (buff_node);
}
t_list	*create_buff(t_list *buffer, char *str, int type)
{
	if (!buffer)
		buffer = ft_lstnew(buff_node(str, type));
	else
		ft_lstadd_back(&buffer, ft_lstnew(buff_node(str, type)));
	return(buffer);
}
int main (int ac, char **av, char **env)
{
	// env = NULL;
	(void)ac;
	(void)av;
	// (void)env;
	// int fd = open("test.txt", O_WRONLY | O_TRUNC);
	t_list	*_env = NULL;
	t_list	*_buffer = NULL;
	_env = create_env(env);
	_buffer = create_buff(_buffer, "cat", 1);
	_buffer = create_buff(_buffer, "test.txt", 3);
	_buffer = create_buff(_buffer, "|", 7);
	_buffer = create_buff(_buffer, "grep", 1);
	_buffer = create_buff(_buffer, "include", 2);
	_buffer = create_buff(_buffer, "|", 7);
	_buffer = create_buff(_buffer, "wc", 1);
	_buffer = create_buff(_buffer, "-w", 2);
	// char *str[] = {"/bin/ls", NULL};
	// while (_buffer)
	// {
	// 	t_buffer *test = (t_buffer *)_buffer->content;
	// 	printf("%s	%d\n", test->str, test->type);
	// 	_buffer = _buffer->next;
	// }
	// while (_env)
	// {
	// 	t_env *test = (t_env *)_env->content;
	// 	printf("%s=%s\n", test->key, test->value);
	// 	_env = _env->next;
	// }
	// exec_echo(NULL, 1);
	// exec_env(_env, 1);
	// printf("*************************************************\n");
	// exec_cd(av+2, _env);
	// execve("/bin/ls",  str, env);
	// exec_pwd(1);
	// ac = 0;
	// exec_export(av+2, &_env, &ac);
	// printf("*************************************************\n");
	// exec_env(_env, 1);
	// exec_unset(av+2, &_env);
	// exec_exit(av+2, &ac);
	ft_lstfree(_env);
	// while (1)
	// ;
	return (0);
}