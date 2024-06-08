/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/08 18:30:40 by davgalle         ###   ########.fr       */
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

int	ft_myexport(char **dup, t_tools *tools, char *prompt)
{
	char	**name;
	char	*str;
	int		index;
	int		i;

	(void)dup;
	str = prompt;
	while (*str == ' ' || *str == 'e' || *str == 'x' || *str == 'p'
		|| *str == 'o' || *str == 'r' || *str == 't')
		str++;
	if (*str == '\0' || tools->sizetokens > 1)
	{
		ft_customenvp(tools);
		ft_printenvp(tools);
		return (0);
	}
	name = ft_split(str, ' ');
	i = 0;
	while (name[i] != NULL)
	{
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
