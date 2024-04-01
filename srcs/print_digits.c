/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:51:25 by ixu               #+#    #+#             */
/*   Updated: 2023/11/20 16:51:25 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	print_dec(long n)
{
	int		count;

	if (n < 0)
	{
		count = print_char('-');
		if (count == -1)
			return (-1);
		return (print_dec(-n) + 1);
	}
	else if (n >= 10)
	{
		count = print_dec(n / 10);
		if (count == -1)
			return (-1);
		return (count + print_char(n % 10 + '0'));
	}
	else
		return (print_char(n % 10 + '0'));
}

int	print_udec(unsigned int n)
{
	int		count;

	if (n >= 10)
	{
		count = print_udec(n / 10);
		if (count == -1)
			return (-1);
		return (count + print_char(n % 10 + '0'));
	}
	else
		return (print_char(n % 10 + '0'));
}

int	print_hex(unsigned int n, int hex_upper)
{
	int		count;
	char	*symbols;

	symbols = "0123456789abcdef";
	if (hex_upper)
		symbols = "0123456789ABCDEF";
	if (n >= 16)
	{
		count = print_hex(n / 16, hex_upper);
		if (count == -1)
			return (-1);
		return (count + print_char(symbols[n % 16]));
	}
	else
		return (print_char(symbols[n]));
}

static int	print_adr(unsigned long n)
{
	char	*symbols;
	int		count;

	symbols = "0123456789abcdef";
	if (n >= 16)
	{
		count = print_adr(n / 16);
		if (count == -1)
			return (-1);
		return (count + print_char(symbols[n % 16]));
	}
	else
		return (print_char(symbols[n]));
}

int	print_ptr(unsigned long n)
{
	int	count;
	int	count_temp;

	count = 0;
	if (n == 0)
		return (print_str(PRINT_NULL));
	count_temp = print_str("0x");
	if (count_temp == -1)
		return (-1);
	count += count_temp;
	count_temp = print_adr(n);
	if (count_temp == -1)
		return (-1);
	count += count_temp;
	return (count);
}
