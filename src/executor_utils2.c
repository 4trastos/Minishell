/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:28:39 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/30 13:32:41 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_split_part(t_list *tokens, unsigned int *j)
{
	if (tokens->data[*j - 1]->op == OP_OUTPUT_REDIRECT
		|| tokens->data[*j - 1]->op == OP_OUTPUT_REDIRECT_APPEND)
	{
		(*j)++;
		return (1);
	}
	else if (tokens->data[*j + 1]->op == OP_INPUT_REDIRECT
		|| tokens->data[*j + 1]->op == OP_HERE_DOC)
	{
		(*j)++;
		return (1);
	}
	return (0);
}

void	ft_execut_part(t_list **arr_tokens, t_tools*tools, unsigned int *i)
{
	if (arr_tokens[*i + 1] == NULL)
	{
		if (executor(arr_tokens[*i], tools) == 1)
			write(1, "ERROR\n", 6);
	}
	else if ((arr_tokens[*i + 1]->data[0]->op == 1
			|| arr_tokens[*i + 1]->data[0]->op == 4)
		&& ft_find_out(arr_tokens[*i]) == 0)
	{
		tools->flag = 1;
		if (executor(arr_tokens[*i], tools) == 1)
			write(1, "ERROR\n", 6);
	}
	else
	{
		if (executor(arr_tokens[*i], tools) == 1)
			write(1, "ERROR\n", 6);
	}
}

void	ft_get_commpart(t_list *tokens, t_executor *exe, int *flag, int *i)
{
	while (tokens->data[*i] != NULL)
	{
		if (tokens->data[*i]->op == OP_NONE
			|| tokens->data[*i]->op == OP_BUILTIN
			|| tokens->data[*i]->op == OP_DOLLAR_SIGN)
		{
			if (*flag == exe->i)
				break ;
			(*flag)++;
		}
		(*i)++;
	}
}

t_string	*ft_prcplt(t_list *blt, t_tools *tools, char *str, unsigned int *i)
{
	t_string	*command;

	command = NULL;
	while (str[*i] == ' ' || str[*i] == 92 || str[*i] == ';')
		(*i)++;
	if (str[*i] == '|' || str[*i] == '$')
		command = parse_pipes(str[*i], str, i, tools);
	else if (str[*i] == '<' || str[*i] == '>')
	{
		command = parse_operators(str[*i], str, i, tools);
		if (!command)
			return (NULL);
	}
	else if (str[*i] == '"' || str[*i] == '\'')
	{
		command = parse_strings(str[*i], str, i, tools);
		if (!command)
			return (NULL);
	}
	else
	{
		command = parsetks(tools, blt, str, i);
		free(tools->prompt);
	}
	return (command);
}

int	ft_exportchek(char *prompt, t_tools *tools)
{
	if (*prompt == '\0')
	{
		ft_customenvp(tools);
		ft_printenvp(tools);
		ft_doublefree(tools->exp);
		return (0);
	}
	ft_doublefree(tools->exp);
	return (1);
}
