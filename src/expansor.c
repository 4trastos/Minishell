/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:59:17 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/25 19:13:12 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void	ft_add_env(char *str, int *subtract, int *add, char *var)
{
	while (*str != '\0' && *str != ' ' && *str != '$')
	{
		*subtract += 1;
		str++;
	}
	*add += ft_strlen(ft_strchr(var, '=') + 1);
}

void	ft_iterone(char *str, t_tools *tools, int *add, int *subtract)
{
	int	index;

	index = 0;
	while (*str != '\0')
	{
		if (*str == '$')
		{
			str++;
			if (*str == '?')
			{
				*subtract += 2;
				*add += ft_strlen(ft_itoa(tools->exit_code));
				str++;
			}
			else
			{
				index = ft_findenv(tools->env, str);
				if (index != -1)
					ft_add_env(str, subtract, add, tools->env[index]);
			}
		}
		if (*str != '\0')
			str++;
	}
}

static char	*ft_iterthree(char **env, int *index, char *update, int *i)
{
	int	j;

	j = 0;
	while (env[*index][j] != '=')
		j++;
	while (env[*index][++j] != '\0')
	{
		update[*i] = env[*index][j];
		*i += 1;
	}
	return (update);
}

static char	*ft_iteraux(char *str, t_tools *tools, int *i, char *update)
{
	int		index;
	char	*exit_code;

	index = 0;
	if (*str == '?')
	{
		exit_code = ft_itoa(tools->exit_code);
		while (*exit_code != '\0')
		{
			update[*i] = *exit_code;
			(*i)++;
			exit_code++;
		}
		str++;
	}
	else
	{
		index = ft_findenv(tools->env, str);
		if (index != -1)
			update = ft_iterthree(tools->env, &index, update, i);
	}
	return (update);
}

char	*ft_itertwo(char *update, char *str, t_tools *tools)
{
	int	i;

	i = 0;
	while (*str != '\0')
	{
		if (*str == '$')
		{
			str++;
			update = ft_iteraux(str, tools, &i, update);
			while (*str != ' ' && *str != '\0' && *str != '$')
				str++;
			if (*str == '\0')
				break ;
		}
		if (*str != '$')
		{
			update[i] = *str;
		}
		if ((*str) + 1 != '\0' && (*str) != '$')
		{
			str++;
			i++;
		}
	}
	return (update);
}
