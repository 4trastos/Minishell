/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/18 10:39:58 by davgalle         ###   ########.fr       */
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
				printf("\"");
				*flag = 2;
			}
		}
		printf("%c", str[i]);
		i++;
	}
}

void	ft_printenvp(t_tools *tools)
{
	int	i;
	int	flag;

	i = 0;
	while (tools->exp[i] != NULL)
	{
		printf("declare -x ");
		flag = 0;
		ft_printenvp_ii(tools->exp[i], &flag);
		if (flag == 1)
		{
			printf("\"");
			printf("\"");
		}
		else if (flag == 2)
			printf("\"");
		printf("\n");
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

int	ft_customenvp(t_tools *tools)
{
	char	*aux;
	int		i;
	int		swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (tools->exp[i + 1] != NULL)
		{
			if (ft_strcmp(tools->exp[i], tools->exp[i + 1]) > 0)
			{
				aux = tools->exp[i];
				tools->exp[i] = tools->exp[i + 1];
				tools->exp[i + 1] = aux;
				swapped = 1;
			}
			i++;
		}
	}
	return (0);
}
