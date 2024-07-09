/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:25:32 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/30 13:34:02 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*get_doc_name(t_executor *exe)
{
	char	*str;
	char	*file;
	char	*id;

	id = ft_itoa(exe->here_doc_id);
	str = ft_strjoin("/tmp/.here_doc", id);
	file = ft_strjoin(str, ".tmp");
	free(id);
	free(str);
	return (file);
}

static char	*no_quotes(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (ft_strchr(str, '\'') != NULL || ft_strchr(str, '"') != NULL)
	{
		new = (char *)malloc(sizeof(char) * (ft_strlen(str) - 1));
		while (str[j] != '\'' && str[j] != '"')
		{
			new[i] = str[j];
			j++;
			i++;
		}
		new[i] = '\0';
		free(str);
		return (new);
	}
	else
		return (str);
}

static void	expand_here_doc(int file, char *str, t_tools *tools)
{
	while (*str != '\0')
	{
		if (*str == '$')
		{
			str++;
			if (*str == '?')
			{
				ft_putstr_fd(ft_itoa(tools->exit_code), file);
				str++;
			}
			else
			{
				tools->index = 0;
				tools->index = ft_findenv(tools->env, str);
				if (tools->index != -1)
				{
					write_env(tools->env[tools->index], file);
					while (iter_str(*str) == 1)
						str++;
				}
			}
		}
		write(file, str++, 1);
	}
}

static int	here_doc_aux(char *limiter, int file, t_tools *tools)
{
	char	*buf;
	char	*new_limiter;

	if (tools->hd_flag == 1)
		new_limiter = no_quotes(limiter);
	else
		new_limiter = limiter;
	while (1)
	{
		buf = readline(">");
		if (g_signal != 100)
			return (free_here_doc(buf, new_limiter, tools), 1);
		if (!buf || (!ft_strncmp(new_limiter, buf, ft_strlen(new_limiter))
				&& ft_strlen(buf) == ft_strlen(new_limiter)))
			break ;
		buf = ft_strjoin(buf, "\n");
		if (tools->hd_flag != 1)
			expand_here_doc(file, buf, tools);
		else
			write(file, buf, ft_strlen(buf));
		free(buf);
	}
	if (tools->hd_flag == 1)
		free(new_limiter);
	return (free(buf), 0);
}

int	here_doc(char *limiter, t_executor *exe, t_tools *tools)
{
	int		file;
	char	*file_name;

	g_signal = 100;
	file_name = get_doc_name(exe);
	file = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file < 0)
		return (-1);
	if (here_doc_aux(limiter, file, tools) == 1)
		return (free(file_name), 1);
	close(file);
	exe->infile = open(file_name, O_RDONLY);
	if (exe->infile < 0)
	{
		free(file_name);
		return (-1);
	}
	free(file_name);
	return (0);
}
