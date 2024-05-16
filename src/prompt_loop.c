/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/05/16 14:20:07 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"
#include "../incl/executor.h"

void	check_commands(t_string *cmd_input)
{
	unsigned int	i;
	t_list			*tokens;

	tokens = create_tokens(cmd_input);
	/* list_app_function(tokens, (t_function)ft_errormsg); */
	i = 0;
	while (i < tokens->size)
	{
		get_op(tokens->data[i]);
/* 		printf("%d\n", tokens->data[i]->op); */
		i++;
	}
	if (executor(tokens) > 0)
		write (1, "mal\n", 4);
	free(tokens->data);
	free(tokens);
}

bool	prompt_loop(t_string *cmd_input, t_tools *tools)
{
	t_list	*built;
	char	*command;
	bool	next_command;

	next_command = !cmd_input;
	built = builtins();
	if (!cmd_input)
	{
		command = readline(PROMPT);
		cmd_input = terminal_string(command);
		free(command);
	}
	add_history(cmd_input->str);
	next_command = check_builtins(built, cmd_input, tools);
	if (!next_command)
	{
		string_delete(cmd_input);
		free(cmd_input);
		return (next_command);
	}
	check_commands(cmd_input);
	string_delete(cmd_input);
	free(cmd_input);
	return (next_command);
}

bool	check_builtins(t_list *built, t_string *cmd_input, t_tools *tools)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	str = cmd_input->str;
	while (i < built->size)
	{
		if (ft_strncmp(built->data[i]->str, str, ft_strlen(str)) == 0)
			j = terminator(built->data[i]->str, tools);
		i++;
	}
	if (j == EXIT)
		return (false);
	else if (j != EXIT)
		return (true);
	else
		return (true);
}

/* 	next_command = check_exit(cmd_input); */

/* bool	check_exit(t_string *cmd_input)
{
	if (ft_strncmp(cmd_input->str, "exit", 4) == 0
		&& ft_strlen(cmd_input->str) == 4)
		return (false);
	else
		return (true);
} */