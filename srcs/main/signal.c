/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:36:00 by brian             #+#    #+#             */
/*   Updated: 2025/04/15 03:11:59 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_mini *get_mini_instance(t_mini *mini)
{
    static t_mini *instance = NULL;
    
    if (mini != NULL)
        instance = mini;
    return (instance);
}

void    sig_int(int code)
{
    t_mini *mini = get_mini_instance(NULL);
    
    (void)code;
    if (mini->pid == 0)
    {
        ft_putstr_fd("\b\b  ", STDERR);
        ft_putstr_fd("\n", STDERR);
        ft_putstr_fd(RED"🤬 minishell >"RESET, STDERR);
        mini->exit_status = 1;
    }
    else
    {
        ft_putstr_fd("\n", STDERR);
        mini->exit_status = 130;
    }
    mini->sigint = 1;
}

void    sig_quit(int code)
{
    t_mini *mini = get_mini_instance(NULL);
    char    *nbr;

    nbr = ft_itoa(code);
    if (mini->pid != 0)
    {
        ft_putstr_fd("Quit: ", STDERR);
        ft_putendl_fd(nbr, STDERR);
        mini->exit_status = 131;
        mini->sigquit = 1;
    }
    else
        ft_putstr_fd("\b\b  \b\b", STDERR);
    ft_memdel(nbr);
}

void    sig_init(t_mini *mini)
{
    get_mini_instance(mini);
    mini->sigint = 0;
    mini->sigquit = 0;
    mini->pid = 0;
    mini->exit_status = 0;
}