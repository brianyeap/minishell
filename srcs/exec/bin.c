/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:08:41 by brian             #+#    #+#             */
/*   Updated: 2025/04/25 20:36:29 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY); // check if writable, -1 menas couldn't open
	folder = opendir(path);  // if success means it's a dir
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
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL)) // doesnt contain slash, open file and folder failed
		ret = UNKNOWN_COMMAND; // 127
	else
		ret = IS_DIRECTORY; // 126
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
	mini->pid = fork();
	if (mini->pid == 0) // in the child process
	{
		ptr = env_to_str(env); // turn linked list into string seperated by \n
		env_array = ft_split(ptr, '\n'); // split by \n
		ft_memdel(ptr);
		if (ft_strchr(path, '/') != NULL)
			execve(path, args, env_array); // means that its is a path so we just run it
		ret = error_message(path); // only triggers if failed casue execve if succes wouldn't come here
		free_tab(env_array);
		free_token(mini->start);
		exit(ret); // exit code will be encoded (*256) can get from aprent at wait pid
	}
	else /// in the parent process
		waitpid(mini->pid, &ret, 0); // wait for child and storing ret (32256 / 32512)
	if (mini->sigint == 1 || mini->sigquit == 1) // if ctrl + c or '\'
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
	folder = opendir(bin); // open the dir
	if (!folder)
		return (NULL);
	item = readdir(folder); // read throught the dir like E.G ["ls", "cat"]
	while (item != NULL)
	{
		if (ft_strcmp(item->d_name, command) == 0) // check if it matches the comand
			path = path_join(bin, item->d_name); // join the path
		item = readdir(folder);
	}
	closedir(folder);
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
	while (env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0) // find the PATH
		env = env->next;
	if (env == NULL || env->next == NULL)
		return (magic_box(args[0], args, env, mini)); // if i don't find the path then just try and execute
	bin = ft_split(env->value, ':'); // split the PATH into an array
	if (!args[0] && !bin[0]) // if no command or failed to split
		return (ERROR);
	i = 1;
	path = check_dir(bin[0] + 5, args[0]); // we do this becasue we want to skip the PATH= part
	while (args[0] && bin[i] && path == NULL)
		path = check_dir(bin[i++], args[0]);  // go theought the list to find the path
	if (path != NULL)
		ret = magic_box(path, args, env, mini); // if found execute it with the path
	else
		ret = magic_box(args[0], args, env, mini);  // if no path found then execute it directly with the command
	free_tab(bin);
	ft_memdel(path);
	return (ret);
}
