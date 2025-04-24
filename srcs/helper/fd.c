/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:58:44 by brian             #+#    #+#             */
/*   Updated: 2025/04/25 05:38:37 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_fds(t_mini *mini)
{
	mini->fdin = -1;  // input redirection file discriptor
	mini->fdout = -1; // output redirection file discriptor
	mini->pipin = -1; // pipe read end
	mini->pipout = -1; // pipe write end
	mini->pid = -1; // process ID
}

// resettignt the standard input and output file descriptors
void	reset_std(t_mini *mini)
{
	dup2(mini->in, STDIN);
	dup2(mini->out, STDOUT);
}

void	close_fds(t_mini *mini)
{
	ft_close(mini->fdin);
	ft_close(mini->fdout);
	ft_close(mini->pipin);
	ft_close(mini->pipout);
}

void	ft_close(int fd) // only closing opened ones and skipping unopened ones
{
	if (fd > 0)
		close(fd);
}
