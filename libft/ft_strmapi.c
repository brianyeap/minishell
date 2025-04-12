/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:31:01 by bryeap            #+#    #+#             */
/*   Updated: 2024/06/11 19:22:44 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i += 1;
	return (i);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*mem;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	mem = malloc(sizeof(char) * (my_strlen((char *)s) + 1));
	if (!mem)
		return (NULL);
	while (s[i])
	{
		mem[i] = f(i, s[i]);
		i++;
	}
	mem[i] = '\0';
	return (mem);
}
