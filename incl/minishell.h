/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:14:29 by davgalle          #+#    #+#             */
/*   Updated: 2024/04/30 18:25:55 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../incl/list.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <sys/ioctl.h>

# define PROMPT "Minishell> "

typedef struct s_global
{
	int		number_paths;
	int		here_doc;
	int		pipe_numb;
	int		*pipe;
	char	*commands;
	char	**envp;
	bool	init;
	bool	error;
	t_list 	*history;
}	t_global;

typedef struct s_tools
{
	int		input;
	int		output;
	char	*input_line;
	t_global	*global;
}	t_tools;

/*** MAIN ***/
int			main(int argc, char **argv, char **envp);

/*** LOOP ***/
void    	prompt_loop(t_tools *tools);

/*** BUILD_IN ***/

/*** PROMPT ***/

int     check_exit(t_tools *tools);

/*** PARSE ***/

void		parse_shell(t_global global, char** argv);
char		*ft_findpath(char **envp);

/*** UTILS ***/
int			ft_strncmp(char *str, char *dst, int numb);
size_t		ft_strlen(const char *s);
char    	**dup_matrix(char **matrix);
char		*ft_strdup(const char *s1);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strchr(const char *str, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		*ft_bzero(void *str, size_t n);
void		*ft_calloc(size_t n, size_t b);
void		*ft_memcpy(void *dst, const void *src, size_t n);

/*** ERROR ***/

void		error_msg(char *str);
void		ft_errormsg(char *str);

#endif
