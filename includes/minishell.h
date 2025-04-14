/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:07:21 by brian             #+#    #+#             */
/*   Updated: 2025/04/15 03:59:43 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SKIP 1
# define NOSKIP 0

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7

# define SUCCESS 0
# define ERROR 1
# define BUFF_SIZE 4096
# define EXPANSION -36
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127

// ANSI escape sequence colors
# define RESET "\033[0m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_sig
{
	int		sigint;
	int		sigquit;
	int		exit_status;
	pid_t	pid;
}	t_sig;

typedef struct s_expansions
{
	char	*new_arg;
	int		i;
	int		j;
}	t_expansions;

typedef struct s_mini
{
	t_token		*start;
	t_env		*env;
	t_env		*secret_env;
	int			in;
	int			out;
	int			fdin;
	int			fdout;
	int			pipin;
	int			pipout;
	int			pid;
	int			charge;
	int			parent;
	int			last;
	int			ret;
	int			exit;
	int			no_exec;
	int			sigint;
	int			sigquit;
	int			exit_status;
	int			in_cmd;
	int			in_heredoc;
}	t_mini;

// Builtins
char		*get_env_value(char *arg, t_env *env);
char		*get_env_key(char *dest, const char *src);
void		mini_exit(t_mini *mini, char **cmd);
int			ft_cd(char **args, t_env *env);
int			ft_pwd(void);
int			ft_env(t_env *env);
int			ft_export(char **args, t_env *env, t_env *secret);
int			ft_unset(char **a, t_mini *mini);
int			env_add(const char *value, t_env *env);
int			is_in_env(t_env *env, char *args);
int			choose_new_env(int error_ret, t_env *env, char *arg);

// Helper
void		reset_fds(t_mini *mini);
int			quotes(char *line, int index);
t_token		*prev_sep(t_token *token, int skip);
int			is_type(t_token *token, int type);
char		*get_var_value(const char *arg, int pos, t_env *env, int ret);
void		print_token_or_newline(t_token *token);

// Envs
int			init_env(t_mini *mini, char **env_array);
int			init_secret_env(t_mini *mini, char **env_array);
int			is_env_char(int c);
size_t		size_env(t_env *lst);
char		*env_to_str(t_env *lst);
int			is_valid_env(const char *env);
void		print_sorted_env(t_env *env);

// Signals
void		sig_init(t_mini *mini);
void		sig_int(int code);
void		sig_quit(int code);

// Parsing
int			ignore_sep(char *line, int i);
int			is_last_valid_arg(t_token *token);
int			check_line(t_mini *mini, t_token *token);
int			is_seperator(char *line, int i);
int			arg_alloc_len(const char *arg, t_env *env, int ret);
char		*expansions(char *arg, t_env *env, int ret);
void		output_emoji(int ret);
int			mini_ret(int cond, int true_val, int false_val);
void		fill_token(char *line, int *i, t_token *token);

// Tokens
t_token		*get_tokens(char *line);
void		type_arg(t_token *token, int separator);
void		squish_args(t_mini *mini);

// Token
t_token		*next_sep(t_token *token, int skip);
t_token		*prev_sep(t_token *token, int skip);
t_token		*next_cmd(t_token *token, int skip);
int			next_alloc(char *line, int *i);

// Redir
void		input(t_mini *mini, t_token *token);
void		redir(t_mini *mini, t_token *token, int type);
int			minipipe(t_mini *mini);

// Fd
void		reset_std(t_mini *mini);
void		close_fds(t_mini *mini);
void		reset_fds(t_mini *mini);
void		ft_close(int fd);

// Line
void		parse(t_mini *mini);

// Free
void		free_tab(char **tab);
void		free_env(t_env *env);

// Types
int			is_type(t_token *token, int type);
int			is_types(t_token *token, char *types);
void		free_token(t_token *start);
int			has_pipe(t_token *token);

// Shell level
void		increment_shell(t_env *env);

// Exec
int			ft_echo(char **args);
int			exec_builtin(char **args, t_mini *mini);
int			is_builtin(char *command);
int			exec_bin(char **args, t_env *env, t_mini *mini);
void		exec_cmd(t_mini *mini, t_token *token);
int			normalize_exit_code(int ret);

#endif