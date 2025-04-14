/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:31:50 by brian             #+#    #+#             */
/*   Updated: 2025/04/14 17:33:06 by brian            ###   ########.fr       */
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
