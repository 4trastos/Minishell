/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:14:29 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/07 20:14:43 by usuario          ###   ########.fr       */
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
# define INCREASE 20

typedef struct s_global
{
	int		number_paths;
	int		here_doc;
	int		pipe_numb;
	int		*pipe;
	char	*commands;
	char	**envp;
	char	*pwd;
	char	*old_pwd;
	bool	init;
	bool	error;
	t_list 	*history;
}	t_global;

typedef struct s_tools
{
	int		input;
	int		output;
	char	*input_line;
	t_global	*ptr_global;
}	t_tools;

/*** MAIN ***/
int				main(int argc, char **argv, char **envp);

/*** LOOP ***/
bool    		prompt_loop(t_string *cmd_input);

/*** BUILD_IN ***/

/*** PROMPT ***/

bool 	    check_exit(t_string *cmd_input);

/*** PARSE ***/

void			parse_shell(t_tools *tools);
char			*ft_findpath(char **envp);
t_string		*parse_strings(char c, char *str, unsigned int *i);
void			check_commands(t_string *cmd_input);
t_string    	*parse_operators(char c, char *str, unsigned int *i);
t_string    	*parse_tokens(char *str, unsigned int *i);
t_string    	*parse_parenthesis(char c, char *str, unsigned int *i);
bool			next_iter(t_iterlist *iter);

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
int			ft_mtx_len(char **mtx);
int			get_lvl(char *str);
char		**ft_addshlvl(char **env);
char		*add_lvl(int lvl);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_putstr_fd(char *s, int fd);
void		get_pwd(t_global *global);
void		get_old_pwd(t_global *global);

/*** ERROR ***/

void		error_msg(char *str);
void		ft_errormsg(char *str);

#endif
