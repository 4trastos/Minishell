/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:25:32 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/03 11:37:23 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	g_signal = 1;

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
	tools.env = dup_matrix(ft_addshlvl(aux));
	get_pwd(&tools);
	get_old_pwd(&tools);
	rl_catch_signals = 0;
	while (prompt_loop(cmd_input, &tools))
		;
	rl_clear_history();
	return (0);
}
