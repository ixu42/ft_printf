/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:44:22 by ixu               #+#    #+#             */
/*   Updated: 2023/11/20 16:44:22 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	print_arg(const char *format, int i, va_list ap)
{
	int	count;

	count = 0;
	if (format[i] == 'c')
		count = print_char(va_arg(ap, int));
	else if (format[i] == 's')
		count = print_str(va_arg(ap, char *));
	else if (format[i] == 'd' || format[i] == 'i')
		count = print_dec((long)va_arg(ap, int));
	else if (format[i] == 'u')
		count = print_udec((unsigned int)va_arg(ap, int));
	else if (format[i] == 'x')
		count = print_hex((unsigned int)va_arg(ap, int), 0);
	else if (format[i] == 'X')
		count = print_hex((unsigned int)va_arg(ap, int), 1);
	else if (format[i] == 'p')
		count = print_ptr((unsigned long)va_arg(ap, void *));
	else if (format[i] == '%')
		count = print_char('%');
	else
		count = -1;
	return (count);
}

static int	eval_format(const char *format, va_list ap)
{
	int	i;
	int	count;
	int	count_temp;

	i = -1;
	count = 0;
	while (format[++i])
	{
		if (format[i] == '%' && format[i + 1] != '\0')
			count_temp = print_arg(format, ++i, ap);
		else if (format[i] == '%' && format[i + 1] == '\0')
			return (-1);
		else
			count_temp = print_char(format[i]);
		if (count_temp == -1)
			return (-1);
		count += count_temp;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = eval_format(format, ap);
	va_end(ap);
	return (count);
}
