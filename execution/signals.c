/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 08:47:55 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/18 12:37:21 by anaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/exec.h"

void    sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

// signal(SIGINT,sig_handler);
// signal(SIGINT,SIG_DFL);
// signal(SIGINT,SIG_IGN);
