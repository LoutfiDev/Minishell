/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:35:50 by yloutfi           #+#    #+#             */
/*   Updated: 2023/07/21 17:58:42 by yloutfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/buffer.h"
#include "../includes/expand.h"

char	*sub_var(char *str, int *i)
{
	int		start;
	int		dolar;
	char	*res;

	dolar = 0;
	while (str[*i])
	{
		if (str[*i] == '$' && dolar == 0)
		{
			dolar++;
			start = *i;
		}
		else if (dolar == 1 && !ft_isalnum(str[*i]) && str[*i] != '?')
			break ;
		*i += 1;
	}
	res = ft_substr(str, start, (*i) - start);
	return (res);
}

char	*get_value(char *str)
{
	if (!ft_strncmp(str, "$?", ft_strlen(str) + 2))
    {
	    free(str); 
		return (ft_itoa(g_exit_status));
    }
	free(str);
	return (ft_strdup("\0"));
}

char    *get_expanded(char  *str)
{
    int		i;
    char	*tmp;
    t_list	*lst;
    char	*res;
    t_list	*head;

    i = 0;
    lst = NULL;
    while (str[i])
    {
        tmp = sub_var(str, &i);
        tmp = get_value(tmp);
        head = ft_lstnew(new_buffer(tmp, 0));
        free(tmp);
        ft_lstadd_back(&lst, head);
    }
    res = join_all(str, lst, 0);
    return (res);
}

void	expand_array(t_exec	**node)
{
	int	i;
	
	i = 0;
	if (has_dollar((*node)->cmd))
		(*node)->cmd = get_expanded((*node)->cmd);
	while ((*node)->opt && (*node)->opt[i])
	{
		if (has_dollar((*node)->opt[i]))
			(*node)->opt[i] = get_expanded((*node)->opt[i]);
		i++;
	}
}