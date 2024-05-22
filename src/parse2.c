/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:33:23 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/22 12:41:56 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"
#include "../incl/executor.h"

static void	ft_strcopydav(char *new, char *name, char c, char *value)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (name[i] != '\0')
	{
		new[i] = name[i];
		i++;
	}
	new[i] = c;
	i++;
	while (value[j] != '\0')
	{
		new[i] = value[j];
		i++;
		j++;
	}
	new[i] = '\0';
}

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

void	ft_addname(char **env, char *name, int index)
{
	int		i;
	char	**text;

	text = ft_split(name, ' ');
	i = 0;
	while (text[i] != NULL)
		i++;
	if (i > 1)
		return ;
	if (ft_isgoodenv(text[0]) != 0)
		return ;
	i = 0;
	if (index == -1)
	{
		while (env[i] != NULL)
			i++;
		env[i] = ft_createname(name, '=');
		env[i + 1] = NULL;
	}
	return ;
}

void	ft_addvalue(char **env, char *name, int index, char *value)
{
	size_t	len_name;
	size_t	len_value;
	int		i;
	char	*new;

	len_name = ft_strlen(name);
	len_value = ft_strlen(value);
	if (ft_isgoodenv(name) != 0)
		return ;
	new = malloc(len_value + len_name + 2);
	if (!new)
		return ;
	ft_strcopydav(new, name, '=', value);
	if (index != -1)
		env[index] = new;
	else
	{
		i = 0;
		while (env[i] != NULL)
			i++;
		env[i] = new;
		env[i + 1] = NULL;
	}
}
