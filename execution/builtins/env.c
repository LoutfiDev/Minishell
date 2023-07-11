/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:11:38 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/11 08:27:34 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exec_env(t_list *env, int export)
{
	t_env	*node;

	if (export)
	{
		while (env)
		{
			node = (t_env *)env->content;
			if (node->value)
				printf("%s=%s\n", node->key, node->value);
			else
				printf("%s\n", node->key);
			env = env->next;
		}
	}
	else
	{
		while (env)
		{
			node = (t_env *)env->content;
			if (node->key && node->value)
				printf("%s=%s\n", node->key, node->value);
			env = env->next;
		}
	}
}
