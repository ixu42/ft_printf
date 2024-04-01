/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:48:57 by ixu               #+#    #+#             */
/*   Updated: 2023/11/23 14:48:57 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

static int	print_hex_only(unsigned int n, int is_X, t_flags flags)
{
	int		count;
	char	*symbols;

	symbols = "0123456789abcdef";
	if (is_X)
		symbols = "0123456789ABCDEF";
	if (flags.prec == 0 && n == 0)
		return (0);
	if (n >= 16)
	{
		count = print_hex_only(n / 16, is_X, flags);
		if (count == -1)
			return (-1);
		return (count + print_c_only(symbols[n % 16]));
	}
	else
		return (print_c_only(symbols[n]));
}

// print first digits then width

static int	print_digit_width(unsigned int n, int is_X, t_flags flags, int len)
{
	int	count;
	int	count_temp;

	count = 0;
	count_temp = print_hash(n, is_X, flags);
	if (count_temp == -1)
		return (-1);
	count += count_temp;
	count_temp = print_prec(flags, flags.prec - digits_len((long)n, 16, flags));
	if (count_temp == -1)
		return (-1);
	count += count_temp;
	count_temp = print_hex_only(n, is_X, flags);
	if (count_temp == -1)
		return (-1);
	count += count_temp;
	count_temp = print_width(flags, flags.width - len);
	if (count_temp == -1)
		return (-1);
	count += count_temp;
	return (count);
}

// print width and hash based on flag 0

static int	print_hash_width(unsigned int n, int is_X, t_flags flags, int len)
{
	int	count;
	int	count_temp;

	count = 0;
	if (flags.zero)
	{
		count_temp = print_hash(n, is_X, flags);
		if (count_temp == -1)
			return (-1);
		count += count_temp;
	}
	count_temp = print_width(flags, flags.width - len);
	if (count_temp == -1)
		return (-1);
	count += count_temp;
	if (!flags.zero)
	{
		count_temp = print_hash(n, is_X, flags);
		if (count_temp == -1)
			return (-1);
		count += count_temp;
	}
	return (count);
}

// print first width then digits

static int	print_width_digit(unsigned int n, int is_X, t_flags flags, int len)
{
	int	count;
	int	count_temp;

	count = 0;
	count_temp = print_hash_width(n, is_X, flags, len);
	if (count_temp == -1)
		return (-1);
	count += count_temp;
	count_temp = print_prec(flags, flags.prec - digits_len((long)n, 16, flags));
	if (count_temp == -1)
		return (-1);
	count += count_temp;
	count_temp = print_hex_only(n, is_X, flags);
	if (count_temp == -1)
		return (-1);
	count += count_temp;
	return (count);
}

/* 
	if (left)
		prec->num->width(' ')
	else
		hash->width(0)->num || 
		width(' ')->hash->prec->num 
*/

int	print_hex(unsigned int n, int is_X, t_flags flags)
{
	int	len;
	int	count;
	int	count_temp;

	count = 0;
	len = digits_len((long)n, 16, flags);
	if (flags.hash && n != 0)
		len += 2;
	if (flags.prec - digits_len((long)n, 16, flags) > 0)
		len += flags.prec - digits_len((long)n, 16, flags);
	if (flags.left)
	{
		count_temp = print_digit_width(n, is_X, flags, len);
		if (count_temp == -1)
			return (-1);
		count += count_temp;
	}
	else
	{
		count_temp = print_width_digit(n, is_X, flags, len);
		if (count_temp == -1)
			return (-1);
		count += count_temp;
	}
	return (count);
}
