/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:33:23 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/15 09:42:54 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"
#include "../incl/executor.h"

t_string	*parse_dollar(char c, char *str, unsigned int *i)
{
	t_string		*new;
	char			*aux;
	unsigned int	start;
	unsigned int	flag;

	start = *i;
	flag = 0;
	while (str[*i] == c)
		(*i)++;
	while (str[*i] != '"' && str[*i] != 92 && str[*i] != '|' && str[*i]
		&& str[*i] != '<' && str[*i] != '>' && str[*i] != ';' && str[*i] != 39
		&& str[*i] && str[*i] != ' ' && flag == 0)
	{
		if (str[*i] == '?')
			flag = 1;
		(*i)++;
	}
	aux = ft_substr(str, start, *i - start);
	new = terminal_string(aux);
	free(aux);
	return (new);
}
