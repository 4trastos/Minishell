/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/06/22 16:15:46 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	ft_findenv(char **env, char *name)
{
	char	*aux;
	int		len;
	int		i;

	i = 0;
	len = 0;
	aux = name;
	while (*name != '=' && *name != '\0' && *name != '\'' && *name != ' '
		&& *name != '"' && *name != '$')
	{
		len++;
		name++;
	}
	name = aux;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], aux, len) == 0 && (env[i][len] == '='
			|| env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

int	ft_isgoodenv(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 30 && str[i] <= 47))
			return (1);
		else if ((str[i] >= 58 && str[i] <= 64)
			|| (str[i] >= 91 && str[i] <= 126))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_createname(char *name, char c)
{
	char	*ptr;
	size_t	i;
	size_t	size_len;

	size_len = ft_strlen(name);
	i = 0;
	ptr = (char *)malloc(sizeof(char) * size_len + 2);
	if (ptr == NULL)
		return (NULL);
	while (name[i] != '\0')
	{
		ptr[i] = name[i];
		i++;
	}
	ptr[i] = c;
	ptr[i + 1] = '\0';
	return (ptr);
}

void	ft_isquotes(char *str, char **env, t_tools *tools, int *single)
{
	if (*single == -1)
		ft_hatedollar(str, env, tools);
	if (*single == 1 || *single == 0)
	{
		while (*str != '\0')
		{
			while (*str == '\'' && *str != '\0')
				str++;
			write(1, &(*str), 1);
			str++;
		}
	}
}

char	*ft_findvarvalue(char *str)
{
	while (*str != '=')
		str++;
	str++;
	return (str);
}
