/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_chars_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:48:35 by ixu               #+#    #+#             */
/*   Updated: 2023/11/23 14:48:35 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

int	print_c_only(int c)
{
	return (write(1, &c, 1));
}

/* 
	if (left): char->width(' ')
	else: width(' ')->char
*/

int	print_char(int c, t_flags flags)
{
	int	count;
	int	count_temp;

	count = 0;
	if (flags.left)
	{
		count_temp = print_c_only(c);
		if (count_temp == -1)
			return (-1);
		count += count_temp;
	}
	count_temp = print_width(flags, flags.width - 1);
	if (count_temp == -1)
		return (-1);
	count += count_temp;
	if (!flags.left)
	{
		count_temp = print_c_only(c);
		if (count_temp == -1)
			return (-1);
		count += count_temp;
	}
	return (count);
}
