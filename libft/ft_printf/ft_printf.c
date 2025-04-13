/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:43:17 by bryeap            #+#    #+#             */
/*   Updated: 2025/04/14 05:21:06 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format(va_list args, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
	{
		len += ft_print_char(va_arg(args, int));
	}
	else if (format == 's')
		len += ft_print_str(va_arg(args, char *));
	else if (format == 'p')
		len += ft_print_ptr(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		len += ft_printnbr(va_arg(args, int));
	else if (format == 'u')
		len += ft_print_unsigned_int(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		len += ft_print_hex(va_arg(args, unsigned int), format);
	else if (format == '%')
		len += write(1, "%", 1);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		len;
	va_list	args;

	va_start(args, format);
	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%')
			len += ft_format(args, format[++i]);
		else
			len += ft_print_char(format[i]);
		i++;
	}
	va_end(args);
	return (len);
}

// #include <stdio.h>
// int main()
// {
// 	char *test = "test";
// 	int num = 2147483650;
// 	ft_printf("%c", 'a');
// 	ft_printf("%c", '\n');
// 	ft_printf("%s", "test");
// 	ft_printf("%c", '\n');
// 	ft_printf("%d", 2147483650);
// 	printf("%d", 2147483650);
// 	ft_printf("%c", '\n');
// 	ft_printf("%%", '%');
// 	ft_printf("%c", '\n');
// 	ft_printf("%p", NULL);
// 	ft_printf("%c", '\n');
// 	ft_printf("%X", &test);

// 	return (0);
// }