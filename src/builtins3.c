/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/03 12:53:57 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void	ft_printenvp_ii(char *str, int *flag)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=' && *flag != 2)
			*flag = 1;
		if (str[i] != '=' )
		{
			if (*flag == 1)
			{
				write(1, "\"", 1);
				*flag = 2;
			}
		}
		write(1, &str[i], 1);
		i++;
	}
}

void	ft_printenvp(char **str)
{
	int	i;
	int	flag;

	i = 0;
	while (str[i] != NULL)
	{
		ft_putstr("declare -x ");
		flag = 0;
		ft_printenvp_ii(str[i], &flag);
		if (flag == 1)
		{
			write(1, "\"", 1);
			write(1, "\"", 1);
		}
		else if (flag == 2)
			write(1, "\"", 1);
		write(1, "\n", 1);
		i++;
	}
}

int	ft_strcmp(char *str1, char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

int	ft_customenvp(char **dup)
{
	char	*aux;
	int		i;
	int		swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (dup[i + 1] != NULL)
		{
			if (ft_strcmp(dup[i], dup[i + 1]) > 0)
			{
				aux = dup[i];
				dup[i] = dup[i + 1];
				dup[i + 1] = aux;
				swapped = 1;
			}
			i++;
		}
	}
	ft_printenvp(dup);
	return (0);
}

int	ft_exit(char *prompt, char *built, int blt)
{
	int	i;
	int	len;

	len = ft_strlen(built);
	i = custom_strncmp(prompt, built, len, blt);
	if (i != 0)
		return (0);
	return (blt);
}
