/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/05/15 13:49:47 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"
#include "../incl/executor.h"

void	check_commands(t_string *cmd_input)
{
	unsigned int	i;
	unsigned int	j;
	t_list			*tokens;

	i = 0;
	tokens = create_tokens(cmd_input);
	tokens = builtins(tokens);
	j = 0;
	while (j <= 7)
	{
		printf("builtins anidados en global: %s\n", tokens->builtins[j]);
		j++;
	}
	list_app_function(tokens, (t_function)ft_errormsg);
	while (i < tokens->size)
	{
		get_op(tokens->data[i]);
		printf("%d\n", tokens->data[i]->op);
		i++;
	}
	if (executor(tokens) > 0)
		write (1, "mal\n", 4);
	free(tokens->data);
	free(tokens);
}

bool	prompt_loop(t_string *cmd_input)
{
	char	*command;
	bool	next_command;

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
		free(cmd_input);
		return (next_command);
	}
	check_commands(cmd_input);
	string_delete(cmd_input);
	free(cmd_input);
	return (next_command);
}

bool	check_exit(t_string *cmd_input)
{
	if (ft_strncmp(cmd_input->str, "exit", 4) == 0
		&& ft_strlen(cmd_input->str) == 4)
		return (false);
	else
		return (true);
}

/* void	check_commands(t_string *cmd_input)
{
	t_list	*tokens;

	tokens = create_tokens(cmd_input);
	list_app_function(tokens, (t_function)ft_errormsg);
	list_expresion(tokens);
	if (executor(tokens) > 0)
		write (1, "mal\n", 4);
	free(tokens->data);
	free(tokens);
} */