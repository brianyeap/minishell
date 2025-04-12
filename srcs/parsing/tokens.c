/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:11:20 by brian             #+#    #+#             */
/*   Updated: 2025/04/12 05:50:21 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	type_arg(t_token *token, int separator)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == 0 && separator == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0 && separator == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<") == 0 && separator == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "|") == 0 && separator == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == 0 && separator == 0)
		token->type = END;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

void	squish_args(t_mini *mini)
{
	t_token	*token;
	t_token	*prev;

	token = mini->start;
	while (token)
	{
		prev = prev_sep(token, NOSKIP); // Finds the previous separator
		if (is_type(token, ARG) && is_types(prev, "TAI")) //  TAI = TRUNC, APPEND, INPUT
		{
			while (is_last_valid_arg(prev) == 0)
				prev = prev->prev;
			token->prev->next = token->next; // rm bc aft redirect != args it's target
			if (token->next)
				token->next->prev = token->prev;
			token->prev = prev; // Setting sep as prev token for target
			token->next = (prev) ? prev->next : mini->start; // prevent disconnection
			prev->next->prev = token;
			prev->next = (mini->start->prev) ? prev->next : token; // Handle start if update
			mini->start = (mini->start->prev) ? mini->start->prev : mini->start; // make sure start points to the first token
		}
		token = token->next;
	}
}

// Gets the next token while ignoring ' ' and slash
t_token	*next_token(char *line, int *i)
{
	t_token	*token;
	int		j;
	char	c;

	j = 0;
	c = ' ';
	if (!(token = malloc(sizeof(t_token)))
	|| !(token->str = malloc(sizeof(char) * next_alloc(line, i))))
		return (NULL);
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
	return (token);
}

t_token *get_tokens(char *line)
{
	t_token *prev;
	t_token *next;
	int i;
	int sep;

	prev = NULL;
	next = NULL;
	i = 0;
	ft_skip_is_space(line, &i);
	while (line[i])
	{
		sep = ignore_sep(line, i);
		next = next_token(line, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		type_arg(next, sep);
		ft_skip_is_space(line, &i);
	}
	if (next) // set the last token to NULL
		next->next = NULL;
	while (next && next->prev)
		next = next->prev; // return head
	return (next);
}