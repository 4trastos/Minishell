/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:49:08 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/07 20:13:20 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_quotescount(char *str, int *doubles, int *single, int *post_exp)
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
	printf("dobles -> %d #### simples -> %d ### posción del expansor -> %d\n", *doubles, *single, *post_exp);
}

/* void	ft_quotescount(char *str, char **env, int *doubles, int *single)
{
	int	i;

	i = 0;
	(void)env;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			(*doubles)++;
		else if (str[i] == 39)
			(*single)++;
		i++;
	}
} */
