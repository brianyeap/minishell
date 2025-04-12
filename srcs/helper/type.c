/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:55:14 by brian             #+#    #+#             */
/*   Updated: 2025/04/06 00:26:18 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

int		is_types(t_token *token, char *types)
{
	if (ft_strchr(types, ' ') && is_type(token, EMPTY))
		return (1);
	else if (ft_strchr(types, 'X') && is_type(token, CMD))
		return (1);
	else if (ft_strchr(types, 'x') && is_type(token, ARG))
		return (1);
	else if (ft_strchr(types, 'T') && is_type(token, TRUNC))
		return (1);
	else if (ft_strchr(types, 'A') && is_type(token, APPEND))
		return (1);
	else if (ft_strchr(types, 'I') && is_type(token, INPUT))
		return (1);
	else if (ft_strchr(types, 'P') && is_type(token, PIPE))
		return (1);
	else if (ft_strchr(types, 'E') && is_type(token, END))
		return (1);
	return (0);
}

int		has_pipe(t_token *token)
{
	while (token && is_type(token, END) == 0)
	{
		if (is_type(token, PIPE))
			return (1);
		token = token->next;
	}
	return (0);
}