/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:52:31 by brian             #+#    #+#             */
/*   Updated: 2025/05/03 01:12:55 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*next_cmd(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != CMD)
	{
		token = token->next;
		if (token && token->type == CMD && token->prev->type < PIPE)
			token = token->next;
	}
	return (token);
}

t_token	*prev_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->prev;
	while (token && token->type < TRUNC)
		token = token->prev;
	return (token);
}

t_token	*next_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type < TRUNC)
		token = token->next;
	return (token);
}

static void	next_alloc_increment(int *j, int *len)
{
	(*j)++;
	(*len)++;
}

int	next_alloc(char *line, int *i)
{
	int		len;
	int		j;
	char	c;

	len = 0;
	j = 0;
	c = ' ';
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '"'))
			c = line[*i + j++];
		else if (c != ' ' && line[*i + j] == c)
		{
			c = ' ';
			j++;
		}
		else if (line[*i + j] == '\\' && c != '\'')
		{
			if (line[*i + ++j])
				next_alloc_increment(&j, &len);
		}
		else
			next_alloc_increment(&j, &len);
	}
	return (len + 1);
}
