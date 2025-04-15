/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:41:14 by brian             #+#    #+#             */
/*   Updated: 2025/04/16 04:21:28 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir(t_mini *mini, t_token *token, int type)
{
	ft_close(mini->fdout); // close current output fd
	if (type == TRUNC) // handle > (truncate)
		mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else // handle >> (apend)
		mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (mini->fdout == -1) // if error
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		mini->ret = 1;
		mini->no_exec = 1;
		return ;
	}
	dup2(mini->fdout, STDOUT); // redirect  STDOUT to the file
}

// same thing
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

	pipe(pipefd);
	pid = fork(); // child
	if (pid == 0) // child
	{
		ft_close(pipefd[1]); // close write end
		dup2(pipefd[0], STDIN); // direct STDIN to read end
		mini->pipin = pipefd[0]; // save the read end 
		mini->pid = -1; // reset PID
		mini->parent = 0; // mark as child
		mini->no_exec = 0; // allow exec
		return (2); // return 2 for child
	}
	else
	{
		ft_close(pipefd[0]); // clsoe the read end
		dup2(pipefd[1], STDOUT); // direct STDOUt to the write end
		mini->pipout = pipefd[1]; // save the write end
		mini->pid = pid; // save PID
		mini->last = 0; // mark as not last process
		return (1); // return for parent
	}
}
