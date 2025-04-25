/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 23:24:40 by brian             #+#    #+#             */
/*   Updated: 2025/04/25 18:11:25 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_valid_tokens(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	return (i);
}

// Turn into array for execve
char	**cmd_tab(t_token *start)
{
	t_token	*token;
	char	**tab;
	int		i;

	if (!start)
		return (NULL); // if no command
	token = start->next;  // Skip the first token, will be added later
	i = count_valid_tokens(token) + 2;
	tab = malloc(sizeof(char *) * i);
	if (!tab)
		return (NULL);
	token = start->next; // restting it back without the firdt one
	tab[0] = start->str; // first token is the command
	i = 1;
	while (token && token->type < TRUNC)
	{
		tab[i++] = token->str;
		token = token->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	exec_cmd(t_mini *mini, t_token *token)
{
	char	**cmd;
	int		i;

	if (mini->charge == 0) // return if charge is not 1
		return ;
	cmd = cmd_tab(token); // Turn into array for execve
	i = 0;
	while (cmd && cmd[i])
	{
		cmd[i] = expansions(cmd[i], mini->env, mini->ret); // expand the $
		i++;
	}
	if (cmd && ft_strcmp(cmd[0], "exit") == 0 && has_pipe(token) == 0)
		mini_exit(mini, cmd); // only exit if exit is typed on it's own and not in a pipe
	else if (cmd && is_builtin(cmd[0]))
		mini->ret = exec_builtin(cmd, mini);  // if it is a builtin
	else if (cmd)
		mini->ret = exec_bin(cmd, mini->env, mini);
	free_tab(cmd);
	ft_close(mini->pipin);
	ft_close(mini->pipout);
	mini->pipin = -1;
	mini->pipout = -1;
	mini->charge = 0;
}
