/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:44:41 by brian             #+#    #+#             */
/*   Updated: 2024/06/11 19:07:44 by brian            ###   ########.fr       */
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*mem;
	size_t		i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > my_strlen(s))
		len = 0;
	else if (len > (my_strlen(s) - start))
		len = my_strlen(s) - start;
	mem = malloc(len * sizeof(char) + 1);
	if (!mem)
		return (NULL);
	while (s[start + i] && i < len)
	{
		mem[i] = s[start + i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}

// #include <stdio.h>
// int main()
// {
// 	char *str = "Hi My name Is Brian";
// 	printf("%s", ft_substr(str, 3, 2));
// 	return (0);
// }