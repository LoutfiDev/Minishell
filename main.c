/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:40:55 by anaji             #+#    #+#             */
/*   Updated: 2023/07/11 09:29:34 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <sys/_types/_null.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include "includes/buffer.h"
#include "includes/parsing.h"
#include "includes/exec.h"
#include <errno.h>

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

int	main_c(int ac, char *av[], char **env)
{
	char	*trim; 	
	char	*buff;
	t_list *head, *tmp;
	int delim;
	t_buffer *bf;;
	t_quote *n_quote;
	t_list	*_env;
	int		*here_doc;
	t_mask	*_tree = NULL;
	char *h;
	int pid;

	_env = create_env(env);
	n_quote = malloc(sizeof(t_quote));
	// while (1)
	// {
		head = NULL;
		n_quote->num_squote = 0;
		n_quote->num_dquote = 0;
		buff  = readline("token here : ");
		trim  = ft_strtrim(buff, " \t");
		parsing(trim, delim, n_quote, &head);
		free(trim);
		if (head)
			add_history(buff); 
		free(buff);
		expanding(&head, _env);
		handle_quote(head);
		tmp = head;
		while (tmp)
		{
			bf = (t_buffer *)tmp -> content;
			if (bf ->type == 6)
			{
			//	printf("buff = %s\n", bf->str);
				here_doc = read_here_doc(bf->str, is_herdoc_expandable(bf->str), _env);
				close(here_doc[1]);
				//write_out(here_doc[0], env, av+1);
				free(bf->str);
				bf->str = ft_itoa(here_doc[0]);
				//close(here_doc[0]);
				//close(here_doc[1]);
				free(here_doc);
			}
			tmp = tmp-> next;
		}
		tmp = head;
		_tree = build_tree(head);
		printTree(_tree, 0);
		printf("\n");
		execution(_tree, _env);
		// while (tmp)
		// {
		// 	bf = (t_buffer *) tmp -> content;
		// 	printf("str = %s\t type = %d\n",bf->str, bf->type);
		// 	tmp = tmp ->next;
		// }
		//printf("sQ = %d dQ = %d\n", n_quote->num_squote, n_quote->num_dquote);
		free_tree(_tree);
		free(n_quote);
		ft_lstclear(&_env, clear_env);
		ft_lstclear(&head, clear_buffer);
	// }
	return (0);
}
	int main (int ac, char **av, char **env)
	{
		int a = main_c(ac, av, env);
		while (1)
		;
		return (a);
	}
