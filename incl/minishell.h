/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:14:29 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/01 09:01:13 by davgalle         ###   ########.fr       */
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
	int				exit_code;
	int				*pipe;
	int				flag;
	int				hd_flag;
	int				index;
	unsigned int	sizetokens;
	char			*commands;
	char			**env;
	char			**exp;
	char			*aux;
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
	BT_EXIT,
	BT_PWD,
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
	int		flag;
	int		chk_fd;
	int		*pipe_fd;
	int		i;
	int		status;
	int		num_built;
	pid_t	*pid;
	char	*cmd;
	char	*rute;
	char	**fullcmd;
	char	**path;
	char	**env;
	char	**aux;
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
t_string	*parse_strings(char c, char *str, unsigned int *i, t_tools *tools);
t_string	*parse_operators(char c, char *str, unsigned int *i,
				t_tools *tools);
t_string	*parsetks(t_tools *tools, t_list *built, char *str,
				unsigned int *i);
t_string	*parse_pipes(char c, char *str, unsigned int *i, t_tools *tools);
t_string	*parse_dollar(char c, char *str, unsigned int *i, t_tools *tools);
bool		next_string(t_list *tokens, unsigned int *i);
bool		is_operators(t_string *token);
void		get_op(t_string *token);
void		ft_built_ins(void);
int			ft_opcmp(char *str, char c);
bool		ft_opdollar(char *str, char c);
t_list		**ft_split_tokens(t_list *tokens);
t_string	*ft_prcplt(t_list *blt, t_tools *tools, char *str, unsigned int *i);
int			ft_exportchek(char *prompt, t_tools *tools);
int			ft_checkquote(char *echo, int *len, char quote);
void		ft_updateprtkn(char *str, unsigned int *i);
char		*updatedollar(char *str, t_tools *tools);
void		piticli_boniko(char *str, unsigned int *i,
				char c, unsigned int *rest);

/*** UTILS ***/

int			ft_strncmp(char *str, char *dst, int numb);
size_t		ft_strlen( char *s);
char		**dup_matrix(char **matrix);
char		*ft_strdup(char *s1);
char		*ft_strtrim(char *s1, char *set);
char		*ft_strchr(char *str, int c);
char		*ft_strchr_hd(char *s, int c);
char		*ft_substr(char *s, unsigned int start, size_t len);
char		*ft_substrop(char *s, unsigned int start, size_t len);
void		ft_bzero(void *str, size_t n);
void		*ft_calloc(size_t n, size_t b);
void		*ft_memcpy(void *dst, void *src, size_t n);
int			ft_mtx_len(char **mtx);
int			get_lvl(char *str);
char		**ft_addshlvl(char **env);
char		*add_lvl(int lvl);
int			ft_atoi( char *str);
char		*ft_itoa(int n);
char		*ft_strjoin(char *s1, char *s2);
void		ft_putstr_fd(char *s, int fd);
void		get_pwd(t_tools *tools);
void		get_old_pwd(t_tools *tools);
char		**ft_split(char *s, char c);
char		**davsplit(char *s, char c);
int			ft_isgoodenv(char *str);
int			custom_strncmp(char *prompt, char *built, int len);
int			ft_isalnum(int c);
void		ft_myenv(char **env);
char		*ft_findvarvalue(char *str);
char		**ft_create_shlvl(char **env, int len);
int			ft_get_code(int cod);
int			ft_isdigit(int c);
int			ft_export_name(char *str);
int			ft_find_out(t_list *l);
int			ft_split_part(t_list *tokens, unsigned int *j);
char		**dup_matrix_envp(char **matrix);
int			ft_exit_toaux(char c);
void		ft_auxgtf(t_executor *exe, t_tools *tools, char *file);
void		ft_empty_doc(t_executor *exe, t_tools *tools);
int			ft_validator_extra(char *echo, int *quotes, int *flag);
char		*no_last_space(char *str);
void		ft_updateprtkn2(char *str, unsigned int *i);
char		*trimspace(char *str);
void		ft_prstksaux(t_tools *tools, char *str, int start, unsigned int *i);
void		ft_updatemrtk(char **test, unsigned int *result);
void		ft_updtfinaltk(char **aux, unsigned int *result);
int			update_pwd(t_tools *tools);
int			update_env(t_tools *tools);
char		ft_get_char(char num);
int			get_n_red(char *str, unsigned int i, char c);

/*** ERROR ***/

void		error_msg(char *str);
void		ft_errormsg(char *str);

/*** BUILTINS ***/

t_list		*builtins(void);
void		insert_global(t_list *list, char *command, int numb);
int			terminator(t_tools *tools, char *prompt, int blt);
void		check_builtins(t_tools *tools, t_list *built, char *input,
				int *flag);
void		ft_myprintecho(char *echo, int flag);
int			ft_builtcmp(t_list *built, char *str, int len, int post);
void		get_builts(t_string *built, unsigned int i);
int			ft_echocmp(char *str, char *dst);
int			ft_myunset(t_tools *tools, char *name);
int			ft_findenv(char **env, char *name);
int			ft_myexport(t_tools *tools, char *prompt);
int			ft_customenvp(t_tools *tools);
void		ft_isquotes(char *str, char **env, t_tools *tools, int *single);
void		ft_writestr(char **echo, int flag, char **env, int index);
t_list		*create_tokens(t_list *built, t_tools *tools, t_string *cmd_input);
int			ft_hatedollar(char *str, char **env, t_tools *tools);
int			ft_testdollar(char *str, char **env);
char		*ft_updatexport(char *prompt);
int			ft_validator(char *echo);
void		ft_putquotes(char *echo);
void		ft_exit(char *str);
void		ft_executator(t_list *tokens, t_tools *tools);
void		ft_execut_part(t_list **arr_tokens, t_tools*tools, unsigned int *i);
void		ft_get_commpart(t_list *tokens, t_executor *exe, int *flag, int *i);
int			ft_updatetspc(char *str);
char		**ft_updtmyunst(t_tools *tools, int index);
char		*jujur_thegoat(t_tools *tools, char *str, char *update, int *i);
void		txurufluki_thegoat(t_tools *tools, char *str,
				int *add, int *subtract);
char		*ft_iterthree(char **env, int *index, char *update, int *i);
void		ft_add_env(char *str, int *subtract, int *add, char *var);
int			ft_fluki(char **test, unsigned int *i);
char		*ft_updateunset(char *prompt);

/*** SIGNAL ***/

void		handle_sigint(int sig);
void		init_sig(void);

#endif
