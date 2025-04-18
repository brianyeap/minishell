/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:15:49 by brian             #+#    #+#             */
/*   Updated: 2025/04/16 19:52:53 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	output_emoji(int ret)
{
	if (ret)
		ft_putstr_fd("🤬 ", STDERR);
	else
		ft_putstr_fd("😎 ", STDERR);
}

int	mini_ret(int cond, int true_val, int false_val)
{
	if (cond)
		return (true_val);
	else
		return (false_val);
}

void	fill_token(char *line, int *i, t_token *token)
{
	int		j;
	char	c;

	j = 0;
	c = ' ';
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
			c = line[(*i)++];
		else if (c != ' ' && line[*i] == c)
		{
			c = ' ';
			(*i)++;
		}
		else if (line[*i] == '\\' && (*i)++)
			token->str[j++] = line[(*i)++];
		else
			token->str[j++] = line[(*i)++];
	}
	token->str[j] = '\0';
}

void	error_and_quit(t_mini *mini)
{
	ft_putendl_fd("exit", STDERR);
	mini->exit = 1;
}
