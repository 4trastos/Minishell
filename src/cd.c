/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/01 10:20:20 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	update_pwd(t_tools *tools)
{
	char	*temp;

	temp = tools->pwd;
	free(tools->old_pwd);
	tools->old_pwd = temp;
	tools->pwd = getcwd(NULL, 0);
	update_env(tools);
	return (1);
}

int	update_env(t_tools *tools)
{
	int		i;
	char	*temp;

	i = 0;
	while (tools->env[i])
	{
		if (ft_strncmp(tools->env[i], "PWD=", 4) == 0)
		{
			temp = ft_strjoin("PWD=", tools->pwd);
			free(tools->env[i]);
			tools->env[i] = temp;
		}
		else if (ft_strncmp(tools->env[i], "OLDPWD=", 7) == 0)
		{
			temp = ft_strjoin("OLDPWD=", tools->old_pwd);
			free(tools->env[i]);
			tools->env[i] = temp;
		}
		i++;
	}
	return (1);
}

int	ft_mychdir(char *prompt, t_tools *tools)
{
	int		res;
	char	*path;
	char	*dir;

	path = prompt;
	while (*path == ' ' || *path == 'c' || *path == 'd')
		path++;
	path = ft_strtrim(path, " ");
	res = 0;
	if (*path == '\0')
	{
		if (chdir(ft_findhome(tools->env)) != 0)
			return (free(path), perror("chdir"), 1);
		return (0);
	}
	dir = getcwd(NULL, 0);
	if (dir == NULL)
		return (free(dir), free(path), EXIT_FAILURE);
	res = chdir(path);
	if (res != 0)
		return (perror("Error"), free(dir), free(path), EXIT_FAILURE);
	if (tools->env)
		update_pwd(tools);
	return (free(dir), free(path), EXIT_SUCCESS);
}

int	ft_fluki(char **test, unsigned int *i)
{
	int	space;

	space = 0;
	while (**test == ' ' && **test != '\0')
	{
		(*test)++;
		(*i)++;
		space = 1;
	}
	return (space);
}

int	get_n_red(char *str, unsigned int i, char c)
{
	unsigned int	count;

	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	if (count == 2 || count == 1)
		return (1);
	else
		return (0);
}
