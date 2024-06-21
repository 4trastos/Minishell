/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:25:32 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/21 11:46:07 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	g_signal = 1;

static void	ft_free_main(t_tools *tools)
{
	free(tools->pwd);
	free(tools->old_pwd);
	ft_doublefree(tools->env);
}

static void	ft_init_tools(t_tools *tools)
{
	get_pwd(tools);
	get_old_pwd(tools);
	tools->exit_code = 0;
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
	aux = dup_matrix(envp);
	tools.aux = ft_addshlvl(aux);
	tools.env = dup_matrix(tools.aux);
	ft_doublefree(aux);
	if (!tools.env)
		return (1);
	ft_init_tools(&tools);
	rl_catch_signals = 0;
	while (prompt_loop(cmd_input, &tools))
		;
	rl_clear_history();
	ft_free_main(&tools);
	return (0);
}
