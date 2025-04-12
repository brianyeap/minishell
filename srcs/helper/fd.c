/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:58:44 by brian             #+#    #+#             */
/*   Updated: 2025/04/12 04:56:42 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// make sure it is unused
void	reset_fds(t_mini *mini)
{
	mini->fdin = -1;
	mini->fdout = -1;
	mini->pipin = -1;
	mini->pipout = -1;
	mini->pid = -1;
}

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

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}