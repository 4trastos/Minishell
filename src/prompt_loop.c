/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/06/04 18:02:45 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	check_exit(t_string *cmd_input)
{
	char	*str;
	char	*aux;
	int		start;
	int		i;

	str = cmd_input->str;
	i = 0;
	start = 0;
	while (str[start] == ' ')
		start++;
	i = start;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	aux = ft_substr(str, start, i - start);
	if (ft_strcmp("exit", aux) == 0)
	{
		free(aux);
		return (0);
	}
	free(aux);
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
			terminator(tools, input, built->data[i]->str,
				built->data[i]->blt);
			*flag = 1;
		}
		i++;
	}
}

static void	check_commands(t_string *cmd_input, t_tools *tools)
{
	t_list			*tokens;
	t_list			*built;
	unsigned int	i;

	built = builtins();
	tokens = create_tokens(built, tools, cmd_input);
	// list_app_function(tokens, (t_function)ft_errormsg);
	i = 0;
	while (i < tokens->size)
	{
		get_op(tokens->data[i]);
		i++;
	}
	if (executor(tokens, tools) > 0)
		write (1, "mal\n", 4);
	list_delete(tokens);
	list_delete(built);
}

bool	prompt_loop(t_string *cmd_input, t_tools *tools)
{
	char	*command;
	bool	next_command;

	init_sig();
	next_command = !cmd_input;
	if (!cmd_input)
	{
		command = readline(PROMPT);
		if (!command)
			return (false);
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
	check_commands(cmd_input, tools);
	string_delete(cmd_input);
	free(cmd_input);
	return (next_command);
}
