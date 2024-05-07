/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/05/07 20:38:56 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"

void	check_commands(t_string *cmd_input)
{
    t_list      *tokens;
    t_list      *aux;
    t_iterlist  iter;

    tokens = create_tokens(cmd_input);
    iter = create_iteri(tokens);
    (void)iter;
    list_app_function(tokens, (t_function)ft_errormsg);
    aux = list_expresion(&iter);
    if (aux)
    {
        write(1, "Se puede recorrer iterlist\n", 27);
        write(1, "Parsing OK\n", 11);
    }
    else
        error_msg("Parsing error");
    list_delete(tokens);
}

bool    prompt_loop(t_string *cmd_input)
{
    char    *command;
    bool  next_command;

    next_command = !cmd_input;
    if (!cmd_input)
    {
        command = readline(PROMPT);
        cmd_input = terminal_string(command);
        free(command);
    }
    add_history(cmd_input->str);
    next_command = check_exit(cmd_input);
    if (!next_command)
    {
        string_delete(cmd_input);
        return (next_command);
    }
    check_commands(cmd_input);
    string_delete(cmd_input);
    return (next_command);
}

bool     check_exit(t_string *cmd_input)
{
    if(ft_strncmp(cmd_input->str, "exit", 4) == 0 
        && ft_strlen(cmd_input->str) == 4)
        return (false); 
    else 
        return (true);
}
