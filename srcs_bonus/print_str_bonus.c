/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:49:12 by ixu               #+#    #+#             */
/*   Updated: 2023/11/23 14:49:12 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

int	print_s_only(char *str)
{
	if (str == NULL)
		return (write(1, "(null)", 6));
	return (write(1, str, ft_strlen(str)));
}

// print string up to len characters

static int	print_str_up_to_len(char *str, int len)
{
	if (str == NULL)
		return (print_str_up_to_len("(null)", len));
	return (write(1, str, len));
}

/* print string up to len characters, 
flags (left, width, precision) are taken care of */

static int	print_string(char *str, t_flags flags, int *count, int print_len)
{
	int	count_temp;

	if (flags.left)
	{
		count_temp = print_str_up_to_len(str, print_len);
		if (count_temp == -1)
			return (-1);
		*count += count_temp;
	}
	if (flags.width - print_len > 0)
	{
		count_temp = print_width(flags, flags.width - print_len);
		if (count_temp == -1)
			return (-1);
		*count += count_temp;
	}
	if (!flags.left)
	{
		count_temp = print_str_up_to_len(str, print_len);
		if (count_temp == -1)
			return (-1);
		*count += count_temp;
	}
	return (0);
}

/*
	if (flags.prec >= 0 && flags.prec < strlen): // print_len = prec
		if (left): str->width
		else: width->str
	else // print_len = strlen
		if (left): str->width
		else: width->str
 */

int	print_str(char *str, t_flags flags)
{
	int	count;
	int	count_temp;
	int	strlen;

	count = 0;
	if (str == NULL)
		strlen = 6;
	else
		strlen = (int)ft_strlen(str);
	if (flags.prec >= 0 && flags.prec < strlen)
	{
		count_temp = print_string(str, flags, &count, flags.prec);
		if (count_temp == -1)
			return (-1);
	}
	else
	{
		count_temp = print_string(str, flags, &count, strlen);
		if (count_temp == -1)
			return (-1);
	}
	return (count);
}
