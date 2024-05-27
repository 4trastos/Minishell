/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/05/27 18:21:30 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"
#include "../incl/executor.h"

int	check_exit(t_string *cmd_input)
{
	char			*str;

	str = cmd_input->str;
	while (*str == ' ')
		str++;
	if (ft_strcmp("exit", str) == 0)
		return (0);
	return (1);
}

void	check_builtins(t_tools *tools, t_list *built, char *input, int *flag)
{
	unsigned int	i;
	int				len;

	i = 0;
	while (i < built->size)
	{
		get_builts(built->data[i], (i + 1));
		i++;
	}
	i = 0;
	while (i < built->size && *flag == 0)
	{
		len = ft_strlen(built->data[i]->str);
		if (custom_strncmp(input, built->data[i]->str, len,
				built->data[i]->blt) == 0)
		{
			write(1, "SI Es un built\n", 15);
			terminator(tools, input, built->data[i]->str,
				built->data[i]->blt);
			*flag = 1;
		}
		i++;
	}
}

static void	check_commands(t_list *built, t_string *cmd_input, t_tools *tools)
{
	t_list			*tokens;
	unsigned int	i;

	tokens = create_tokens(built, tools, cmd_input);
	list_app_function(tokens, (t_function)ft_errormsg);
	i = 0;
	while (i < tokens->size)
	{
		printf("Operador antes de get_op: %d\n", tokens->data[i]->op);
		get_op(tokens->data[i]);
		printf("Operador: %d\n", tokens->data[i]->op);
		i++;
	}
	if (executor(tokens, tools) > 0)
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
	next_command = check_exit(cmd_input);
	if (!next_command)
	{
		string_delete(cmd_input);
		free(cmd_input);
		return (next_command);
	}
	check_commands(built, cmd_input, tools);
	string_delete(cmd_input);
	free(cmd_input);
	return (next_command);
}
