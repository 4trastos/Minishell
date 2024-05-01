/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicgonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/04/23 13:13:56 by nicgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"

void    prompt_loop(t_tools *tools)
{
    char    *input_read;

    while (1)
    {
    input_read = readline(PROMPT);
    if (!input_read)
        exit(0);
    tools->input_line = ft_strtrim(input_read, " \t\n\r");
    add_history(tools->input_line);
    if (check_exit(tools) != -1)
        break;
    }
}

int     check_exit(t_tools *tools)
{
    if(ft_strncmp(tools->input_line, "exit", 4) == 0 
        && ft_strlen(tools->input_line) == 4)
        return (0); 
    else 
        return (-1);
}