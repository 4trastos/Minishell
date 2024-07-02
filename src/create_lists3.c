/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lists3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:33:23 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/28 14:09:26 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_upupdatetk(char *str, char **test, unsigned int *i)
{
	while (str[*i] != 92 && str[*i] != '|' && str[*i]
		&& str[*i] != '<' && str[*i] != '>' && str[*i] != ';'
		&& str[*i] != '\'' && str[*i] != '"')
	{
		(*i)++;
		(*test)++;
	}
}

char	*ft_updatemoretk(char *new, char *test, unsigned int *i, t_tools *tools)
{
	int	h;
	int	j;

	h = 0;
	while (test[h] != '\0' && test[h] != '|' && test[h] != '<' && test[h] != '>'
		&& test[h] != ' ' && test[h] != '"' && test[h] != '\'')
		h++;
	new = malloc(h + 1);
	if (!new)
		return (NULL);
	j = 0;
	while (h > 0)
	{
		new[j] = *test;
		j++;
		test++;
		(*i)++;
		h--;
	}
	new[j] = '\0';
	if (ft_strchr(new, '$') != NULL)
		new = updatedollar(new, tools);
	return (new);
}

void	prsopaux(char *str, unsigned int *i, unsigned int *rest)
{
	while (str[*i] == ' ')
	{
		(*rest)++;
		(*i)++;
	}
}

int	istru(char c, char actual)
{
	if (actual == c || actual == '\0' || actual == '>'
		|| actual == '|' || actual == ' ')
		return (1);
	else
		return (0);
}

void	addblt(t_string *new, int *flag)
{
	if (*flag != 0)
	{
		new->op = OP_BUILTIN;
		new->blt = *flag;
		*flag = 0;
	}
}
