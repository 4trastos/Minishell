/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/06/18 11:07:14 by davgalle         ###   ########.fr       */
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
		return (ft_create_shlvl(env, ft_mtx_len(env) + 1));
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
	char	**new;
	char	**aux;
	int		i;

	aux = dup_matrix(env);
	ft_doublefree(env);
	new = (char **)malloc(sizeof(char *) * len + 45);
	if (!new)
		return (NULL);
	i = 0;
	while (aux[i] != NULL)
	{
		new[i] = ft_strdup(aux[i]);
		i++;
	}
	new[i] = (char *)malloc(sizeof(char) * 8);
	new[i] = "SHLVL=1";
	new[i + 1] = NULL;
	ft_doublefree(aux);
	return (new);
}
