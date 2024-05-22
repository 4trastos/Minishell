/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/05/16 13:55:43 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"
#include "../incl/executor.h"

void	get_pwd(t_global *global)
{
	int		i;

	i = 0;
	while (global->env[i])
	{
		if (ft_strncmp(global->env[i], "PWD=", 4) == 0)
			break ;
		i++;
	}
	global->pwd = ft_strtrim(global->env[i], "PWD=");
}

void	get_old_pwd(t_global *global)
{
	int		i;

	i = 0;
	while (global->env[i])
	{
		if (ft_strncmp(global->env[i], "OLDPWD=", 7) == 0)
			break ;
		i++;
	}
	global->old_pwd = ft_strtrim(global->env[i], "OLDPWD=");
}
