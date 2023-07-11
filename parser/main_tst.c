/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:40:55 by anaji             #+#    #+#             */
/*   Updated: 2023/07/11 16:23:03 by yloutfi          ###   ########.fr       */
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
#include "../includes/buffer.h"
#include "../includes/parsing.h"
#include "../includes/exec.h"
#include <errno.h>

// int	main(int ac, char **av, char **env)
// {
// 	t_list	*head;
// 	t_list	*_env;

// 	_env = create_env(env);
// 	while (1)
// 	{
// 		head = main_parse(_env);
// 		ft_lstclear(&head, clear_buffer);
// 	}
// 	return (0);
// }
