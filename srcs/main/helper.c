/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 02:11:41 by brian             #+#    #+#             */
/*   Updated: 2025/04/30 04:03:40 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	mark_expansions(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '$')
			line[i] = (char)EXPANSION;
		i++;
	}
}

int	handle_pipe_fail(t_mini *mini)
{
	ft_putstr_fd("minishell: ", STDERR);
	perror("pipe");
	mini->ret = 1;
	mini->no_exec = 1;
	return (-1);
}

void	heredoc_expand(t_mini *mini, char *line, int expand, int *pipefd)
{
	char	*expanded;

	if (expand)
	{
		mark_expansions(line);
		expanded = expansions(line, mini->env, mini->ret);
	}
	else
		expanded = ft_strdup(line);
	if (expanded)
	{
		write(pipefd[1], expanded, ft_strlen(expanded));
		write(pipefd[1], "\n", 1);
		free(expanded);
	}
}

int	handle_heredoc_line(char *line, char *delimiter)
{
	if (!line)
	{
		ft_putstr_fd("minishell: warning: heredoc delimited by end-of-file "
			"(wanted `", STDERR);
		ft_putstr_fd((char *)delimiter, STDERR);
		ft_putendl_fd("')", STDERR);
		ft_memdel(line);
		return (1);
	}
	if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
		&& ft_strlen(line) == ft_strlen(delimiter))
	{
		ft_memdel(line);
		return (1);
	}
	return (0);
}
