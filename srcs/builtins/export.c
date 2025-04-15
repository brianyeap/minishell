/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:19:07 by brian             #+#    #+#             */
/*   Updated: 2025/04/15 19:08:54 by brian            ###   ########.fr       */
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

// add new/update env
int	env_add(const char *value, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	if (env && env->value == NULL) //updates with new value
	{
		env->value = ft_strdup(value);
		return (SUCCESS);
	}
	// create new env and add it to the end of the list
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

// extracts the key
char	*get_env_key(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// check if alr in env
int	is_in_env(t_env *env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	get_env_key(var_name, args);
	while (env && env->next)
	{
		get_env_key(env_name, env->value); // Extract the key from the env
		if (ft_strcmp(var_name, env_name) == 0) // compare keys
		{
			ft_memdel(env->value);
			env->value = ft_strdup(args); // Update the value
			return (1);
		}
		env = env->next; // Move to the next env
	}
	return (SUCCESS); // not in env
}

int	ft_export(char **args, t_env *env, t_env *secret)
{
	int		new_env;
	int		error_ret;

	new_env = 0;
	if (!args[1]) // if no arg provided print 
	{
		print_sorted_env(secret);
		return (SUCCESS);
	}
	else
	{
		error_ret = is_valid_env(args[1]); // validate arg
		if (args[1][0] == '=') // if first char is '='
			error_ret = -3;
		if (error_ret <= 0)
			return (print_error(error_ret, args[1]));
		new_env = choose_new_env(error_ret, env, args[1]);
		if (new_env == 0) // if it's new var
		{
			if (error_ret == 1)
				env_add(args[1], env); // add to env
			env_add(args[1], secret); // add to secret env
		}
	}
	return (SUCCESS);
}
