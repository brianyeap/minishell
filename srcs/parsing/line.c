/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:46:45 by brian             #+#    #+#             */
/*   Updated: 2025/04/09 23:14:05 by brian            ###   ########.fr       */
/*                                         export                                    */
/* ************************************************************************** */

#include "minishell.h"

char *space_alloc(char *line)
{
	char *new;
	int count;
	int i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (is_seperator(line, i))
			count++;
		i++;
	}
	if (!(new = malloc(sizeof(char) * (i + 2 * count + 1))))
		return (NULL);
	return (new);
}

char *space_line(char *line)
{
	char *new;
	int i;
	int j;

	i = 0;
	j = 0;
	new = space_alloc(line);
	while (new && line[i])
	{
		if (quotes(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\') // must ' and is $ and not escaped
			new[j++] = (char)(-line[i++]);
		else if (quotes(line, i) == 0 && is_seperator(line, i))
		{ // add spaces around seperator
			new[j++] = ' ';
			new[j++] = line[i++];
			if (quotes(line, i) == 0 && line[i] == '>')
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else // copy regular char
			new[j++] = line[i++];
	}
	new[j] = '\0';
	ft_memdel(line);
	return (new);
}

// Check for unmatched quotes
int quote_check(t_mini *mini, char **line)
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
	t_token	*token;

	signal(SIGINT, &sig_int); // ctrl + c
	signal(SIGQUIT, &sig_quit); // ctrl + "\"
	mini->ret ? ft_putstr_fd("🤬 ", STDERR) : ft_putstr_fd("😎 ", STDERR);
	ft_putstr_fd("\033[0;36m\033[1mminishell ▸ \033[0m", STDERR);
	if (get_next_line(0, &line) == -2 && (mini->exit = 1))
		ft_putendl_fd("exit", STDERR);
	mini->ret = (g_sig.sigint == 1) ? g_sig.exit_status : mini->ret;
	if (quote_check(mini, &line))
		return ;
	line = space_line(line);
	if (line && line[0] == '$')
		line[0] = (char)(-line[0]);
	mini->start = get_tokens(line);
	ft_memdel(line);
	squish_args(mini);
	token = mini->start;
	while (token)
	{
		if (is_type(token, ARG))
			type_arg(token, 0);
		token = token->next;
	}
}
