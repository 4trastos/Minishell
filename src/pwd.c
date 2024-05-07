/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicgonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/04/23 13:13:56 by nicgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include "../incl/list.h"

void	get_pwd(t_global *global)
{
	int		i;

	i = 0;
	while (global->envp[i])
	{
		if (ft_strncmp(global->envp[i], "PWD=", 4) == 0)
			break;
		i++;
	}
	global->pwd = ft_strtrim(global->envp[i], "PWD=");
}

void	get_old_pwd(t_global *global)
{
	int		i;

	i = 0;
	while (global->envp[i])
	{
		if (ft_strncmp(global->envp[i], "OLDPWD=", 7) == 0)
			break;
		i++;
	}
	global->old_pwd = ft_strtrim(global->envp[i], "OLDPWD=");
}