/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/21 17:50:32 by davgalle         ###   ########.fr       */
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

int	ft_mychdir(char *prompt, t_tools *tools)
{
	char	cwd[MAX_PATH_LEN];
	char	*path;
	int		i;

	path = prompt;
	while (*path == ' ' || *path == 'c' || *path == 'd')
		path++;
	path = ft_strtrim(path, " ");
	if (*path == '\0')
	{
		if (chdir(ft_findhome(tools->env)) != 0)
			perror("chdir");
	}
	else if (*path == '$')
	{
		path++;
		i = ft_findenv(tools->env, path);
		if (chdir(ft_findvarvalue(tools->env[i])) != 0)
			perror("chdir");
	}
	else if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd");
	else if (chdir(path) != 0)
		perror("chdir");
	return (0);
}

int	ft_myunset(char **env, char *name)
{
	char	*str;
	int		index;
	int		i;

	str = name;
	index = 0;
	while (*str == ' ' || *str == 'u' || *str == 'n' || *str == 's'
		|| *str == 'e' || *str == 't')
		str++;
	index = ft_findenv(env, str);
	if (index == -1)
	{
		printf("Variable de entorno: '%s' no encontrada\n", str);
		return (0);
	}
	env[index] = NULL;
	i = index;
	while (env[i] != NULL)
	{
		env[i] = env[i + 1];
		i++;
	}
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
			return (0);
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
