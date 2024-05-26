/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/05/13 11:20:21 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"
#include "../incl/executor.h"

char	*add_lvl(int lvl)
{
	char	*new_lvl;
	char	*str;

	new_lvl = ft_itoa(lvl);
	str = ft_strjoin("SHLVL=", new_lvl);
	free(new_lvl);
	return (str);
}

int	get_lvl(char *str)
{
	char	*num;

	num = ft_strtrim(str, "SHLVL=");
	return (ft_atoi(num));
}

char	**ft_addshlvl(char **env)
{
	int	i;
	int	lvl;
	int len;

	i = 0;
	len = 0;
	while (env[len] != NULL)
		len++;
	if (!env[0])
		return (NULL);
	while (i < len)
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
			break ;
		i++;
	}
	if (i == ft_mtx_len(env))
		printf("No SHLVL variable\n");
	lvl = get_lvl(env[i]);
	lvl++;
	free(env[i]);
	env[i] = add_lvl(lvl);
	return (env);
}
