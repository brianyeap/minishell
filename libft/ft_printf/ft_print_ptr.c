/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryeap <bryeap@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:08:36 by brian             #+#    #+#             */
/*   Updated: 2024/06/28 14:22:40 by bryeap           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptr_len(uintptr_t num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		num /= 16;
		len++;
	}
	return (len);
}

void	ft_put_ptr(uintptr_t num)
{
	if (num >= 16)
	{
		ft_put_ptr(num / 16);
		ft_put_ptr(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_print_char(num + '0');
		else
		{
			ft_print_char(num - 10 + 'a');
		}
	}
}

int	ft_print_ptr(unsigned long long ptr)
{
	int	len;

	len = 0;
	len += write(1, "0x", 2);
	if (ptr == 0)
		len += write(1, "0", 1);
	else
	{
		ft_put_ptr(ptr);
		len += ft_ptr_len(ptr);
	}
	return (len);
}
