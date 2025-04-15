/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 23:36:18 by brian             #+#    #+#             */
/*   Updated: 2025/04/16 03:12:08 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get the return value length if 42, output 2
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
	if (arg[pos] == '?') // Handle special case for `$?` (exit status)
		return (ret_size(ret));
	if (ft_isdigit(arg[pos])) // if it's a digit means invalid
		return (0);
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFF_SIZE) // get var name
	{
		var_name[i] = arg[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = get_env_value(var_name, env); // value
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
		if (arg[i] == EXPANSION) // handle var expansion '$'
		{
			i++;
			if ((arg[i] == '\0' || ft_isalnum(arg[i]) == 0) && arg[i] != '?')
				size++; // if not a var, just treat $ as a literall $
			else
				size += get_var_len(arg, i, env, ret); // add the path lengrh 
			if (ft_isdigit(arg[i]) == 0)  // if not digit skip var
			{
				while (arg[i + 1] && is_env_char(arg[i]))
					i++;
			}
			else
				size--; // decrement if invalid
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
		var_value = ft_itoa(ret); // convert return code to string
		return (var_value);
	}
	if (ft_isdigit(arg[pos])) // if digit means invalid
		return (NULL);
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFF_SIZE) // get var name
	{
		var_name[i] = arg[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = get_env_value(var_name, env);
	return (var_value);
}
