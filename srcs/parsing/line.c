/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:08:10 by brian             #+#    #+#             */
/*   Updated: 2025/04/29 23:47:44 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// This function is incase the raw input is joined tgt like "ls|cat|grep"
// It will add spaces around the sepereator so that it is easier to tokenize
char	*space_line(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0; // index for ori line
	j = 0; // index for new line
	new = space_alloc(line); // allocate space for new line
	while (new && line[i])
	{
		if (quotes(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\') // checking the $ is not inside single quotes and it is not escaped NOTE i made it so that i must be non zero
			new[j++] = (char)(-line[i++]); // marking it negative which is -36 == EXPANSION in the header file
		else if (quotes(line, i) == 0 && is_seperator(line, i)) // we are not in quotes and this cahr is a seperator
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (quotes(line, i) == 0 && (line[i] == '>' || line[i] == '<'))
				new[j++] = line[i++]; // this is for if it is a >> or <<
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	ft_memdel(line);
	return (new);
}

int	quote_check(t_mini *mini, char **line)
{
	if (quotes(*line, 2147483647))
	{
		ft_putendl_fd("minishell: syntax error with open quotes", STDERR);
		ft_memdel(*line);
		mini->ret = 2;
		mini->start = NULL;
		return (1);
	}
	return (0);
}

void	parse(t_mini *mini)
{
	char	*line;

	signal(SIGINT, &sig_int); // Ctrl + c
	signal(SIGQUIT, &sig_quit); // Ctrl + '\'
	output_emoji(mini->ret);
	line = readline("\033[0;36m\033[1mminishell ▸ \033[0m");
	if (!line)
	{
		error_and_quit(mini);
		return;
	}
	if (*line)
		add_history(line);
	mini->ret = mini_ret((mini->sigint == 1), mini->exit_status, mini->ret); // if sigint then set the exit staus
	if (quote_check(mini, &line)) // check for open quotes
		return ;
	line = space_line(line); // space line so it is easier to tokenize
	if (line && line[0] == '$')  // even thought in space line we already marked the $ but it doesnt mark the first $ becaise of the -1 check for the '\'
		line[0] = (char)(-line[0]); // marking it negative which is -36 == EXPANSION in the header file
	mini->start = get_tokens(line); // turning it into tokens
	ft_memdel(line);
}
