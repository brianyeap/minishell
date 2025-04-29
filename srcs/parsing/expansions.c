/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 23:25:34 by brian             #+#    #+#             */
/*   Updated: 2025/04/30 00:01:12 by brian            ###   ########.fr       */
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

static void	insert_var(t_expansions *ex, char *arg, t_env *env, int ret)
{
	char	*env_value;

	env_value = get_var_value(arg, ex->j, env, ret); // gettign the value
	if (env_value)
		ex->i += varlcpy(ex->new_arg, env_value, ex->i); // copy the data over
	else
		ex->i += 0;
	ft_memdel(env_value);
	if (arg[ex->j] == '?')
		ex->j++; // skip it
	if (ft_isdigit(arg[ex->j]) == 0 && arg[ex->j - 1] != '?')
	{
		while (is_env_char(arg[ex->j]) == 1)
			ex->j++; // skip over the expanded var name
	}
	else
	{
		if (arg[ex->j - 1] != '?')
			ex->j++; 	// skip over single digit var like $1
	}
}

char	*expansions(char *arg, t_env *env, int ret)
{
	t_expansions	ex;
	int				new_arg_len;

	new_arg_len = arg_alloc_len(arg, env, ret); // getting the size of the new arg len
	ex.new_arg = malloc(sizeof(char) * new_arg_len + 1);
	if (!ex.new_arg)
		return (NULL);
	ex.i = 0; // output string index
	ex.j = 0; // input string index
	while (ex.i < new_arg_len && arg[ex.j])
	{
		while (arg[ex.j] == EXPANSION) // if $ is detected
		{
			ex.j++; // skip the $ sign
			if ((arg[ex.j] == '\0' || ft_isalnum(arg[ex.j]) == 0)
				&& arg[ex.j] != '?')  // if not the end and is not num and not ?
				ex.new_arg[ex.i++] = '$'; // treat it as a literal $
			else
				insert_var(&ex, arg, env, ret); // insert the variable
		}
		ex.new_arg[ex.i++] = arg[ex.j++]; // / copy the char over
	}
	ex.new_arg[ex.i] = '\0';
	return (ex.new_arg);
}
