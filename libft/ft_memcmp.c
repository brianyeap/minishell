/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryeap <bryeap@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:08:41 by brian             #+#    #+#             */
/*   Updated: 2024/06/14 14:44:40 by bryeap           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (((const unsigned char *)s1)[i] ==
		((const unsigned char *)s2)[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return ((((const unsigned char *)s1)[i] - ((const unsigned char *)s2)[i]));
}
