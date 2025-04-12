/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:07:48 by brian             #+#    #+#             */
/*   Updated: 2024/06/11 18:37:05 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	char const	*occur;

	i = 0;
	occur = NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
			occur = &s[i];
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return ((char *)occur);
}
