/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:33:23 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/29 13:29:24 by davgalle         ###   ########.fr       */
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

void	ft_addname(char **env, char *name)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(ft_strlen(name) * 1);
	if (!new)
		return ;
	while (name[i] != '\0')
	{
		new[i] = name[i];
		i++;
	}
	new[i] = '\0';
	i = 0;
	while (env[i] != NULL)
		i++;
	env[i] = new;
	env[i + 1] = NULL;
	return ;
}

void	ft_updatevalue(char **env, char *name, int index)
{
	char	*new;
	size_t	len_name;
	size_t	i;

	write(1, "Existe la variable\n", 19);
	len_name = ft_strlen(name);
	new = malloc(len_name + 1);
	if (!new)
		return ;
	i = 0;
	while (name[i] != '\0')
	{
		new[i] = name[i];
		i++;
	}
	new[i] = '\0';
	env[index] = new;
}

