/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/30 15:14:55 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_string	*parse_strings(char c, char *str, unsigned int *i)
{
	t_string		*new;
	char			*aux;
	unsigned int	start;

	start = *i + 1;
	(*i)++;
	while (str[*i] != '\0' && str[*i] != c)
		(*i)++;
	aux = ft_substr(str, start, *i - start);
	new = terminal_string(aux);
	free(aux);
	if (str[*i] == c && str[*i] != '\0')
		(*i)++;
	return (new);
}

t_string	*parse_operators(char c, char *str, unsigned int *i)
{
	t_string		*new;
	char			*aux;
	unsigned int	start;
	unsigned int	rest;

	start = *i;
	rest = 0;
	while (str[*i] == c)
		(*i)++;
	while (str[*i] == ' ')
	{
		rest++;
		(*i)++;
	}
	while (str[*i] != c && str[*i] != '\0' && str[*i] != '>' && str[*i] != '|'
		&& str[*i] != ' ')
		(*i)++;
	aux = ft_substrop(str, start, (*i - start) - rest);
	new = terminal_string(aux);
	free(aux);
	return (new);
}

t_string	*parse_pipes(char c, char *str, unsigned int *i)
{
	t_string		*new;
	char			*aux;
	unsigned int	start;

	start = *i;
	if (str[*i] == '$')
	{
		return (new = parse_dollar(c, str, i));
	}
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

t_string	*parse_tokens(t_tools *tools, t_list *built, char *str,
				unsigned int *i)
{
	t_string		*new;
	char			*aux;
	unsigned int	start;
	int				flag;

	start = *i;
	flag = 0;
	while (str[*i] != '"' && str[*i] != 92 && str[*i] != '|' && str[*i]
		&& str[*i] != '<' && str[*i] != '>' && str[*i] != ';' && str[*i] != 39
		&& str[*i] != 36)
		(*i)++;
	aux = ft_substr(str, start, *i - start);
	check_builtins(tools, built, aux, &flag);
	new = terminal_string(aux);
	free (aux);
	if (flag == 1)
		new->op = OP_BUILTIN;
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
