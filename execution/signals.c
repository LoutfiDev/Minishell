/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 08:47:55 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/21 16:52:59 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/exec.h"

void    sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
		g_exit_status = 1;
    }
}

// signal(SIGINT,sig_handler);
// signal(SIGINT,SIG_DFL);
// signal(SIGINT,SIG_IGN);
