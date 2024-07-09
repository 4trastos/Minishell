/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/09 09:08:34 by davgalle         ###   ########.fr       */
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
	else if (i == 7)
		built->blt = BT_PWD;
}

int	ft_myunset(t_tools *tools, char *name)
{
	char	*str;
	char	**new;
	char	**temp;
	int		index;
	int		i;

	index = 0;
	str = ft_updateunset(name);
	temp = ft_split(str, ' ');
	i = 0;
	while (temp[i] != NULL)
	{
		index = ft_findenv(tools->env, temp[i]);
		if (index != -1)
		{
			new = ft_updtmyunst(tools, index);
			ft_doublefree(tools->env);
			tools->env = dup_matrix(new);
		}
		i++;
	}
	ft_doublefree(temp);
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
		index = ft_findenv(tools->env, name[i]);
		if (ft_export_name(name[i]) == 1)
			write(1, "Invalid variable\n", 17);
		else if (index == -1)
			ft_addname(tools, name[i]);
		else
			ft_updatevalue(tools->env, name[i], index);
		if (name[i] != NULL)
			i++;
	}
	return (ft_doublefree(name), 0);
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

int	iter_str(char c)
{
	if (c == ' ' || c == '\0' || c == '$' || c == '\'' || c == '"'
		|| c == '\n')
		return (0);
	else
		return (1);
}
