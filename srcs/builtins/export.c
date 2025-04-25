/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:19:07 by brian             #+#    #+#             */
/*   Updated: 2025/04/25 17:20:14 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error(int error, const char *arg)
{
	int		i;

	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", STDERR);
	else if (error == 0 || error == -3)
		ft_putstr_fd("export: not a valid identifier: ", STDERR);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(STDERR, &arg[i], 1);
		i++;
	}
	write(STDERR, "\n", 1);
	return (ERROR);
}

int	env_add(const char *value, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	if (env && env->value == NULL)
	{
		env->value = ft_strdup(value);
		return (SUCCESS);
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (-1);
	new->value = ft_strdup(value);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (SUCCESS);
}

char	*get_env_key(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE) // If exist and not = adn len is less than buffSize
	{
		dest[i] = src[i]; 		// copy the name
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// return 1 if exist/updates value, 0 if not exist
int	is_in_env(t_env *env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	get_env_key(var_name, args);
	while (env)
	{
		get_env_key(env_name, env->value);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			ft_memdel(env->value);
			env->value = ft_strdup(args);
			return (1);
		}
		env = env->next;
	}
	return (SUCCESS);
}

// Diffrence between env and secret is that secret is print when doing export with no args
// it is also sorted and can out put env with no value
int	ft_export(char **args, t_env *env, t_env *secret)
{
	int		new_env;
	int		error_ret;

	new_env = 0;
	if (!args[1])
	{
		print_sorted_env(secret);
		return (SUCCESS);
	}
	else
	{
		error_ret = is_valid_env(args[1]); // -1 invalid char, 0 starts witn digit, 2 valid var name but no addignment, 1= valid
		if (args[1][0] == '=')
			error_ret = -3;
		if (error_ret <= 0)
			return (print_error(error_ret, args[1]));
		new_env = choose_new_env(error_ret, env, args[1]);  // 1 for exist and 0 for not
		if (new_env == 0)
		{
			if (error_ret == 1)  // if valid
				env_add(args[1], env);
			env_add(args[1], secret); // incase no value is provided, we will add to secret
		}
	}
	return (SUCCESS);
}
