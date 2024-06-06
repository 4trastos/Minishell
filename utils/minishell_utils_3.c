/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/06/06 19:29:29 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"


int	ft_findenv(char **env, char *name)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (name[len] != '=' && name[len] != '\0')
		len++;
	if (name[len - 1] == '"')
		len--;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
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

void	ft_isquotes(char *str, char **env, int *doubles, int *single)
{
	if ((*doubles || !*doubles) && !*single)
		ft_hatedollar(str, env);
	if (*single)
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

/* int	ft_findenv(char **env, char *name)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (name[len] != '=' && name[len] != '\0')
		len++;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, len) == 0)
			return (i);
		i++;
	}
	return (-1);
} */

/* void	ft_isquotes(char *str, char **env, int *doubles, int *single)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			(*doubles)++;
		else if (str[i] == 39)
			(*single)++;
		i++;
	}
} */