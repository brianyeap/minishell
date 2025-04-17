/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:15:49 by brian             #+#    #+#             */
/*   Updated: 2025/04/17 16:43:17 by brian            ###   ########.fr       */
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

// handles ' " and '\' escaped chars
void	fill_token(char *line, int *i, t_token *token)
{
	int		j;
	char	c; // tracking quote

	j = 0;
	c = ' ';
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
			c = line[(*i)++]; // set to the quote
		else if (c != ' ' && line[*i] == c)  // close quote
		{
			c = ' ';
			(*i)++;
		}
		else if (line[*i] == '\\' && (*i)++) // handles escaped chars
			token->str[j++] = line[(*i)++]; // copy the next
		else
			token->str[j++] = line[(*i)++]; // normal cahr
	}
	token->str[j] = '\0';
}

void	error_and_exit(t_mini *mini)
{
	ft_putendl_fd("exit", STDERR);
	mini->exit = 1;
}