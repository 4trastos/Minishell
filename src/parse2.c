/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:33:23 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/28 14:59:00 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

t_string	*parse_dollar(char c, char *str, unsigned int *i, t_tools *tools)
{
	t_string		*new;
	char			*aux;
	unsigned int	start;
	unsigned int	flag;

	start = *i;
	flag = 0;
	if (str[*i] + 1 != '\0')
	{
		ft_updatepdll(str, c, i, &flag);
		aux = ft_substr(str, start, *i - start);
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

void	ft_addname(t_tools *tools, char *name)
{
	char	*new;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (tools->env[size] != NULL)
		size++;
	new = ft_calloc(sizeof (char *), ft_strlen(name) + 1);
	if (!new)
		return ;
	while (name[i] != '\0')
	{
		new[i] = name[i];
		i++;
	}
	tools->env = ft_realloc(tools->env, sizeof(char *) * (size + 2));
	if (!tools->env)
	{
		free (new);
		return ;
	}
	tools->env[size] = ft_strdup(new);
	free(new);
	tools->env[size + 1] = NULL;
}

void	ft_updatevalue(char **env, char *name, int index)
{
	char	*new;
	size_t	len_name;
	size_t	i;

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

int	ft_export_name(char *str)
{
	int	i;

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
		return (1);
	while (str[++i] != '\0' && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (1);
	}
	return (0);
}

void	ft_myenv(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strchr(env[i], '=') != NULL)
		{
			ft_putstr(env[i]);
			write(1, "\n", 1);
			i++;
		}
		else
			i++;
	}
}
