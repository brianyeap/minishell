/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:07:25 by brian             #+#    #+#             */
/*   Updated: 2025/04/25 05:45:46 by brian            ###   ########.fr       */
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

	prev = prev_sep(token, NOSKIP);  // find the prev sep token
	next = next_sep(token, NOSKIP);  // find the next sep token
	pipe = 0;
	if (is_type(prev, TRUNC))
		redir(mini, token, TRUNC);
	else if (is_type(prev, APPEND))
		redir(mini, token, APPEND);
	else if (is_type(prev, INPUT))
		input(mini, token);
	else if (is_type(prev, PIPE))
		pipe = minipipe(mini); // return 1 for parent and 2 for child
	if (next && is_type(next, END) == 0 && pipe != 1) // if there is next command and it's not the end and it's a child
		redir_and_exec(mini, next->next); // recursive to handle the remaining pipe
	if ((is_type(prev, END) || is_type(prev, PIPE) || !prev)
		&& pipe != 1 && mini->no_exec == 0)
		exec_cmd(mini, token);  // execute if at the start or after | or ; and is child and can exec
}

void	minishell(t_mini *mini)
{
	t_token	*token;
	int		status;

	token = next_cmd(mini->start, NOSKIP); // getting the next CMD
	token = t_k(is_types(mini->start, "TAI"), mini->start->next, token); // skipping the first token if it is a redirection
	while (mini->exit == 0 && token)
	{
		mini->charge = 1; // For execution once
		mini->parent = 1; // tracking parent or child
		mini->last = 1; // tracking last comand for exit code
		redir_and_exec(mini, token); // redirection and execution
		reset_std(mini); // restore std as just now we backed it up before
		close_fds(mini); // close all fds
		reset_fds(mini); // setting all to unused
		waitpid(-1, &status, 0); // wait for the child process to finish
		status = WEXITSTATUS(status);  // storing chidl exist code
		mini->ret = ternary_int((mini->last == 0), status, mini->ret); // if lasat command then store the exit code if not then keep the previous one
		if (mini->parent == 0) // if in chidl thne exit
		{
			free_token(mini->start);
			exit(mini->ret); // exit with the code
		}
		mini->no_exec = 0; // resetting
		token = next_cmd(token, SKIP); // get the next command
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	(void)argc;
	(void)argv;
	(void)env;
	mini.in = dup(STDIN); // For resetting stdin at reset_std
	mini.out = dup(STDOUT);
	mini.exit = 0;  // when to exit
	mini.ret = 0;  // return status
	mini.no_exec = 0; // can exec
	reset_fds(&mini);  // reset fds to -1 to mark as unsued
	init_env(&mini, env); // Convert the env array into a linked list
	init_secret_env(&mini, env); // init secret for export with no args
	increment_shell(mini.env); // increment SHLVL
	while (mini.exit == 0) // See if need ti exit or not
	{
		sig_init(&mini); // resetting it to 0
		parse(&mini); // Parsing and getting tokens
		if (mini.start != NULL && check_line(&mini, mini.start)) // check if tokens are valid
			minishell(&mini);
		free_token(mini.start);
	}
	free_env(mini.env);
	free_env(mini.secret_env);
	return (mini.ret);
}
