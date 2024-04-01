/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:41:53 by ixu               #+#    #+#             */
/*   Updated: 2023/11/20 16:41:53 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include "libft/libft.h"

int	ft_printf(const char *format, ...);
int	print_char(int c);
int	print_str(char *str);
int	print_dec(long n);
int	print_udec(unsigned int n);
int	print_hex(unsigned int n, int hex_upper);
int	print_ptr(unsigned long int adr);

#endif