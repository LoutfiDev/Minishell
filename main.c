/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:40:55 by anaji             #+#    #+#             */
/*   Updated: 2023/07/11 10:50:22 by yloutfi          ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	t_mask	*_tree = NULL;
	
	_tree = build_tree(buffer);
	execution(_tree, _env);
		
	free_tree(_tree);
	return (0);
}
