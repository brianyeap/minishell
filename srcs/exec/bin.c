/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:08:41 by brian             #+#    #+#             */
/*   Updated: 2025/04/16 02:36:27 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY); // open path as file
	folder = opendir(path);  // open path as directory
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", STDERR);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", STDERR);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", STDERR);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = UNKNOWN_COMMAND;
	else
		ret = IS_DIRECTORY;
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (ret);
}

int	magic_box(char *path, char **args, t_env *env, t_mini *mini)
{
	char	**env_array;
	char	*ptr;
	int		ret;

	ret = SUCCESS;
	mini->pid = fork(); // Create child process
	if (mini->pid == 0) // inside child process
	{
		ptr = env_to_str(env);  // Convert the env to string
		env_array = ft_split(ptr, '\n'); // Split str into array
		ft_memdel(ptr);
		if (ft_strchr(path, '/') != NULL)
			execve(path, args, env_array); // exc coomand 
		ret = error_message(path);
		free_tab(env_array);
		free_token(mini->start);
		exit(ret);
	}
	else
		waitpid(mini->pid, &ret, 0); // wait f child
	if (mini->sigint == 1 || mini->sigquit == 1)
		return (mini->exit_status);
	ret = normalize_exit_code(ret);
	return (ret);
}

char	*path_join(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	ft_memdel(tmp);
	return (path);
}

char	*check_dir(char *bin, char *command)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	item = readdir(folder);
	while (item != NULL)
	{
		if (ft_strcmp(item->d_name, command) == 0) // check if cmd matches
			path = path_join(bin, item->d_name);
		item = readdir(folder);
	}
	closedir(folder); // close the dir
	return (path);
}

int	exec_bin(char **args, t_env *env, t_mini *mini)
{
	int		i;
	char	**bin;
	char	*path;
	int		ret;

	i = 0;
	ret = UNKNOWN_COMMAND;
	while (env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
		env = env->next; // find the path var in env 
	if (env == NULL || env->next == NULL)
		return (magic_box(args[0], args, env, mini));  // exc if no path, bascically yolo and just try
	bin = ft_split(env->value, ':'); // split the path into dirs
	if (!args[0] && !bin[0])
		return (ERROR);
	i = 1;
	path = check_dir(bin[0] + 5, args[0]); // check the first dir but remove the PATH= part
	while (args[0] && bin[i] && path == NULL) // check the rest of the dirs
		path = check_dir(bin[i++], args[0]);
	if (path != NULL)
		ret = magic_box(path, args, env, mini); // exc	if fouind
	else
		ret = magic_box(args[0], args, env, mini); // exc if not found
	free_tab(bin);
	ft_memdel(path);
	return (ret);
}
