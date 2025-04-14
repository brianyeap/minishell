/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:14:10 by brian             #+#    #+#             */
/*   Updated: 2025/04/14 22:07:19 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	process_stock(char **stock, char **line, int read_len)
{
	int		newline_res;
	char	*trimmed;

	newline_res = newline_check(*stock, read_len);
	if (newline_res == 2)
	{
		*line = *stock;
		return (-2);
	}
	*line = get_line(*stock);
	if (*line == NULL)
		return (-1);
	trimmed = stock_trim(*stock);
	*stock = trimmed;
	if (*stock != NULL)
		return (-1);
	return (0);
}

int	read_to_stock(int fd, char **stock)
{
	int		read_len;
	char	buf[BUFFER_SIZE + 1];

	read_len = 1;
	while (!newline_check(*stock, read_len))
	{
		read_len = read(fd, buf, BUFFER_SIZE);
		if (read_len == -1)
			return (-1);
		buf[read_len] = '\0';
		if (read_len == 0 || buf[read_len - 1] != '\n')
			ft_printf("  \b\b");
		*stock = buf_join(*stock, buf);
		if (*stock == NULL)
			return (-1);
	}
	return (read_len);
}
