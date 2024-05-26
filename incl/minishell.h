/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:14:29 by davgalle          #+#    #+#             */
/*   Updated: 2024/05/26 13:29:01 by davgalle         ###   ########.fr       */
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


typedef struct s_tools
{
	int			number_paths;
	int			here_doc;
	int			pipe_numb;
	int			*pipe;
	char		*commands;
	char		**env;
	char		*pwd;
	char		*old_pwd;
	bool		init;
	bool		error;
	t_string	**builtins;
	t_list		*history;
}	t_tools;

/*** MAIN ***/
int			main(int argc, char **argv, char **envp);

/*** LOOP ***/

bool		prompt_loop(t_string *cmd_input, t_tools *tools);

/*** PROMPT ***/

bool		check_exit(t_string *cmd_input);

/*** PARSE ***/

void		parse_shell(t_tools *tools);
void		check_commands(t_string *cmd_input, t_tools *tools);
char		*ft_findpath(char **envp);
t_string	*parse_strings(char c, char *str, unsigned int *i);
t_string	*parse_operators(char c, char *str, unsigned int *i);
t_string	*parse_tokens(char *str, unsigned int *i);
t_string	*parse_pipes(char c, char *str, unsigned int *i);
t_string	*parse_dollar(char c, char *str, unsigned int *i);
bool		next_string(t_list *tokens, unsigned int *i);
bool		is_operators(t_string *token);
void		get_op(t_string *token);
void		ft_built_ins(void);
int			ft_opcmp(char *str, char c);
bool		ft_opdollar(char *str, char c);

/*** UTILS ***/

int			ft_strncmp(char *str, char *dst, int numb);
size_t		ft_strlen(const char *s);
char		**dup_matrix(char **matrix);
char		*ft_strdup(char *s1);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strchr(char *str, int c);
char		*ft_strchr_hd(char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_substrop(char const *s, unsigned int start, size_t len);
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
void		get_pwd(t_tools *tools);
void		get_old_pwd(t_tools *tools);
char		**ft_split(char const *s, char c);
int			ft_isgoodenv(char *str);
int			custom_strncmp(char *prompt, char *built, int len, int blt);

/*** ERROR ***/

void		error_msg(char *str);
void		ft_errormsg(char *str);

/*** BUILTINS ***/

t_list		*builtins(void);
void		insert_global(t_list *list, char *command, int numb);
int			terminator(t_tools *tools, char *prompt, char *built, int blt);
bool		check_builtins(t_list *list, t_string *cmd_input, t_tools *tls);
void		ft_myprintecho(char **echo, t_tools *tools, int flag, int i);
int			ft_builtcmp(t_list *built, char *str, int len, int post);
void		get_builts(t_string *built, unsigned int i);
int			ft_echocmp(char *str, char *dst);
int			ft_myunset(char **env, char *name);
int			ft_findenv(char **env, char *name);
int			ft_myexport(char **env, char *prompt, t_tools *tools);
int			ft_customenvp(t_tools *tools);
void		ft_isquotes(char *str, int *quotes, int *single);
void		ft_writestr(char *echo, int flag, char **env, bool dollar);
int			ft_exit(char *prompt, char *built, int blt);

#endif
