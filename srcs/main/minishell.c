/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:07:25 by brian             #+#    #+#             */
/*   Updated: 2025/04/30 01:57:24 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline t_token	*t_k(int cond, t_token *t_v, t_token *f_l)
{
	if (cond)
		return (t_v);
	else
		return (f_l);
}

static inline int	ternary_int(int cond, int true_val, int false_val)
{
	if (cond)
		return (true_val);
	else
		return (false_val);
}

void	redir_and_exec(t_mini *mini, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;

	prev = prev_sep(token, NOSKIP);
	next = next_sep(token, NOSKIP);
	pipe = 0;
	if (is_type(prev, TRUNC))
		redir(mini, token, TRUNC);
	else if (is_type(prev, APPEND))
		redir(mini, token, APPEND);
	else if (is_type(prev, HEREDOC))
		handle_heredoc(mini, token->str, !token->quoted);
	else if (is_type(prev, INPUT))
		input(mini, token);
	else if (is_type(prev, PIPE))
		pipe = minipipe(mini);
	if (next && is_type(next, END) == 0 && pipe != 1)
		redir_and_exec(mini, next->next);
	if ((is_type(prev, END) || is_type(prev, PIPE) || !prev)
		&& pipe != 1 && mini->no_exec == 0)
		exec_cmd(mini, token);
}

void	minishell(t_mini *mini)
{
	t_token	*token;
	int		status;

	token = next_cmd(mini->start, NOSKIP);
	token = t_k(is_types(mini->start, "TAHI"), mini->start->next, token);
	while (mini->exit == 0 && token)
	{
		mini->charge = 1;
		mini->parent = 1;
		mini->last = 1;
		redir_and_exec(mini, token);
		reset_std(mini);
		close_fds(mini);
		reset_fds(mini);
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		mini->ret = ternary_int((mini->last == 0), status, mini->ret);
		if (mini->parent == 0)
		{
			free_token(mini->start);
			exit(mini->ret);
		}
		mini->no_exec = 0;
		token = next_cmd(token, SKIP);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	(void)env;
	mini.in = dup(STDIN);
	mini.out = dup(STDOUT);
	mini.exit = 0;
	mini.ret = 0;
	mini.no_exec = 0;
	reset_fds(&mini);
	init_env(&mini, env);
	init_secret_env(&mini, env);
	increment_shell(mini.env);
	while (mini.exit == 0)
	{
		sig_init(&mini);
		parse(&mini);
		if (mini.start != NULL && check_line(&mini, mini.start))
			minishell(&mini);
		free_token(mini.start);
	}
	free_env(mini.env);
	free_env(mini.secret_env);
	return (mini.ret);
}
