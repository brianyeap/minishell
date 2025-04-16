/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:11:20 by brian             #+#    #+#             */
/*   Updated: 2025/04/16 19:26:03 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// lol i did this to save space
static inline t_token	*s(t_token *cond, t_token *if_t, t_token *if_f)
{
	if (cond)
		return (if_t);
	else
		return (if_f);
}

// setting arg type
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


// ensure that args (file.txt) are linked to the right redirection
void	squish_args(t_mini *mini)
{
	t_token	*token;
	t_token	*prev;

	token = mini->start;
	while (token)  // go thorugh the tokens
	{
		prev = prev_sep(token, NOSKIP); // find the prev sep
		if (is_type(token, ARG) && is_types(prev, "TAI")) //make sure is ARG and prev is TAI
		{
			while (is_last_valid_arg(prev) == 0) // ensure is valid
				prev = prev->prev;
			// unlink arg E.G File.txt
			token->prev->next = token->next;
			if (token->next) // if ther is next
				token->next->prev = token->prev; // link next to prev
			//  attach current (arg) to prev
			token->prev = prev;
			token->next = s(prev, prev->next, mini->start); // Set the next base on the redirection 
			// Update the links for the redirection token
			prev->next->prev = token; // Link the redirection next back to the arg
			prev->next = s(mini->start->prev, prev->next, token); // Link the redirection to the current token
			// Update the start of the token list if necessary
			mini->start = s(mini->start->prev, mini->start->prev, mini->start);
		}
		token = token->next;
	}
}

// create new token and allocate memory eg "echo hello > file.txt" is echo
t_token	*next_token(char *line, int *i)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = malloc(sizeof(char) * next_alloc(line, i));
	if (!token->str)
		return (NULL);
	fill_token(line, i, token);
	return (token);
}

// tokenize input turning all into tokens
t_token	*get_tokens(char *line)
{
	t_token	*prev;
	t_token	*next;
	int		i;
	int		sep;

	prev = NULL;
	next = NULL;
	i = 0;
	ft_skip_is_space(line, &i);
	while (line[i])
	{
		sep = ignore_sep(line, i);
		next = next_token(line, &i); // vreate new token
		next->prev = prev; // link the new token
		if (prev)
			prev->next = next; // link to the new token
		prev = next; // update the pointer
		type_arg(next, sep); // set type for the sep
		ft_skip_is_space(line, &i); // skips spaced inbetweem tokens
	}
	if (next)
		next->next = NULL; // set the last to NULL
	while (next && next->prev)
		next = next->prev; // move to the start
	return (next);
}
