/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:13:54 by nicgonza          #+#    #+#             */
/*   Updated: 2024/06/28 19:15:56 by davgalle         ###   ########.fr       */
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

char	ft_get_char(char num)
{
	if (num == '0')
		return ('0');
	else if (num == '1')
		return ('1');
	else if (num == '2')
		return ('2');
	else if (num == '3')
		return ('3');
	else if (num == '4')
		return ('4');
	else if (num == '5')
		return ('5');
	else if (num == '6')
		return ('6');
	else if (num == '7')
		return ('7');
	else if (num == '8')
		return ('8');
	else if (num == '9')
		return ('9');
	return ('0');
}

char	*jujur_thegoat(t_tools *tools, char *str, char *update, int *i)
{
	int		index;

	index = 0;
	index = ft_findenv(tools->env, str);
	if (index != -1)
		update = ft_iterthree(tools->env, &index, update, i);
	return (update);
}

void	txurufluki_thegoat(t_tools *tools, char *str, int *add, int *subtract)
{
	int		index;

	index = 0;
	index = ft_findenv(tools->env, str);
	if (index != -1)
		ft_add_env(str, subtract, add, tools->env[index]);
}
