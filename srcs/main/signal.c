/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:36:00 by brian             #+#    #+#             */
/*   Updated: 2025/04/16 05:03:26 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_mini	*get_mini_instance(t_mini *mini)
{
	static t_mini	*instance = NULL;

	if (mini != NULL)
		instance = mini; // set the instance
	return (instance); // return current instance
}

// Signal handler for SIGINT (CTRL+C)
void	sig_int(int code)
{
	t_mini	*mini;

	(void)code;
	mini = get_mini_instance(NULL); // get the instance
	if (mini->pid == 0) // if no child running
	{
		ft_putstr_fd("\b\b  ", STDERR); // clear the line
		ft_putstr_fd("\n", STDERR);  // new line
		ft_putstr_fd(RED"🤬 minishell >"RESET, STDERR); // print
		mini->exit_status = 1; // exit
	}
	else // if child runing
	{
		ft_putstr_fd("\n", STDERR); // print new line
		mini->exit_status = 130; // 130 for sigint 
	}
	mini->sigint = 1;
}

void	sig_quit(int code)
{
	t_mini	*mini;
	char	*nbr;

	mini = get_mini_instance(NULL);
	nbr = ft_itoa(code); // convert signal code to string
	if (mini->pid != 0) // if child running
	{
		ft_putstr_fd("Quit: ", STDERR);
		ft_putendl_fd(nbr, STDERR); // print signla code
		mini->exit_status = 131; // for siqquit
		mini->sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR);
	ft_memdel(nbr);
}

// reste all and set teh isnatnce
void	sig_init(t_mini *mini)
{
	get_mini_instance(mini);
	mini->sigint = 0;
	mini->sigquit = 0;
	mini->pid = 0;
	mini->exit_status = 0;
}
