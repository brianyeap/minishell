/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 04:03:23 by brian             #+#    #+#             */
/*   Updated: 2024/06/11 23:07:24 by brian            ###   ########.fr       */
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

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;	
	size_t	j;

	i = 0;
	j = 0;
	while (i < n && dest[i])
		i++;
	while ((i + j + 1) < n && src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i != n)
		dest[i + j] = '\0';
	return (i + my_strlen(src));
}
