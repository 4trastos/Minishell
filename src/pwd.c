/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/06/03 13:14:16 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	get_pwd(t_tools *tools)
{
	int		i;

	i = 0;
	while (tools->env[i])
	{
		if (ft_strncmp(tools->env[i], "PWD=", 4) == 0)
			break ;
		i++;
	}
	tools->pwd = ft_strtrim(tools->env[i], "PWD=");
}

void	get_old_pwd(t_tools *tools)
{
	int		i;

	i = 0;
	while (tools->env[i])
	{
		if (ft_strncmp(tools->env[i], "OLDPWD=", 7) == 0)
			break ;
		i++;
	}
	tools->old_pwd = ft_strtrim(tools->env[i], "OLDPWD=");
}
