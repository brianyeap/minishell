/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:46:10 by brian             #+#    #+#             */
/*   Updated: 2024/06/11 19:08:29 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	my_strlen(char const *str)
{
	size_t	i;

	i = 0;
	while (str [i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*mem;
	int		i;
	int		j;

	i = 0;
	j = 0;
	mem = malloc((my_strlen(s1) + my_strlen(s2)) * sizeof(char) + 1);
	if (!mem)
		return (NULL);
	while (s1[i])
	{
		mem[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		mem[i + j] = s2[j];
		j++;
	}
	mem[i + j] = '\0';
	return (mem);
}
