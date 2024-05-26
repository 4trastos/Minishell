/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/24 13:30:57 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"
#include "../incl/executor.h"

int	ft_customenvp(t_tools *tools)
{
	int	i;

	i = 0;
	while (tools->env[i] != NULL)
	{
		printf("%s\n", tools->env[i]);
		i++;
	}
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

