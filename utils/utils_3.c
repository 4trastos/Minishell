/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:49:08 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/10 09:34:01 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_quotescount(char *str, int *doubles, int *single)
{
	int	s;
	int	i;

	s = 0;
	i = 0;
	(void)doubles;
	while (*str != '\0')
	{
		if (str[i] == '\'')
		{
			s++;
			*single = !*single;
		}
		i++;
	}
	if (s % 2 != 0 && *single)
		ft_errormsg("Error\n");
}

/* void	ft_quotescount(char *str, int *doubles, int *single, int *post_exp)
{
	int	i;

	i = 0;
	(*doubles) = 0;
	(*post_exp) = -1;
	(*single) = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			(*doubles)++;
		else if (str[i] == 39)
			(*single)++;
		else if (str[i] == '$')
			(*post_exp) = i;
		i++;
	}
}*/
