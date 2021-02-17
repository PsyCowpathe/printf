/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_id_conv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 12:49:51 by agirona           #+#    #+#             */
/*   Updated: 2021/02/17 18:02:08 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	all_flag(t_flags *data, long long nb, int neg)
{
	int		space;
	int		ret;

	space = data->fillen;
	if (space < data->space)
		space = data->space;
	if (space < data->preclen)
		space = data->preclen;
	if (data->preclen >= space)
	{
		space = space - ft_longlen(nb);
		if (neg == 1)
			ft_putchar('-');
		ret = print_char(space, '0');
		ft_putnbr(nb);
	}
	else
	{
		space = space - ft_longlen(nb) - neg;
		if (neg == 1)
			ft_putchar('-');
		ft_putnbr(nb);
		ret = print_char(space, ' ');
	}
	data->total += ret + ft_longlen(nb) + neg;
}

void	advanced_fill_prec(t_flags *data, long long nb, int neg)
{
	int		ret;
	int		zero;
	int		print;

	print = 0;
	if (nb == 0 && data->precision == 1 && data->preclen == 0)
		print = 1;
	if (data->fillen > data->preclen)
	{
		if (neg == 1)
			ft_putchar('-');
		zero = data->preclen - ft_longlen(nb);
		ret = print_char(zero, '0');
		if (print == 0)
			ft_putnbr(nb);
		zero = data->fillen - ft_longlen(nb) - neg - ret;
		ret += print_char(zero + print, ' ');
		ret += neg + ft_longlen(nb);
	}
	else
		ret = preclen_is_upper(data, nb, neg, 0);
	data->total += ret - print;
}

void	advanded_space_prec(t_flags *data, long long nb, int neg)
{
	int		space;
	int		zero;
	int		ret;
	int		print;

	print = 0;
	if (nb == 0 && data->precision == 1 && data->preclen == 0)
		print = 1;
	if (data->space > data->preclen)
	{
		if (neg == 1)
			ft_putchar('-');
		if (data->preclen > ft_longlen(nb))
			zero = data->preclen - ft_longlen(nb);
		else
			zero = 0;
		ret = print_char(zero, '0') + ft_longlen(nb) + neg;
		if (print == 0)
			ft_putnbr(nb);
		space = ret;
		ret += print_char(data->space - space + print, ' ');
	}
	else
		ret = preclen_is_upper(data, nb, neg, 0);
	data->total += ret - print;
}

void	advanced_no_prec(t_flags *data, long long nb, int neg)
{
	int		space;
	int		ret;

	if (neg == 1)
		ft_putchar('-');
	ft_putnbr(nb);
	space = data->fillen;
	if (space < data->space)
		space = data->space;
	space = space - neg - ft_longlen(nb);
	ret = print_char(space, ' ');
	data->total += ret + neg + ft_longlen(nb);
}

void	advanced_int_conv(t_flags *data, long long nb, int neg)
{
	if (data->precision == 0)
		advanced_no_prec(data, nb, neg);
	else if (data->precision == 1 && data->fill == 1 && data->space == 0)
		advanced_fill_prec(data, nb, neg);
	else if (data->precision == 1 && data->space > 0 && data->fill == 0)
		advanded_space_prec(data, nb, neg);
	else if (data->precision == 1 && data->space > 0 && data->fill == 1)
		all_flag(data, nb, neg);
	else
		with_prec(data, nb, neg);
}
