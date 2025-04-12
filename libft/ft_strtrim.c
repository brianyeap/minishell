/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:10:37 by brian             #+#    #+#             */
/*   Updated: 2024/06/11 19:08:09 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i += 1;
	return (i);
}

static int	check_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*mem;
	int		start;
	int		end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && check_char((char *)set, (char)s1[start]))
		start++;
	end = my_strlen((char *)s1);
	while (end > start && check_char((char *)set, (char)s1[end - 1]))
		end--;
	mem = malloc(end - start + 1);
	if (!mem)
		return (NULL);
	i = 0;
	while ((start + i) < end)
	{
		mem[i] = s1[start + i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}

// int main()
// {
// 	char *str = "    Your mom is yes!     ";
// 	char *set = " ";
// 	printf("%s", ft_strtrim(str, set));
// 	return (0);
// }