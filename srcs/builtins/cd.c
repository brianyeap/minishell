/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:56:03 by brian             #+#    #+#             */
/*   Updated: 2025/04/15 18:23:02 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

static char	*get_env_path(t_env *env, const char *var, size_t len)
{
	char	*oldpwd;
	int		i;
	int		j;

	while (env && env->next != NULL) // go through env list
	{
		if (ft_strncmp(env->value, var, len) == 0) // see if it matches
		{
			oldpwd = malloc(sizeof(char) * (ft_strlen(env->value) - len) + 1);
			if (!oldpwd)
				return (NULL);
			i = 0;
			j = 0;
			while (env->value[i++]) 
			{
				if (i > (int)len)
					oldpwd[j++] = env->value[i]; // Copy the value after the variable name
			}
			oldpwd[j] = '\0';
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}

static int	update_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ERROR);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (ERROR);
	if (is_in_env(env, oldpwd) == 0) // Check if `OLDPWD` exists
		env_add(oldpwd, env); // Add it if it doesn't exist
	ft_memdel(oldpwd);  // Free the allocated memory
	return (SUCCESS);
}

static int	go_to_path(int option, t_env *env)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)  // If the option is 0, go to `HOME`
	{
		update_oldpwd(env);
		env_path = get_env_path(env, "HOME", 4); // Get the `HOME` path
		if (!env_path)
			ft_putendl_fd("minishell : cd: HOME not set", STDERR);  // Print error if `HOME` is not set
		if (!env_path)
			return (ERROR);
	}
	else if (option == 1) // If the option is 1, go to `OLDPWD`
	{
		env_path = get_env_path(env, "OLDPWD", 6);
		if (!env_path)
			ft_putendl_fd("minishell : cd: OLDPWD not set", STDERR);
		if (!env_path)
			return (ERROR);
		update_oldpwd(env);
	}
	ret = chdir(env_path);  // Change to the directory
	ft_memdel(env_path);
	return (ret);
}

int	ft_cd(char **args, t_env *env)
{
	int		cd_ret;

	if (!args[1]) // If no arguments are provided, go to `HOME`
		return (go_to_path(0, env));
	if (ft_strcmp(args[1], "-") == 0)  // If the argument is "-", go to `OLDPWD`
		cd_ret = go_to_path(1, env);
	else
	{
		update_oldpwd(env); // Update `OLDPWD`
		cd_ret = chdir(args[1]);  // Change to the specified directory
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
			print_error(args);
	}
	return (cd_ret);
}
