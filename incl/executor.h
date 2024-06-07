/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 09:31:05 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/03 13:09:59 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../incl/minishell.h"
# include "../incl/list.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef enum s_builtin		t_builtin;

typedef enum s_operator		t_operator;

typedef struct s_string		t_string;

typedef struct s_list		t_list;

typedef struct s_tools		t_tools;

typedef struct s_executor	t_executor;

int		here_doc(char *limiter, t_executor *exe);
int		get_infile(t_string *infile, t_executor *exe);
int		executor(t_list *tokens, t_tools *tools);
int		get_outfile(t_string *outfile, t_executor *exe);
char	*ft_new_line(char *board);
char	*ft_line(char *board);
char	*ft_read(int fd, char *board, int	*bytes_read);
int		get_next_line(int fd, char **line);
char	*get_doc_name(t_executor *exe);
void	delete_heredoc(t_executor *exe);
int		execute_cmd(t_list *tokens, t_executor *exe, t_tools *tools);
void	ft_exec_cmd(t_tools *tools, t_list *tokens, t_executor *exe, int i);
void	ft_dup2(int zero, int first);
void	create_pipes(t_executor *exe);
int		get_pipes(t_list *tokens, t_executor *exe);
int		get_cmds(t_list *tokens, t_executor *exe);
void 	get_command(t_list *tokens, t_executor *exe, t_tools *tools);
void	ft_close_pipes(t_executor *exe);
char	*get_rute(char *comand, char **paths);
void	ft_close_fd(t_executor *exe);
void	ft_free_exe(t_executor *exe);
int		ft_setparams(t_list *tokens, t_executor *exe);
char	*get_cmd_aux(t_list *tokens, int i);
void	ft_setexe(t_executor *executor, t_tools *tools);

#endif