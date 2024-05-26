/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/26 13:12:39 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"
#include "../incl/executor.h"
#include <limits.h>

void	get_builts(t_string *built, unsigned int i)
{
	if (i == 1)
		built->blt = BT_EXIT;
	else if (i == 2)
		built->blt = BT_CD;
	else if (i == 3)
		built->blt = BT_ECHO;
	else if (i == 4)
		built->blt = BT_PWD;
	else if (i == 5)
		built->blt = BT_EXPORT;
	else if (i == 6)
		built->blt = BT_UNSET;
	else
		built->blt = BT_ENV;
}

void	ft_myprintecho(char **echo, t_tools *tools, int flag, int i)
{
	int		k;
	int		quotes;
	int		single;
	bool	dollar;

	k = i;
	quotes = 0;
	single = 0;
	dollar = false;
	ft_isquotes(echo[k], &quotes, &single);
	if (ft_strchr(echo[i], '$') != NULL)
		dollar = true;
	if (quotes > 1 || single > 1)
	{
		write(1, "Tiene dobles comillas\n", 22);
	}
	else
		ft_writestr(echo[i], flag, tools->env, dollar);
	return ;
}

int	ft_mychdir(char *prompt)
{
	char	cwd[MAX_PATH_LEN];
	char	*path;

	path = prompt;
	while (*path == ' ' || *path == 'c' || *path == 'd')
		path++;
	if (*path == '\0')
	{
		printf("Error: Ruta vacía\n");
		return (0);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", path);
	else
	{
		perror("getcwd");
		return (0);
	}
	if (chdir(path) != 0)
	{
		perror("chdir");
		return (0);
	}
	return (0);
}

int	ft_myunset(char **env, char *name)
{
	char	*str;
	int		post;
	int		i;

	str = name;
	post = 0;
	while (*str == ' ' || *str == 'u' || *str == 'n' || *str == 's'
		|| *str == 'e' || *str == 't')
		str++;
	post = ft_findenv(env, str);
	if (post == -1)
	{
		printf("Variable de entorno: '%s' no encontrada\n", str);
		return (0);
	}
	env[post] = NULL;
	i = post;
	while (env[i] != NULL)
	{
		env[i] = env[i + 1];
		i++;
	}
	return (0);
}

int	ft_myexport(char **env, char *prompt, t_tools *tools)
{
	char	*str;
	char	*name;
	char	*value;
	int		index;

	str = prompt;
	while (*str == ' ' || *str == 'e' || *str == 'x' || *str == 'p'
		|| *str == 'o' || *str == 'r' || *str == 't')
		str++;
	if (*str == '\0')
		return (ft_customenvp(tools));
	name = str;
	value = ft_strchr(str, '=');
	if (value != NULL)
	{
		*value = '\0';
		value++;
	}
	index = ft_findenv(env, name);
	if (value == NULL)
		ft_addname(env, name, index);
	else
		ft_addvalue(env, name, index, value);
	return (0);
}
