/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:07:25 by brian             #+#    #+#             */
/*   Updated: 2025/04/16 20:44:40 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// condition to return true or false value
static inline t_token	*t_k(int cond, t_token *t_v, t_token *f_l)
{
	if (cond)
		return (t_v);
	else
		return (f_l);
}

// Same thing
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

	prev = prev_sep(token, NOSKIP); // Get the previous separator token
	next = next_sep(token, NOSKIP); // Get the next separator token
	pipe = 0;

	// Handle different types of redirections
	if (is_type(prev, TRUNC))
		redir(mini, token, TRUNC);
	else if (is_type(prev, APPEND))
		redir(mini, token, APPEND);
	else if (is_type(prev, INPUT))
		input(mini, token);
	else if (is_type(prev, PIPE))
		pipe = minipipe(mini);
	// Recursive handle the next command if exists
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

	// Get the first command token
	token = next_cmd(mini->start, NOSKIP);
	// Check if the first token is TRUNC, APPEND, INPUT
	token = t_k(is_types(mini->start, "TAI"), mini->start->next, token);
	// Process commands in a loop until the shell exits
	while (mini->exit == 0 && token)
	{
		mini->charge = 1;
		mini->parent = 1;
		mini->last = 1;
		redir_and_exec(mini, token);
		// Reset standard file descriptors and close open file descriptors
		reset_std(mini);
		close_fds(mini);
		reset_fds(mini);
		// Wait for child processes to finish
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status); // Exit status
		mini->ret = ternary_int((mini->last == 0), status, mini->ret);
		// Exit the shell if the process is a child
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
	mini.in = dup(STDIN);  // Duplicate standard input, keeping ori
	mini.out = dup(STDOUT);
	mini.exit = 0;
	mini.ret = 0;
	mini.no_exec = 0;
	reset_fds(&mini);
	init_env(&mini, env);
	init_secret_env(&mini, env); // Initialize secret environment variables
	increment_shell(mini.env); // increment shell casue we are in a new shell
	while (mini.exit == 0)
	{
		sig_init(&mini);  // Initialize signal handlers
		parse(&mini);
		if (mini.start != NULL && check_line(&mini, mini.start))
			minishell(&mini);
		free_token(mini.start);
	}
	free_env(mini.env);
	free_env(mini.secret_env);
	return (mini.ret);
}
