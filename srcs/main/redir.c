/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:41:14 by brian             #+#    #+#             */
/*   Updated: 2025/04/30 05:17:53 by brian            ###   ########.fr       */
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

void	mark_expansions(char *line)
{
	int i = 0;
	while (line && line[i])
	{
		if (line[i] == '$')
			line[i] = (char)EXPANSION; // usually -36
		i++;
	}
}

int	handle_heredoc(t_mini *mini, const char *delimiter, int expand)
{
	int		pipefd[2];
	char	*line;
	char	*expanded;

	pipe(pipefd);
	while (1)
	{
		line = readline("heredoc ▸ ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: heredoc delimited by end-of-file (wanted `", STDERR);
			ft_putstr_fd((char *)delimiter, STDERR);
			ft_putendl_fd("')", STDERR);
			break;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& ft_strlen(line) == ft_strlen(delimiter))
		{
			free(line);
			break;
		}
		if (expand)
		{
			mark_expansions(line);
			expanded = expansions(line, mini->env, mini->ret);
		}
		else
			expanded = ft_strdup(line);
		if (expanded)
		{
			write(pipefd[1], expanded, ft_strlen(expanded));  // write to write end
			write(pipefd[1], "\n", 1);
			free(expanded);
		}
		free(line);
	}

	close(pipefd[1]); // close write end cause we done with writting
	dup2(pipefd[0], STDIN_FILENO); // Now anything that reads from STDIN (file descriptor 0) will get data from pipefd[0].  like E.G cat
	close(pipefd[0]); // close read end since i already dup2 it and i don't need it anymore
	return (0);
}
