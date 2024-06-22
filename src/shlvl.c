/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/06/22 13:59:22 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

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
	int		n;

	num = ft_strtrim(str, "SHLVL=");
	n = ft_atoi(num);
	free(num);
	return (n);
}

char	**ft_addshlvl(char **env)
{
	int	i;
	int	lvl;
	int	len;

	i = -1;
	len = 0;
	while (env[len] != NULL)
		len++;
	if (!env[0])
		return (NULL);
	while (++i < len)
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
			break ;
	}
	if (i == ft_mtx_len(env))
		return (ft_create_shlvl(env, ft_mtx_len(env)));
	else
	{
		lvl = get_lvl(env[i]);
		lvl++;
		free(env[i]);
		env[i] = add_lvl(lvl);
	}
	return (env);
}

char	**ft_create_shlvl(char **env, int len)
{
	char	**aux;
	char	*new;

	aux = dup_matrix(env);
	aux = ft_realloc(aux, sizeof(char *) * (len + 2));
	if (!aux)
		return (NULL);
	new = malloc(8);
	if (!new)
	{
		free (aux);
		return (NULL);
	}
	new = "SHLVL=1";
	aux[len] = new;
	aux[len + 1] = NULL;
	return (aux);
}
