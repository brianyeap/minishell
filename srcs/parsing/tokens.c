/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:11:20 by brian             #+#    #+#             */
/*   Updated: 2025/04/27 00:50:32 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Seperator is to check if it is ignored
// EMPTY is set becasue i neeed eveyrhting to have a type even EMPTY
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
	else if (token->prev == NULL || token->prev->type == PIPE || token->prev->type == END)
		token->type = CMD;
	else
		token->type = ARG;
}

// allocate space and fill the next token
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

// turn string into tokens 
t_token	*get_tokens(char *line)
{
	t_token	*prev;
	t_token	*next;
	int		i;
	int		sep;

	prev = NULL;
	next = NULL;
	i = 0;
	ft_skip_is_space(line, &i); // skips the initial is_spcaes
	while (line[i])
	{
		sep = ignore_sep(line, i); // igore the seperator 1 is escaped and 0 is not
		next = next_token(line, &i); // allocate space and fill the token
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next; // so we have a prev for the next
		type_arg(next, sep); // set the type of the token
		ft_skip_is_space(line, &i); // skip the is_space
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;  // going to the start to set the head
	return (next);
}
