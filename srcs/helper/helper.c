/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:31:50 by brian             #+#    #+#             */
/*   Updated: 2025/05/03 01:46:22 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_or_newline(t_token *token)
{
	if (token)
		ft_putstr_fd(token->str, STDERR);
	else
		ft_putstr_fd("newline", STDERR);
}

void	arg_alloc_len_helper(const char *arg, int *i, int *size)
{
	if (ft_isdigit(arg[*i]) == 0)
	{
		while (arg[*i + 1] && is_env_char(arg[*i]))
			(*i)++;
	}
	else
		(*size)--;
}
