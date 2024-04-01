/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ixu <ixu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:47:55 by ixu               #+#    #+#             */
/*   Updated: 2023/11/23 14:47:55 by ixu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H
# include <stdarg.h>
# include "libft/libft.h"

typedef struct s_flags
{
	int	left;
	int	zero;
	int	prec;
	int	width;
	int	star;
	int	hash;
	int	space;
	int	sign;
}	t_flags;

// ft_printf() function
int		ft_printf(const char *format, ...);

// funcs for analyzing or modifying flags
t_flags	flags_init(void);
void	set_left_flag(t_flags **flags);
void	eval_star(t_flags **flags, va_list ap);
void	get_width(char c, t_flags **flags);
int		get_prec(const char *format, int i, t_flags **flags, va_list ap);

// funcs for printing specifiers (csdiuxXp)
// c
int		print_c_only(int c);
int		print_char(int c, t_flags flags);
// s
int		print_s_only(char *str);
int		print_str(char *str, t_flags flags);
// d, i
int		print_dec(long n, t_flags flags);
// u
int		print_udec(unsigned int n, t_flags flags);
// x, X
int		print_hex(unsigned int n, int is_X, t_flags flags);
// p
int		print_ptr(unsigned long int add, t_flags flags);
// helper funcs for the prints
int		print_width(t_flags flags, int len);
int		print_sign(t_flags flags, int is_neg);
int		print_prec(t_flags flags, int print_len);
int		print_hash(unsigned int n, int is_X, t_flags flags);

// other helper funcs
int		is_specifier(char c);
int		digits_len(long n, int base, t_flags flags);
int		ft_is_neg(long n);

#endif