/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:55:03 by brian             #+#    #+#             */
/*   Updated: 2025/04/16 03:23:39 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// chec is inside quote single or double
int	quotes(char *line, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i] && i != index)
	{
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (open == 0 && line[i] == '\"')
			open = 1;
		else if (open == 0 && line[i] == '\'')
			open = 2;
		else if (open == 1 && line[i] == '\"')
			open = 0;
		else if (open == 2 && line[i] == '\'')
			open = 0;
		i++;
	}
	return (open); // 0if not inside, 1 for "", 2 for ''
}

int	is_seperator(char *line, int i)
{
	if (i > 0 && line[i - 1] == '\\' && ft_strchr("<>|;", line[i]))
		return (0);// Ignore escaped separators
	else if (ft_strchr("<>|;", line[i]) && quotes(line, i) == 0)
		return (1);// Valid separator outside quotes
	else
		return (0);
}

int	is_last_valid_arg(t_token *token)
{
	t_token	*prev;

	if (!token || is_type(token, CMD) || is_type(token, ARG))
	{
		prev = prev_sep(token, NOSKIP);
		if (!prev || is_type(prev, END) || is_type(prev, PIPE))
			return (1);
		return (0);
	}
	else
		return (0);
}

// check if it is escaped
int	ignore_sep(char *line, int i)
{
	if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == ';')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '|')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1]
		== '>' && line[i + 2] && line[i + 2] == '>')
		return (1);
	return (0);
}

int	check_line(t_mini *mini, t_token *token)
{
	while (token)
	{
		if (is_types(token, "TAI") && (!token->next
				|| is_types(token->next, "TAIPE"))) // make sure next is not empty and not TAIPE
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
			print_token_or_newline(token->next);
			ft_putendl_fd("'", STDERR);
			mini->ret = 258; // syntax error
			return (0);
		}
		if (is_types(token, "PE") && (!token->prev || !token->next
				|| is_types(token->prev, "TAIPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
			ft_putstr_fd(token->str, STDERR);
			ft_putendl_fd("'", STDERR);
			mini->ret = 258;
			return (0);
		}
		token = token->next;
	}
	return (1);
}
