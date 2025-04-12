/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 20:00:33 by brian             #+#    #+#             */
/*   Updated: 2024/06/11 18:36:47 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
		else if (str[i] == c)
			i++;
	}
	return (count);
}

static char	**split(char const *s, char c, char **mem, int len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (i < count_words((char *)s, c))
	{
		while (s[j] && s[j] == c)
			j++;
		while (s[j] && s[j] != c)
		{
			j++;
			len++;
		}
		mem[i] = malloc(sizeof(char) * (len + 1));
		if (!mem[i])
			return (NULL);
		k = 0;
		while (len)
			mem[i][k++] = s[j - len--];
		mem[i++][k] = '\0';
	}
	mem[i] = NULL;
	return (mem);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	int		len;
	char	**mem;

	len = 0;
	words = count_words((char *)s, c);
	mem = (char **)malloc(sizeof(char *) * (words + 1));
	if (!mem)
		return (NULL);
	mem = split(s, c, mem, len);
	if (!mem)
		return (NULL);
	return (mem);
}

// #include <stdio.h>

// int main()
// {
//     int i = 0;
//     char *test = ",your,mom,kinda,happy,tbh!,";
//     char **result = ft_split(test, ',');

//     while (result[i])
//     {
//         printf("%s\n", result[i]);
//         i++;
//     }
//     i = 0;
//     while (result[i])
//     {
//         free(result[i]);
//         i++;
//     }
//     free(result);
//     return (0);
// }