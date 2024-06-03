/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lists2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/03 11:37:38 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	**ft_realloc(char **env, size_t new_size)
{
	char	**new;
	int		i;

	new = malloc(new_size);
	if (!new)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		new[i] = env[i];
		i++;
	}
	new[i] = NULL;
	free(env);
	return (new);
}
