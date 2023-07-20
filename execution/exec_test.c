/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 09:01:39 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/20 08:43:01 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/buffer.h"

void	printTree(t_mask *node, int space)
{
	t_pipe	*pipe_node;
	t_exec	*exec_node;

	if (!node)
		return ;
	if (node->mask == PIPE_NODE)
	{
		pipe_node = (t_pipe *)node;
		space += 10;
		printTree(pipe_node->left, space);
		printf("\n");
		for (int i = 10; i < space; i++)
			printf(" ");
		printf("%s", "P");
		printTree(pipe_node->right, space);
	}
	else if (node->mask == EXEC_NODE)
	{
		exec_node = (t_exec *)node;
		space += 10;
		printf("\n");
		for (int i = 10; i < space; i++)
			printf(" ");
		printf("%s", exec_node->cmd);
	}
}

t_buffer	*buff_node(char *str, int type)
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
	return (buffer);
}

int run(int ac, char **av, char **env)
{
	// env = NULL;
	(void)ac;
	// (void)av;
	// (void)env;
	// int fd = open("test.txt", O_WRONLY | O_TRUNC);
	t_list	*_env = NULL;
	// t_list	*_buffer = NULL;
	// t_mask	*_tree = NULL;
	_env = create_env(env);
	// _buffer = create_buff(_buffer, "cd", 1);
	// _buffer = create_buff(_buffer, "~", 2);
	// _buffer = create_buff(_buffer, "|", 7);
	// _buffer = create_buff(_buffer, "grep", 1);
	// _buffer = create_buff(_buffer, "s", 2);
	// _buffer = create_buff(_buffer, "|", 7);
	// _buffer = create_buff(_buffer, "wc", 1);
	// _buffer = create_buff(_buffer, "-c", 2);
	// _buffer = create_buff(_buffer, "outfile", 4);
	// _buffer = create_buff(_buffer, "append", 5);
	// _tree = build_tree(_buffer, _env);
	// execution(_tree, _env, env);
	// printTree(_tree, 0);
	// printf("\n");
	// char *str[] = {"/bin/cat", NULL};
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
	exec_cd(av+2, _env, 1);
	// execve("/bin/cat",  str, NULL);
	// exec_pwd(1);
	// ac = 0;
	// exec_export(av+2, &_env, &ac);
	// exec_env(_env, 1);
	// exec_unset(av+2, &_env);
	// printf("*************************************************\n");
	// exec_exit(av+2, &ac);
	// ft_lstfree(_env);
	// free_tree(_tree);
	ft_lstclear(&_env, clear_env);
	// ft_lstclear(&_buffer, clear_buffer);
	return (0);
}
// int main (int ac, char **av, char **env)
// {
// 	int a = run(ac, av, env);
// 	while (1)
// 	;
// 	return (a);
// }
