/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:15:49 by brian             #+#    #+#             */
/*   Updated: 2025/05/03 21:17:47 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	token->quoted = 0;
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
			c = line[(*i)++];
		else if (c != ' ' && line[*i] == c)
		{
			(*i)++;
			c = ' ';
			token->quoted = 1;
		}
		else if (line[*i] == '\\' && c != '\'')
		{
			(*i)++;
			if (line[*i])
				token->str[j++] = line[(*i)++];
		}
		else
			token->str[j++] = line[(*i)++];
	}
	token->str[j] = '\0';
}

void	error_and_quit(t_mini *mini)
{
	ft_putendl_fd("exit", STDERR);
	mini->exit = 1;
	mini->start = NULL;
}
