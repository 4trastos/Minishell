/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:41:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/28 17:48:49 by davgalle         ###   ########.fr       */
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

	path = prompt;
	while (*path == ' ' || *path == 'c' || *path == 'd')
		path++;
	res = 0;
	res = chdir(path);
	if (res != 0)
	{
		perror("Error");
		return (EXIT_FAILURE);
	}
	if (tools->env)
	{
		update_pwd(tools);
		update_env(tools);
	}
	return (EXIT_SUCCESS);
}
