/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:41:14 by brian             #+#    #+#             */
/*   Updated: 2025/03/11 18:38:37 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir(t_mini *mini, t_token *token, int type)
{
	ft_close(mini->fdout);
	if (type == TRUNC) // Open in trunc mode
		mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU); // R.W.E
	else // Open in append mode
		mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU); // R.W.E
	if (mini->fdout == -1)
	{ // If fail to open file
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		mini->ret = 1;
		mini->no_exec = 1;
		return ;
	}
	dup2(mini->fdout, STDOUT); // Redirect stdout to file
}

void	input(t_mini *mini, t_token *token)
{
	ft_close(mini->fdin);
	mini->fdin = open(token->str, O_RDONLY, S_IRWXU);
	if (mini->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		mini->ret = 1;
		mini->no_exec = 1;
		return ;
	}
	dup2(mini->fdin, STDIN); // read from file
}

int		minipipe(t_mini *mini)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(pipefd[1]); // Close write end
		dup2(pipefd[0], STDIN); // read from pipe
		mini->pipin = pipefd[0]; // store pipe in
		mini->pid = -1; // Tracking
		mini->parent = 0; // Child
		mini->no_exec = 0; // Allowed to execute
		return (2); // Child
	}
	else
	{
		ft_close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		mini->pipout = pipefd[1]; // store pipe out
		mini->pid = pid;
		mini->last = 0;
		return (1);
	}
}