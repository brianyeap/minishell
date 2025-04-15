/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:21:48 by brian             #+#    #+#             */
/*   Updated: 2025/04/16 01:57:14 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// deivide by 256 to get the actual exit code (126, 127)
// 126 is for cmd not executable
// 127 is for cmd not found
int	normalize_exit_code(int ret)
{
	if (ret == 32256 || ret == 32512)
		return (ret / 256);
	else
		return (!!ret); // converts non-zero value to 1 amd 0 to 0
}
