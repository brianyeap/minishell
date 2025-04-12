/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:53:00 by brian             #+#    #+#             */
/*   Updated: 2024/06/11 18:37:05 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void const *str, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (n--)
	{
		if (((unsigned char *)str)[i] == (unsigned char)c)
			return ((void *)((unsigned char *)str + i));
		i++;
	}
	return (NULL);
}
