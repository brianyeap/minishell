/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:52:31 by brian             #+#    #+#             */
/*   Updated: 2025/04/16 03:54:22 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*next_cmd(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != CMD) // loop until cmd
	{
		token = token->next;
		if (token && token->type == CMD && token->prev == NULL)
			; // do ntg if first token is cmd
		else if (token && token->type == CMD && token->prev->type < END)
			token = token->next; // skip invalid cmd
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

// calc len of next token with quotes escaped and sapces
int	next_alloc(char *line, int *i)
{
	int		count;
	int		j;
	char	c; // for quote tracking

	count = 0;
	j = 0;
	c = ' ';
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' ')) // stops when encounter space outside quotes
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			c = line[*i + j++]; // oopen quotes
		else if (c != ' ' && line[*i + j] == c)
		{
			count += 2; // close quoyes and count 
			c = ' ';
			j++;
		}
		else
			j++;
		if (line[*i + j - 1] == '\\')
			count--; // igore escaped char
	}
	return (j - count + 1);
}
