/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:08:10 by brian             #+#    #+#             */
/*   Updated: 2025/04/17 16:43:40 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// allocate spce for line with sep spaces in mind
char	*space_alloc(char *line)
{
	char	*new;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (is_seperator(line, i))
			count++;
		i++;
	}
	new = malloc(sizeof(char) * (i + 2 * count + 1));
	if (!new)
		return (NULL);
	return (new);
}

// adds spaces for seperators
char	*space_line(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = space_alloc(line);
	while (new && line[i])
	{
		if (quotes(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\')
			new[j++] = (char)(-line[i++]); // if outside quote and not escahandle eped it is marked with - to be prossess later
		else if (quotes(line, i) == 0 && is_seperator(line, i))
		{
			new[j++] = ' '; // add space before sep
			new[j++] = line[i++]; // add sep
			if (quotes(line, i) == 0 && line[i] == '>')
				new[j++] = line[i++]; // handle >>
			new[j++] = ' '; // handle space after sep (appennd)
		}
		else
			new[j++] = line[i++]; // add normal char
	}
	new[j] = '\0';
	ft_memdel(line);
	return (new);
}

int	quote_check(t_mini *mini, char **line)
{
	if (quotes(*line, 2147483647)) // check fot unclosed quotes
	{
		ft_putendl_fd("minishell: syntax error with open quotes", STDERR);
		ft_memdel(*line);
		mini->ret = 2; // syntax error 
		mini->start = NULL; // reset token list
		return (1); // err
	}
	return (0);
}

void	parse(t_mini *mini)
{
	char	*line;
	t_token	*token;

	signal(SIGINT, &sig_int); // ctrl c
	signal(SIGQUIT, &sig_quit); // ctrl '\'
	output_emoji(mini->ret);
	line = readline("minishell ▸ ");
	if (!line)
		error_and_exit(mini);
	if (*line)
		add_history(line);
	mini->ret = mini_ret((mini->sigint == 1), mini->exit_status, mini->ret);
	if (quote_check(mini, &line)) // check for unclosed quotes
		return ;
	line = space_line(line); // add spaces for seps
	if (line && line[0] == '$')
		line[0] = (char)(-line[0]); // marking it - to be processed later (36 ascii is $)
	mini->start = get_tokens(line); // tokenize the line
	free(line);
	squish_args(mini); // combine args
	token = mini->start;
	while (token)
	{
		if (is_type(token, ARG))
			type_arg(token, 0); // process args setting types
		token = token->next;
	}
}
