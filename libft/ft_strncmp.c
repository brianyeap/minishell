/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:30:27 by brian             #+#    #+#             */
/*   Updated: 2024/06/11 18:37:05 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return (((unsigned char)s1[i] - (unsigned char)s2[i]));
}

// #include <stdio.h>
// int main()
// {
// 	printf("%d", ft_strncmp("hA", "haass", 2));
// 	return (0);
// }