/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:26:12 by bryeap            #+#    #+#             */
/*   Updated: 2025/04/16 18:20:58 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	u_int_len(unsigned int nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		len++;
	while (nbr)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static char	*u_ft_itoa(unsigned int n)
{
	int					len;
	unsigned int		nbr;
	char				*mem;

	nbr = n;
	len = u_int_len(nbr);
	mem = malloc(sizeof(char) * (len + 1));
	if (!mem)
		return (NULL);
	mem[len] = '\0';
	while (len--)
	{
		mem[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (mem);
}

int	ft_print_unsigned_int(unsigned int n)
{
	char	*num;
	int		len;

	len = 0;
	if (n == 0)
		len += write(1, "0", 1);
	else
	{
		num = u_ft_itoa(n);
		len = ft_print_str(num);
		free(num);
	}
	return (len);
}
