/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:33:07 by agirona           #+#    #+#             */
/*   Updated: 2021/01/30 16:20:30 by agirona          ###   ########lyon.fr   */
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

typedef struct	s_flags
{
	char		*form;
	char		*primlist;
	char		*seclist;
	char		primary;
	int			len;
	bool		align;
	bool		fill;
	int			fillen;
	bool		precision;
	int			preclen;
	bool		size;
	int			width;
}				t_flags;

char	*ft_long_itoa(long long n);
int		ft_abs(int nb);
int		ft_nblen(long long nb);
void	ft_long_putnbr_base(uintptr_t nbr, char *base);
int		cut_flags(t_flags data, va_list arg);
int		flags_init(char **primary, char *plist, char **secondary, char *slist);
int		int_conv(t_flags data, va_list arg);
int		unsigned_conv(t_flags data, va_list arg);
int		verif_flags(t_flags data, char *cut);
void	string_conv(t_flags data, va_list arg);
void	address_conv(t_flags data, va_list arg);
void	hex_conv(t_flags data, va_list arg);
int		ft_long_size_base(uintptr_t nbr, char *base);
int		is_vip(char *list, char c);
int		set_struct(t_flags data, va_list arg, char *cut);


#endif
