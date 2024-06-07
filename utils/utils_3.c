/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:49:08 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/07 16:05:23 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_quotescount(char *str, char **env, int *doubles, int *single)
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
}