/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:25:32 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/28 17:25:53 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	g_signal = 1;

static void	ft_free_main(t_tools *tools)
{
	free(tools->pwd);
	free(tools->old_pwd);
}

char	*no_last_space(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	if (ft_strlen(str) < 2)
		return (str);
	while (str[i] != '\0')
		i++;
	if (str[--i] == ' ')
		str[i] = '\0';
	return (str);
}

int	main(int argc, char **argv, char **envp)
{
	t_tools		tools;
	t_string	*cmd_input;
	char		**aux;

	cmd_input = NULL;
	if (*envp == NULL)
		error_msg("Error: Missing environment variables");
	if (!ft_findpath(envp))
		error_msg("Error: finding PATH variable");
	if (argc > 1 || argv[1] != NULL)
		error_msg("This program does not accept arguments");
	aux = dup_matrix_envp(envp);
	tools.env = ft_addshlvl(aux);
	if (!tools.env)
		return (1);
	get_pwd(&tools);
	get_old_pwd(&tools);
	tools.exit_code = 0;
	rl_catch_signals = 0;
	while (prompt_loop(cmd_input, &tools))
		;
	ft_doublefree(tools.env);
	ft_free_main(&tools);
	rl_clear_history();
	return (0);
}
