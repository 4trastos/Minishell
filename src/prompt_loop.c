/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/05/20 11:10:06 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"
#include "../incl/executor.h"

bool	check_builtins(t_list *built, t_string *cmd_input, t_tools *tls)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;
	unsigned int	len;

	i = 0;
	j = 0;
	str = cmd_input->str;
	while (i < built->size)
	{
		get_builts(built->data[i], (i + 1));
		i++;
	}
	i = 0;
	while (i < built->size)
	{
		len = ft_strlen(built->data[i]->str);
		if (ft_strncmp(built->data[i]->str, str, len) == 0)
			j = terminator(built->data[i]->str, tls, str, built->data[i]->blt);
		i++;
	}
	if (j == BT_EXIT)
		return (false);
	else
		return (true);
}

void	check_commands(t_string *cmd_input)
{
	unsigned int	i;
	t_list			*tokens;

	tokens = create_tokens(cmd_input);
	i = 0;
	while (i < tokens->size)
	{
		get_op(tokens->data[i]);
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
