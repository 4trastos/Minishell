/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/06/22 16:56:31 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	check_exit(t_string *cmd_input)
{
	char	*str;
	char	*aux;
	char	**mtx;
	int		start;
	int		i;

	str = cmd_input->str;
	mtx = ft_split(str, ' ');
	if (ft_mtx_len(mtx) > 2)
		return (ft_doublefree(mtx), 1);
	i = 0;
	start = 0;
	while (str[start] == ' ')
		start++;
	i = start;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	aux = ft_substr(str, start, i - start);
	if (ft_strcmp("exit", aux) == 0)
		ft_exit(cmd_input->str);
	ft_doublefree(mtx);
	free(aux);
	return (1);
}

void	check_builtins(t_tools *tools, t_list *built, char *input, int *flag)
{
	unsigned int	i;

	i = 0;
	(void)tools;
	while (i < built->size)
	{
		get_builts(built->data[i], (i + 1));
		i++;
	}
	i = 0;
	while (i < built->size && *flag == 0)
	{
		if (custom_strnstr(input, built->data[i]->str) == 0)
			*flag = built->data[i]->blt;
		i++;
	}
}

static void	check_commands(t_string *cmd_input, t_tools *tools)
{
	t_list			*tokens;
	t_list			*built;
	unsigned int	i;

	if (ft_strlen(cmd_input->str) > 1)
	{
		built = builtins();
		tokens = create_tokens(built, tools, cmd_input);
		i = 0;
		if (tokens != NULL)
		{
			while (i < tokens->size)
			{
				get_op(tokens->data[i]);
				i++;
			}
			ft_executator(tokens, tools);
			list_delete(tokens);
		}
		list_delete(built);
	}
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

void	ft_exit(char *str)
{
	int		code;
	char	**mtx;
	int		i;

	mtx = ft_split(str, ' ');
	if (ft_mtx_len(mtx) > 2)
	{
		ft_doublefree(mtx);
		write(2, "too many arguments\n", 20);
		return ;
	}
	if (ft_mtx_len(mtx) == 1)
	{
		ft_doublefree(mtx);
		exit(0);
	}
	i = -1;
	while (mtx[1][++i] != '\0')
		if (ft_exit_toaux(mtx[1][i]) == 1)
			return (ft_doublefree(mtx));
	code = ft_atoi(mtx[1]);
	code = ft_get_code(code);
	ft_doublefree(mtx);
	free(str);
	exit(code);
}
