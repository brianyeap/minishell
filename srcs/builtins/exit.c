/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 00:28:27 by brian             #+#    #+#             */
/*   Updated: 2025/04/15 18:33:39 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_exit(t_mini *mini, char **cmd)
{
	mini->exit = 1;
	ft_putstr_fd("exit ", STDERR);
	if (cmd[1])
		ft_putendl_fd("❌", STDERR);
	else
		ft_putendl_fd("✅", STDERR);
	if (cmd[1] && cmd[2]) // If too many args
	{
		mini->ret = 1;
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
	}
	else if (cmd[1] && ft_strisnum(cmd[1]) == 0) //  Handle Non-Numeric Argument
	{
		mini->ret = 255;
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
	}
	else if (cmd[1]) // If a valid convert to int
		mini->ret = ft_atoi(cmd[1]);
	else
		mini->ret = 0;
}
