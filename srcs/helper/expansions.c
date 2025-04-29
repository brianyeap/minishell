/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 23:36:18 by brian             #+#    #+#             */
/*   Updated: 2025/04/27 02:45:20 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ret_size(int ret)
{
	char	*tmp;
	int		ret_len;

	tmp = ft_itoa(ret);
	ret_len = ft_strlen(tmp);
	ft_memdel(tmp);
	return (ret_len);
}

int	get_var_len(const char *arg, int pos, t_env *env, int ret)
{
	char	var_name[BUFF_SIZE];
	char	*var_value;
	int		i;

	i = 0;
	if (arg[pos] == '?')  // if it is ? then return the size of ret (127 is 3 char)
		return (ret_size(ret));
	if (ft_isdigit(arg[pos])) // var can't start with a digit
		return (0);
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFF_SIZE) // if exist and var_name is valif and is lesser than buff size
	{
		var_name[i] = arg[pos]; // copy
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = get_env_value(var_name, env); // get env value
	i = ft_strlen(var_value);
	ft_memdel(var_value);
	return (i);
}

int	arg_alloc_len(const char *arg, t_env *env, int ret)
{
	int		i;
	int		size;

	i = -1;
	size = 0;
	while (arg[++i])
	{
		if (arg[i] == EXPANSION) // if $ is detected as EXPANSION is -36
		{
			i++;  // Skip over the $
			if ((arg[i] == '\0' || ft_isalnum(arg[i]) == 0) && arg[i] != '?') // not end or not alnum and not ?
				size++; // skip it and treat it as a literal char
			else
				size += get_var_len(arg, i, env, ret); // treat it as a variable
			if (ft_isdigit(arg[i]) == 0)
			{
				while (arg[i + 1] && is_env_char(arg[i])) // if there is next and current is valid var name skip through
					i++;
			}
			else // invalid var name like $1
				size--;  // minus it cause not valid and won't be included at the end
		}
		size++;
	}
	return (size);
}

char	*get_var_value(const char *arg, int pos, t_env *env, int ret)
{
	char	var_name[BUFF_SIZE];
	char	*var_value;
	int		i;

	i = 0;
	if (arg[pos] == '?')
	{
		var_value = ft_itoa(ret);
		return (var_value);  // return the ret value
	}
	if (ft_isdigit(arg[pos])) // can't start with a digit
		return (NULL);
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFF_SIZE) /// if all okay
	{
		var_name[i] = arg[pos]; // vopy var name
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = get_env_value(var_name, env); // ge the value
	return (var_value);
}
