/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:00:29 by brian             #+#    #+#             */
/*   Updated: 2025/05/05 15:53:38 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_env_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	sort_env(char **tab, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = 0;
	while (tab && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

void	print_sorted_env_helper(char *eq, char *tab)
{
	*eq = '\0';
	ft_putstr("declare -x ");
	ft_putstr(tab);
	ft_putstr("=\"");
	ft_putstr(eq + 1);
	ft_putendl("\"");
}

void	print_sorted_env(t_env *env)
{
	int		i;
	char	**tab;
	char	*str_env;
	char	*eq;

	str_env = env_to_str(env);
	tab = ft_split(str_env, '\n');
	ft_memdel(str_env);
	sort_env(tab, str_env_len(tab));
	i = 0;
	while (tab[i])
	{
		eq = ft_strchr(tab[i], '=');
		if (eq)
			print_sorted_env_helper(eq, tab[i]);
		else
		{
			ft_putstr("declare -x ");
			ft_putendl(tab[i]);
		}
		i++;
	}
	free_tab(tab);
}
