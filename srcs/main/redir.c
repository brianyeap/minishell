/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:41:14 by brian             #+#    #+#             */
/*   Updated: 2025/04/25 05:03:13 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir(t_mini *mini, t_token *token, int type)
{
	ft_close(mini->fdout); // close the previous fdout
	if (type == TRUNC)
		mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU); // S_IRWXU i 777 permission
	else
		mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (mini->fdout == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		mini->ret = 1; // exit code
		mini->no_exec = 1; // don't exec
		return ;
	}
	dup2(mini->fdout, STDOUT); // redirect stdout to mini->fdout
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
	dup2(mini->fdin, STDIN);
}

int	minipipe(t_mini *mini)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd); // create a pipe
	pid = fork(); // fork a child process
	if (pid == 0) // in child
	{
		ft_close(pipefd[1]); // close the write end of the pipe
		dup2(pipefd[0], STDIN); // redirect stdin to read from the pipe
		mini->pipin = pipefd[0]; // save the read end of the pipe
		mini->pid = -1; // in child so no need store pid for waitpid
		mini->parent = 0; // child process
		mini->no_exec = 0;  //can exec
		return (2); // 2 for child
	}
	else
	{
		ft_close(pipefd[0]);  // clos read end
		dup2(pipefd[1], STDOUT); // redirect stdout to write to the pipe
		mini->pipout = pipefd[1]; // save the write end of the pipe
		mini->pid = pid; // store the pid for waitpid
		mini->last = 0; // not the last command, cause paernt writting into a pipe means there is more to come
		return (1);  // 1 for parent
	}
}
