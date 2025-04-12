/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryeap <bryeap@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 03:53:46 by brian             #+#    #+#             */
/*   Updated: 2024/06/14 14:45:54 by bryeap           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	my_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i += 1;
	return (i);
}

size_t	ft_strlcpy(char *des, char const *src, size_t n)
{
	size_t	i;
	size_t	src_size;

	if (!des || !src)
		return (0);
	src_size = my_strlen(src);
	i = 0;
	while (src[i])
		i++;
	i = 0;
	if (n != 0)
	{
		while (i < (n - 1) && src[i])
		{
			des[i] = src[i];
			i++;
		}
		des[i] = '\0';
	}
	return (src_size);
}

// #include <string.h>
// #include <assert.h>
// #include <stdio.h>
// int main() {
//     char src[] = "Hello, world!";
//     char dest[20];

//     // Testing ft_strlcpy
//     ft_strlcpy(dest, src, sizeof(dest));

//     printf("%s", dest);

//     return 0;
// }