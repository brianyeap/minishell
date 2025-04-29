/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:43:04 by brian             #+#    #+#             */
/*   Updated: 2025/04/26 21:59:11 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_not_digit(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

// bacially atoi
static int	get_lvl(const char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	ft_skip_is_space(str, &i);
	if (is_not_digit(str))
		return (0);
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
	return (num * sign);
}

int	increment_shell_level(char *val)
{
	int		shell_level;

	shell_level = get_lvl(val) + 1;
	ft_memdel(val);
	return (shell_level);
}

void	increment_shell(t_env *env)
{
	int		shell_level;
	char	env_name[BUFF_SIZE];
	char	*shlvl;
	char	*shell_level_value;

	shell_level_value = get_env_value("SHLVL", env);
	if (ft_strcmp(shell_level_value, "") == 0) // if not exist
	{
		ft_memdel(shell_level_value);
		return ;
	}
	shell_level = increment_shell_level(shell_level_value);
	while (env && env->next)
	{
		get_env_key(env_name, env->value);
		if (ft_strcmp("SHLVL", env_name) == 0)
		{
			ft_memdel(env->value);
			shlvl = ft_itoa(shell_level);
			env->value = ft_strjoin("SHLVL=", shlvl);
			ft_memdel(shlvl);
			return ;
		}
		env = env->next;
	}
}
