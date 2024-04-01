/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_udec_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 21:39:45 by ixu               #+#    #+#             */
/*   Updated: 2023/11/22 21:39:45 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

static int	print_udec_only(unsigned int n, t_flags flags)
{
	int		count;

	if (flags.prec == 0 && n == 0)
		return (0);
	if (n >= 10)
	{
		count = print_udec_only(n / 10, flags);
		if (count == -1)
			return (-1);
		return (count + print_c_only(n % 10 + '0'));
	}
	else
		return (print_c_only(n % 10 + '0'));
}

// print first digits then width

static int	print_digit_width(unsigned int n, t_flags flags, int len)
{
	int	count;
	int	count_temp;

	count = 0;
	count_temp = print_prec(flags, flags.prec - digits_len((long)n, 10, flags));
	if (count_temp == -1)
		return (-1);
	count += count_temp;
	count_temp = print_udec_only(n, flags);
	if (count_temp == -1)
		return (-1);
	count += count_temp;
	count_temp = print_width(flags, flags.width - len);
	if (count_temp == -1)
		return (-1);
	count += count_temp;
	return (count);
}

// print first width then digits

static int	print_width_digit(unsigned int n, t_flags flags, int len)
{
	int	count;
	int	count_temp;

	count = 0;
	count_temp = print_width(flags, flags.width - len);
	if (count_temp == -1)
		return (-1);
	count += count_temp;
	count_temp = print_prec(flags, flags.prec - digits_len((long)n, 10, flags));
	if (count_temp == -1)
		return (-1);
	count += count_temp;
	count_temp = print_udec_only(n, flags);
	if (count_temp == -1)
		return (-1);
	count += count_temp;
	return (count);
}

/*
	if (left)
		prec->num->width(' ')
	else
		width(0)->num || 
		width(' ')->prec->num 
*/

int	print_udec(unsigned int n, t_flags flags)
{
	int	len;
	int	count;
	int	count_temp;

	count = 0;
	len = digits_len((long)n, 10, flags);
	if (flags.prec - digits_len((long)n, 10, flags) > 0)
		len += flags.prec - digits_len((long)n, 10, flags);
	if (flags.left)
	{
		count_temp = print_digit_width(n, flags, len);
		if (count_temp == -1)
			return (-1);
		count += count_temp;
	}
	else
	{
		count_temp = print_width_digit(n, flags, len);
		if (count_temp == -1)
			return (-1);
		count += count_temp;
	}
	return (count);
}
