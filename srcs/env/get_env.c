/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:16:05 by brian             #+#    #+#             */
/*   Updated: 2025/04/12 05:11:26 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// checkif alphanumeric or underscore
int		is_env_char(int c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}

int		is_valid_env(const char *env)
{
	int		i;

	i = 0;
	// env var vant start with a digit
	if (ft_isdigit(env[i]) == 1)
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0)
			return (-1);
		i++;
	}
	if (env[i] != '=')
		return (2);
	return (1);
}

// claculate len
int		env_value_len(const char *env)
{
	int		i;
	int		size_name;

	size_name = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	while (env[i])
	{
		i++;
		size_name++;
	}
	return (size_name);
}

// get env key value
char	*env_value(char *env)
{
	int		i;
	int		j;
	int		size_alloc;
	char	*env_value;

	// get size of env value
	size_alloc = env_value_len(env) + 1;
	if (!(env_value = malloc(sizeof(char) * size_alloc)))
		return (NULL);
	i = 0;
	// skip to value
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	j = 0;
	// copy value
	while (env[i])
		env_value[j++] = env[i++];
	env_value[j] = '\0';
	return (env_value);
}

char	*get_env_value(char *arg, t_env *env)
{
	char	env_key_name[BUFF_SIZE];
	char	*env_val;

	env_val = ft_strdup("");
	while (env && env->value)
	{
		get_env_key(env_key_name, env->value); // set key
		if (ft_strcmp(arg, env_key_name) == 0)
		{
			ft_memdel(env_val);
			env_val = env_value(env->value);
			return (env_val);
		}
		env = env->next;
	}
	return (env_val);
}