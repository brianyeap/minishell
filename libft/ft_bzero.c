/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 02:17:32 by brian             #+#    #+#             */
/*   Updated: 2024/06/11 18:37:05 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)str)[i] = 0;
		i++;
	}
}

// #include <stdio.h>
// int main() {
// 	char buffer[3];

// 	ft_bzero(buffer, sizeof(buffer));
// 	printf("Buffer contents in integer format:\n");
// 	for (int i = 0; i < sizeof(buffer); i++) {
// 		printf("%d ", buffer[i]);
// 	}
// 	printf("\n");

// 	printf("Buffer contents in character format:\n");
// 	for (int i = 0; i < sizeof(buffer); i++) {
// 		printf("%c", buffer[i] == 0 ? '.' : buffer[i]);
// 	}
// 	printf("\n");
// 	return (0);
// }