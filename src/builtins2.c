/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/28 17:58:35 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include <limits.h>

void	get_builts(t_string *built, unsigned int i)
{
	if (i == 0)
		built->blt = BT_NONE;
	else if (i == 1)
		built->blt = BT_CD;
	else if (i == 2)
		built->blt = BT_ECHO;
	else if (i == 3)
		built->blt = BT_EXPORT;
	else if (i == 4)
		built->blt = BT_UNSET;
	else if (i == 5)
		built->blt = BT_ENV;
	else if (i == 6)
		built->blt = BT_EXIT;
}

int	ft_myunset(t_tools *tools, char *name)
{
	char	*str;
	char	**new;
	int		index;

	str = name;
	index = 0;
	while (*str == ' ' || *str == 'u' || *str == 'n' || *str == 's'
		|| *str == 'e' || *str == 't')
		str++;
	index = ft_findenv(tools->env, str);
	if (index == -1)
	{
		printf("Variable de entorno: '%s' no encontrada\n", str);
		return (1);
	}
	new = ft_updtmyunst(tools, index);
	ft_doublefree(tools->env);
	tools->env = dup_matrix(new);
	return (0);
}

int	ft_myexport(t_tools *tools, char *prompt)
{
	char	**name;
	int		index;
	int		i;

	prompt = ft_updatexport(prompt);
	if (ft_exportchek(prompt, tools) == 0)
		return (0);
	name = ft_split(prompt, ' ');
	i = 0;
	while (name[i] != NULL)
	{
		if (ft_export_name(name[i]) == 1)
		{
			write(1, "Invalid variable\n", 17);
			return (1);
		}
		index = ft_findenv(tools->env, name[i]);
		if (index == -1)
			ft_addname(tools, name[i]);
		else
			ft_updatevalue(tools->env, name[i], index);
		i++;
	}
	ft_doublefree(name);
	return (0);
}

char	*prsstraux(char *aux, char *str, unsigned int *i, t_tools *tools)
{
	char	*temp;
	char	*jujur;

	temp = ft_moretoken(str, i, tools);
	jujur = ft_strjoin(aux, temp);
	free(temp);
	free(aux);
	return (jujur);
}
