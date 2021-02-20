/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:33:07 by agirona           #+#    #+#             */
/*   Updated: 2021/02/20 15:41:36 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define FPRIMARY 9
# define FSECONDARY 4

#include "libft/libft.h"
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>

typedef struct	s_flags
{
	char		*form;
	char		*primlist;
	char		*seclist;
	char		primary;
	bool		align;
	bool		fill;
	int			fillen;
	bool		precision;
	int			preclen;
	int			space;
	int			total;
	bool		error;
	bool		noprim;
	int			nbsize;
	va_list		arg;
}				t_flags;

int		ft_printf(const char *str, ...);
char	*ft_long_itoa(long long n);
void	ft_long_putnbr_base(uintptr_t nbr, char *base);
void	ft_llong_putnbr_base(unsigned long long nbr, char *base);
int		cut_flags(t_flags data);
int		flags_init(char **primary, char *plist, char **secondary, char *slist);
void	int_conv(t_flags *data);
void	unsigned_conv(t_flags *data);
int		verif_flags(t_flags data, char *cut);
void	string_conv(t_flags *data, char *str);
void	address_conv(t_flags *data);
void	hex_conv(t_flags *data);
int		ft_long_size_base(uintptr_t nbr, char *base);
void	char_conv(t_flags *data);
void	*struct_init(t_flags *data);
int		print_char(int len, char c);
void	advanced_int_conv(t_flags *data, long long nb, int neg);
void	with_prec(t_flags *data, long long nb, int neg);
int		preclen_is_upper(t_flags *data, long long nb, int neg, int wich);
void	advanced_unsigned_conv(t_flags *data, long long nb);
int		u_preclen_is_upper(t_flags *data, long long nb, char *tmp, int wich);
int		get_nb(t_flags *data, char *cut, int *i);
void	moin(t_flags *data, char *cut, int *i);
void	zero(t_flags *data, char *cut, int *i);
void	dot(t_flags *data, char *cut, int *i);
void	asterisk(t_flags *data, char *cut, int *i);
void	nombre(t_flags *data, char *cut, int *i);

void	print_struct(t_flags data);

#endif
