/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:39:48 by ixu               #+#    #+#             */
/*   Updated: 2024/04/01 17:14:29 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

// check if the passed char is a conversion specifier

int	is_specifier(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

int	digits_len(long n, int base, t_flags flags)
{
	int	len;

	len = 0;
	if (flags.prec == 0 && n == 0)
		return (0);
	if (n < 0)
		n *= -1;
	if (n >= base)
	{
		len = digits_len(n / base, base, flags);
		return (len + 1);
	}
	else
		return (len + 1);
	return (len);
}

int	ft_is_neg(long n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}
