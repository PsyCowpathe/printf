/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:33:07 by agirona           #+#    #+#             */
/*   Updated: 2021/02/12 18:01:32 by agirona          ###   ########lyon.fr   */
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
}				t_flags;

int		ft_printf(const char *str, ...);
char	*ft_long_itoa(long long n);
void			ft_long_putnbr_base(uintptr_t nbr, char *base);
void	ft_llong_putnbr_base(unsigned long long nbr, char *base);
int		cut_flags(t_flags data, va_list arg);
int		flags_init(char **primary, char *plist, char **secondary, char *slist);
void	int_conv(t_flags *data, va_list arg);
void	unsigned_conv(t_flags *data, va_list arg);
int		verif_flags(t_flags data, char *cut);
void	string_conv(t_flags *data, char *str);
void	address_conv(t_flags *data, va_list arg);
void	hex_conv(t_flags *data, va_list arg);
int		ft_long_size_base(uintptr_t nbr, char *base);
void	char_conv(t_flags *data, va_list arg);
int		print_percent(char *form, int *i);
void	struct_init(t_flags *data);

void	print_struct(t_flags data);

#endif
