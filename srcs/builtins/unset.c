/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:57:35 by brian             #+#    #+#             */
/*   Updated: 2025/04/25 19:15:04 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	inline t_env	*choose_env(t_env *candidate, t_env *fallback)
{
	if (candidate)
		return (candidate);
	else
		return (fallback);
}

// get env name size
static size_t	env_size(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void	free_node(t_mini *mini, t_env *env)
{
	if (mini->env == env && env->next == NULL)
	{
		ft_memdel(mini->env->value);
		mini->env->value = NULL;
		mini->env->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

int	ft_unset(char **a, t_mini *mini)
{
	t_env	*env;
	t_env	*tmp;

	env = mini->env;
	if (!(a[1])) // if no arg
		return (SUCCESS);
	if (ft_strncmp(a[1], env->value, env_size(env->value)) == 0) // handles if it is the first node
	{
		mini->env = choose_env(env->next, mini->env);
		free_node(mini, env);
		return (SUCCESS); // this already unset he first env
	}
	while (env && env->next)
	{
		// Using next next so we can free the next one and join next next to current
		if (ft_strncmp(a[1], env->next->value, env_size(env->next->value)) == 0)
		{
			tmp = env->next->next;
			free_node(mini, env->next);
			env->next = tmp;
			return (SUCCESS);
		}
		env = env->next;
	}
	return (SUCCESS);
}
