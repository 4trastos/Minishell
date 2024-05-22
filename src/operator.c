/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:58:01 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/16 13:41:14 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"
#include "../incl/executor.h"

void	ft_dollarpipe(t_string *token)
{
	if (token->str[0] == '|')
	{
		if (ft_opcmp(token->str, '|') == 0)
			token->op = OP_PIPE;
		else
			token->op = OP_NONE;
	}
	if (token->str[0] == '$')
	{
		if (ft_opdollar(token->str, '$') == 0)
			token->op = OP_DOLLAR_SIGN;
		else
			token->op = OP_NONE;
	}
	return ;
}

bool	ft_opdollar(char *str, char c)
{
	int	i;
	int	dollar;
	int	len;
	int	j;

	i = 0;
	dollar = 0;
	j = 0;
	if (!str)
		return (1);
	len = ft_strlen(str);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			dollar++;
		if (str[i] == ' ')
			j++;
		i++;
	}
	if (len == 1 || (dollar != 1 && j == 1) || (dollar == len))
		return (true);
	else
		return (false);
}

int	ft_opcmp(char *str, char c)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	if (!str)
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			pipe++;
		i++;
	}
	if (pipe != 1)
		return (true);
	else
		return (false);
}

void	get_op(t_string *token)
{
	if (token->str[0] == '|' || token->str[0] == '$')
		ft_dollarpipe(token);
	else if (ft_strncmp(token->str, "<<", 2) == 0)
		token->op = OP_HERE_DOC;
	else if (ft_strncmp(token->str, ">>", 2) == 0)
		token->op = OP_OUTPUT_REDIRECT_APPEND;
	else if (ft_strncmp(token->str, "<", 1) == 0)
		token->op = OP_INPUT_REDIRECT;
	else if (ft_strncmp(token->str, ">", 1) == 0)
		token->op = OP_OUTPUT_REDIRECT;
	else
		token->op = OP_NONE;
}

bool	is_operators(t_string *token)
{
	if (ft_strncmp(token->str, "|", 1) == 0)
		return (false);
	else if (ft_strncmp(token->str, "<", 1) == 0)
		return (false);
	else if (ft_strncmp(token->str, ">", 1) == 0)
		return (false);
	else if (ft_strncmp(token->str, "<<", 2) == 0)
		return (false);
	else if (ft_strncmp(token->str, ">>", 2) == 0)
		return (false);
	else
		return (true);
}
