/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:49:24 by ixu               #+#    #+#             */
/*   Updated: 2023/11/23 14:49:24 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

// pad width with zero or space up to len characters

int	print_width(t_flags flags, int print_len)
{
	int	count;
	int	count_temp;

	count = 0;
	while (print_len > 0)
	{
		if (flags.zero)
			count_temp = print_c_only('0');
		else
			count_temp = print_c_only(' ');
		if (count_temp == -1)
			return (-1);
		count += count_temp;
		print_len--;
	}
	return (count);
}

static int	print_space(t_flags flags, int is_neg)
{
	int	count;
	int	count_temp;

	count = 0;
	if (flags.space && !is_neg)
	{
		count_temp = print_c_only(' ');
		if (count_temp == -1)
			return (-1);
		count += count_temp;
	}
	return (count);
}

int	print_sign(t_flags flags, int is_neg)
{
	int	count;
	int	count_temp;

	count = 0;
	if (flags.sign && !is_neg)
	{
		count_temp = print_c_only('+');
		if (count_temp == -1)
			return (-1);
		count += count_temp;
	}
	if (is_neg)
	{
		count_temp = print_c_only('-');
		if (count_temp == -1)
			return (-1);
		count += count_temp;
	}
	count_temp = print_space(flags, is_neg);
	if (count_temp == -1)
		return (-1);
	count += count_temp;
	return (count);
}

int	print_prec(t_flags flags, int print_len)
{
	int	count;
	int	count_temp;

	count = 0;
	if (flags.prec != -1)
	{
		while (print_len > 0)
		{
			count_temp = print_c_only('0');
			if (count_temp == -1)
				return (-1);
			count += count_temp;
			print_len--;
		}
	}
	return (count);
}

int	print_hash(unsigned int n, int is_X, t_flags flags)
{
	int	count;
	int	count_temp;

	count = 0;
	count_temp = 0;
	if (flags.hash)
	{
		if (is_X && n != 0)
			count_temp = print_s_only("0X");
		else if (!is_X && n != 0)
			count_temp = print_s_only("0x");
		if (count_temp == -1)
			return (-1);
		count += count_temp;
	}
	return (count);
}
