/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 03:04:45 by brian             #+#    #+#             */
/*   Updated: 2024/06/11 18:37:05 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*dest_ptr;
	size_t	i;

	i = 0;
	dest_ptr = dest;
	if ((!dest && !src) || (dest == src))
		return (dest);
	if (dest > src)
	{
		while (n--)
			((char *)dest)[n] = ((char *)src)[n];
	}
	else
	{
		while (i < n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
	}
	return (dest_ptr);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// // Your ft_memmove function
// void *ft_memmove(void *dest, const void *src, size_t n);

// int main() {
//     char src[] = "Hello, World!";
//     char dest[20];

//     // Copying src to dest using ft_memmove
//     ft_memmove(dest, src, strlen(src) + 1);

//     // Printing the result
//     printf("Destination after copying: %s\n", dest);

//     return 0;
// }