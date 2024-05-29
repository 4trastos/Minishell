/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/05/29 13:40:18 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"

int	ft_findenv(char **env, char *name)
{
	size_t	len;
	int		i;

	i = 0;
	while (name[len] != '=' && name[len] != '\0')
		len++;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, len) == 0)
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

void	ft_isquotes(char *str, int *quotes, int *single)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			(*quotes)++;
		else if (str[i] == 39)
			(*single)++;
		i++;
	}
}

void	ft_writestr(char *echo, int flag, char **env, bool dollar)
{
	int	index;

	index = 0;
	if (dollar)
	{
		echo++;
		index = ft_findenv(env, echo);
		if (index == -1)
			return ;
		printf("%s", env[index] + (ft_strlen(echo) + 1));
		if (flag == 0)
			printf("\n");
	}
	else
	{
		while (echo[index] != '\0')
		{
			while (echo[index] == '"' || echo[index] == 39)
				index++;
			write(1, &echo[index], 1);
			index++;
		}
		if (flag == 0)
			write(1, "\n", 1);
	}
}
