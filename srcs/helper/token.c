/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:52:31 by brian             #+#    #+#             */
/*   Updated: 2025/04/27 01:59:53 by brian            ###   ########.fr       */
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
			token = token->next;  // skip CMD that comes after redirection like > cat
	}
	return (token);
}

// Goes backward until it finds TRUNC and lesser
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

int	next_alloc(char *line, int *i)
{
	int		count;
	int		j;
	char	c;

	count = 0;
	j = 0;
	c = ' '; // for quotes
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' ')) // this checks if we are at the end or if there is a space but space in a quote is fine and we know that because of c
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			c = line[*i + j++]; // mark it with quotes if there is
		else if (c != ' ' && line[*i + j] == c) // this is for the end quote
		{
			count += 2;
			c = ' ';
			j++;
		}
		else
			j++;
		if (line[*i + j - 1] == '\\') // inscae it is escaped we minus it
			count++;
	}
	return (j - count + 1);
}
