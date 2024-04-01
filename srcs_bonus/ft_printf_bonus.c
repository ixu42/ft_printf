/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:46:21 by ixu               #+#    #+#             */
/*   Updated: 2023/11/23 14:46:21 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

static int	print_arg(const char *format, int i, t_flags flags, va_list ap)
{
	int	count;

	count = 0;
	if (format[i] == 'c')
		count = print_char(va_arg(ap, int), flags);
	else if (format[i] == 's')
		count = print_str(va_arg(ap, char *), flags);
	else if (format[i] == 'd' || format[i] == 'i')
		count = print_dec((long)va_arg(ap, int), flags);
	else if (format[i] == 'u')
		count = print_udec((unsigned int)va_arg(ap, int), flags);
	else if (format[i] == 'x')
		count = print_hex((unsigned int)va_arg(ap, int), 0, flags);
	else if (format[i] == 'X')
		count = print_hex((unsigned int)va_arg(ap, int), 1, flags);
	else if (format[i] == 'p')
		count = print_ptr((unsigned long)va_arg(ap, void *), flags);
	else if (format[i] == '%')
		count = print_char('%', flags);
	else
		count = -1;
	return (count);
}

static int	parse_flags(const char *format, int i, t_flags *flags, va_list ap)
{
	while (!is_specifier(format[++i]))
	{
		if (format[i] == '-')
			set_left_flag(&flags);
		else if (format[i] == '0' && flags->width == 0 && flags->left == 0)
			flags->zero = 1;
		else if (format[i] == '#')
			flags->hash = 1;
		else if (format[i] == ' ' && flags->sign == 0)
			flags->space = 1;
		else if (format[i] == '+')
			flags->sign = 1;
		else if (format[i] == '*')
			eval_star(&flags, ap);
		else if (ft_isdigit(format[i]))
			get_width(format[i], &flags);
		else if (format[i] == '.')
			i = get_prec(format, i, &flags, ap);
		else
			return (i);
		if (is_specifier(format[i]))
			break ;
	}
	return (i);
}

static int	eval_format(const char *format, va_list ap, t_flags flags)
{
	int	i;
	int	count;
	int	count_temp;

	i = -1;
	count = 0;
	while (format[++i])
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			i = parse_flags(format, i, &flags, ap);
			count_temp = print_arg(format, i, flags, ap);
			flags = flags_init();
		}
		else if (format[i] == '%' && format[i + 1] == '\0')
			return (-1);
		else
			count_temp = print_c_only(format[i]);
		if (count_temp == -1)
			return (-1);
		count += count_temp;
	}
	return (count);
}

/*
	The overall syntax of a conversion specification:
	%[flags][width][.precision]conversion
	flags = "-0# +"
*/

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	t_flags	flags;
	int		count;

	flags = flags_init();
	va_start(ap, format);
	count = eval_format(format, ap, flags);
	va_end(ap);
	return (count);
}
