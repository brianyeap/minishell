/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:58:19 by brian             #+#    #+#             */
/*   Updated: 2025/04/15 19:09:47 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	choose_new_env(int error_ret, t_env *env, char *arg)
{
	if (error_ret == 2)  // if it's a new var
		return (1);
	else
		return (is_in_env(env, arg)); // check if it's already in env
}
