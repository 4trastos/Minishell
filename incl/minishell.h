/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:14:29 by davgalle          #+#    #+#             */
/*   Updated: 2024/06/08 18:41:28 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../incl/list.h"
# include "../incl/executor.h"
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

extern int		g_signal;

typedef struct s_tools
{
	int				number_paths;
	int				here_doc;
	int				pipe_numb;
	int				*pipe;
	unsigned int	sizetokens;
	char			*commands;
	char			**env;
	char			**exp;
	char			**aux;
	char			*pwd;
	char			*old_pwd;
	bool			init;
	bool			error;
	char			*prompt;
	t_string		**builtins;
	t_list			*history;
}	t_tools;

typedef enum s_builtin
{
	BT_NONE,
	BT_CD,
	BT_ECHO,
	BT_EXPORT,
	BT_UNSET,
	BT_ENV,
}	t_builtin;

typedef enum s_operator
{
	OP_NONE,
	OP_INPUT_REDIRECT,
	OP_OUTPUT_REDIRECT,
	OP_PIPE,
	OP_HERE_DOC,
	OP_OUTPUT_REDIRECT_APPEND,
	OP_DOLLAR_SIGN,
	OP_BUILTIN,
}	t_operator;

typedef struct s_string
{
	unsigned int	size;
	char			*str;
	t_builtin		blt;
	t_operator		op;
}	t_string;

typedef struct s_list
{
	unsigned int	size;
	unsigned int	tokens;
	unsigned int	builts_numb;
	unsigned int	i;
	void			*value;
	t_string		**data;
}	t_list;

typedef struct s_executor
{
	int		here_doc_id;
	int		infile;
	int		outfile;
	int		num_cmd;
	int		num_pipes;
	int		*pipe_fd;
	int		i;
	int		status;
	int		exit_code;
	int		num_built;
	pid_t	*pid;
	char	*cmd;
	char	*rute;
	char	**fullcmd;
	char	**path;
	char	**env;
}	t_executor;

/*** MAIN ***/
int			main(int argc, char **argv, char **envp);

/*** LOOP ***/

bool		prompt_loop(t_string *cmd_input, t_tools *tools);

/*** PROMPT ***/

int			check_exit(t_string *cmd_input);

/*** PARSE ***/

void		parse_shell(t_tools *tools);
char		*ft_findpath(char **envp);
char		*ft_findhome(char **envp);
t_string	*parse_strings(char c, char *str, unsigned int *i);
t_string	*parse_operators(char c, char *str, unsigned int *i);
t_string	*parse_tokens(t_tools *tools, t_list *built, char *str,
				unsigned int *i);
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
char		**davsplit(char const *s, char c);
int			ft_isgoodenv(char *str);
int			custom_strncmp(char *prompt, char *built, int len, int blt);
int			ft_isalnum(int c);
void		ft_myenv(char **env);
char		*ft_findvarvalue(char *str);

/*** ERROR ***/

void		error_msg(char *str);
void		ft_errormsg(char *str);

/*** BUILTINS ***/

t_list		*builtins(void);
void		insert_global(t_list *list, char *command, int numb);
void		terminator(t_tools *tools, char *prompt, char *built, int blt);
void		check_builtins(t_tools *tools, t_list *built, char *input,
				int *flag);
void		ft_myprintecho(char *echo, t_tools *tools, int flag);
int			ft_builtcmp(t_list *built, char *str, int len, int post);
void		get_builts(t_string *built, unsigned int i);
int			ft_echocmp(char *str, char *dst);
int			ft_myunset(char **env, char *name);
int			ft_findenv(char **env, char *name);
int			ft_myexport(char **dup, t_tools *tools, char *prompt);
int			ft_customenvp(t_tools *tools);
void		ft_isquotes(char *str, char **env, int *doubles, int *single);
void		ft_writestr(char **echo, int flag, char **env, int index);
void		ft_putquotes(char *echo, char **env, int doubles, int single);
int			ft_exit(char *prompt, char *built, int blt);
t_list		*create_tokens(t_list *built, t_tools *tools, t_string *cmd_input);
void		ft_hatedollar(char *str, char **env);
void		ft_quotescount(char *str, int *doubles, int *single);

/*** SIGNAL ***/

void		handle_sigint(int sig);
void		init_sig(void);

#endif
