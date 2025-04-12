/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 02:36:21 by brian             #+#    #+#             */
/*   Updated: 2024/06/11 18:37:05 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *des, void const *src, size_t n)
{
	void	*des_ptr;
	size_t	i;

	des_ptr = des;
	i = 0;
	if (!des && !src)
		return (des);
	while (i < n)
	{
		((char *)des)[i] = ((char *)src)[i];
		i++;
	}
	return (des_ptr);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
//     char test[10];
//     char word[10] = "Hello";

//     printf("Before memcpy: test = '%s', word = '%s'\n", test, word);
//     ft_memcpy(test, word, strlen(word) + 1);
//     printf("After memcpy: test = '%s', word = '%s'\n", test, word);
//     return 0;
// }