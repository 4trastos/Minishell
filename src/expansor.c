/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:59:17 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/28 19:17:16 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_add_env(char *str, int *subtract, int *add, char *var)
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
	char	*ec;

	ec = ft_itoa(tools->exit_code);
	while (*str != '\0')
	{
		if (*str == '$')
		{
			str++;
			if (*str == '?')
			{
				*subtract += 2;
				*add += ft_strlen(ec);
				str++;
			}
			else
				txurufluki_thegoat(tools, str, add, subtract);
		}
		if (*str != '\0')
			str++;
	}
	free(ec);
}

char	*ft_iterthree(char **env, int *index, char *update, int *i)
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
	char	*exit_code;
	char	tmp;
	char	*start;

	if (*str == '?')
	{
		exit_code = ft_itoa(tools->exit_code);
		start = exit_code;
		while (*exit_code != '\0')
		{
			tmp = ft_get_char(*exit_code);
			update[*i] = tmp;
			(*i)++;
			exit_code++;
		}
		free(start);
		str++;
	}
	else
		update = jujur_thegoat(tools, str, update, i);
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
			while (iter_str(*str) == 1)
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
