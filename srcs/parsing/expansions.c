/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 23:25:34 by brian             #+#    #+#             */
/*   Updated: 2025/04/16 05:13:03 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	varlcpy(char *new_arg, const char *env_value, int pos)
{
	int		i;

	i = 0;
	while (env_value[i])
		new_arg[pos++] = env_value[i++];
	return (i);
}

// insert value of var into new arg
static void	insert_var(t_expansions *ex, char *arg, t_env *env, int ret)
{
	char	*env_value;

	env_value = get_var_value(arg, ex->j, env, ret); // get value
	if (env_value)
		ex->i += varlcpy(ex->new_arg, env_value, ex->i); // copy calue into new arg
	else
		ex->i += 0; // no value to copy
	ft_memdel(env_value);
	if (arg[ex->j] == '?') // handle the case dor $?
		ex->j++;
	if (ft_isdigit(arg[ex->j]) == 0 && arg[ex->j - 1] != '?') // if valid
	{
		while (is_env_char(arg[ex->j]) == 1)
			ex->j++;
	}
	else
	{
		if (arg[ex->j - 1] != '?')
			ex->j++;
	}
}

char	*expansions(char *arg, t_env *env, int ret)
{
	t_expansions	ex;
	int				new_arg_len;

	new_arg_len = arg_alloc_len(arg, env, ret);
	ex.new_arg = malloc(sizeof(char) * new_arg_len + 1);
	if (!ex.new_arg)
		return (NULL);
	ex.i = 0;
	ex.j = 0;
	while (ex.i < new_arg_len && arg[ex.j]) // gping through args
	{
		while (arg[ex.j] == EXPANSION)
		{
			ex.j++;
			if ((arg[ex.j] == '\0' || ft_isalnum(arg[ex.j]) == 0)
				&& arg[ex.j] != '?')
				ex.new_arg[ex.i++] = '$'; // treat $ as literal $
			else
				insert_var(&ex, arg, env, ret); // insert var
		}
		ex.new_arg[ex.i++] = arg[ex.j++]; // copy char
	}
	ex.new_arg[ex.i] = '\0';
	return (ex.new_arg);
}
