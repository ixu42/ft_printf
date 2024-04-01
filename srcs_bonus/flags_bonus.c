/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:45:07 by ixu               #+#    #+#             */
/*   Updated: 2023/11/23 14:45:07 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf_bonus.h"

// all flags (excl. prec) are intialized to 0 (false)

t_flags	flags_init(void)
{
	t_flags	flags;

	flags.left = 0;
	flags.zero = 0;
	flags.hash = 0;
	flags.space = 0;
	flags.sign = 0;
	flags.width = 0;
	flags.prec = -1;
	flags.star = 0;
	return (flags);
}

void	set_left_flag(t_flags **flags)
{
	(*flags)->left = 1;
	(*flags)->zero = 0;
}

void	eval_star(t_flags **flags, va_list ap)
{
	(*flags)->star = 1;
	(*flags)->width = va_arg(ap, int);
	if ((*flags)->width < 0)
	{
		(*flags)->left = 1;
		(*flags)->width *= -1;
	}
}

void	get_width(char c, t_flags **flags)
{
	(*flags)->width = (*flags)->width * 10 + (c - '0');
}

int	get_prec(const char *format, int i, t_flags **flags, va_list ap)
{
	int	j;

	(*flags)->zero = 0;
	j = i + 1;
	if (format[j] == '*')
	{
		(*flags)->prec = va_arg(ap, int);
		return (j++);
	}
	(*flags)->prec = 0;
	while (ft_isdigit(format[j]))
	{
		(*flags)->prec = (*flags)->prec * 10 + (format[j] - '0');
		j++;
	}
	return (j);
}
