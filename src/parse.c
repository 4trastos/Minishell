/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/30 14:13:58 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_string	*parse_strings(char c, char *str, unsigned int *i, t_tools *tools)
{
	t_string		*new;
	char			*aux;
	char			*test;
	unsigned int	result;

	if (ft_validator(str) == 1)
		return (NULL);
	test = str;
	result = *i;
	while (result > 0)
	{
		test++;
		result--;
	}
	ft_finaltoken(test, &result);
	aux = ft_searchqu(test, c, i, tools);
	while (result > 0)
	{
		aux = prsstraux(aux, str, i, tools);
		result--;
	}
	new = terminal_string(aux);
	free(aux);
	return (new);
}

t_string	*parse_operators(char c, char *str, unsigned int *i, t_tools *tools)
{
	t_string		*new;
	char			*aux;
	unsigned int	start;
	unsigned int	rest;

	start = *i;
	rest = 0;
	if (get_n_red(str, start, c) == 0)
		return (NULL);
	if (str[*i] + 1 != '\0')
	{
		piticli_boniko(str, i, c, &rest);
		aux = ft_substrop(str, start, (*i - start) - rest);
		aux = updatedollar(aux, tools);
	}
	else
	{
		aux = ft_substr(str, start, *i);
		(*i)++;
	}
	new = terminal_string(aux);
	free(aux);
	return (new);
}

t_string	*parse_pipes(char c, char *str, unsigned int *i, t_tools *tools)
{
	t_string		*new;
	char			*aux;
	unsigned int	start;

	start = *i;
	if (str[*i] == '$')
		return (new = parse_dollar(c, str, i, tools));
	else
	{
		while (str[*i] == c)
			(*i)++;
		aux = ft_substr(str, start, *i - start);
		new = terminal_string(aux);
		free(aux);
	}
	return (new);
}

t_string	*parsetks(t_tools *tools, t_list *built, char *str, unsigned int *i)
{
	t_string		*new;
	unsigned int	start;
	int				flag;
	int				result;
	int				quotes;

	start = *i;
	flag = 0;
	quotes = 0;
	result = ft_validator_extra(str, &quotes, &flag);
	if (result == 1)
		return (NULL);
	else if (result == 0)
	{
		ft_updateprtkn(str, i);
		ft_prstksaux(tools, str, start, i);
	}
	else if (result == 2)
		tools->prompt = ft_updatetokens(str, i, tools);
	check_builtins(tools, built, tools->prompt, &flag);
	new = terminal_string(tools->prompt);
	addblt(new, flag);
	return (new);
}

void	list_expresion(t_list *tokens)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (next_string(tokens, &i))
	{
		if (!is_operators(tokens->data[j]))
			get_op(tokens->data[j]);
		j++;
	}
}
