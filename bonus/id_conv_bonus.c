/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_conv_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 12:48:14 by agirona           #+#    #+#             */
/*   Updated: 2021/02/25 12:00:06 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	with_prec(t_flags *data, long long nb, int neg)
{
	int		space;
	int		ret;
	int		print;

	print = 0;
	if (nb == 0 && data->precision == 1 && data->preclen == 0)
		print = 1;
	space = data->preclen - data->nbsize;
	if (neg == 1)
		ft_putchar('-');
	ret = print_char(space + print, '0');
	if (print == 0)
		ft_putnbr(nb);
	data->total += ret + data->nbsize + neg - print;
}

void	fill_prec(t_flags *data, long long nb, int neg)
{
	int		space;
	int		zero;
	int		ret;
	int		print;

	print = (nb == 0 && data->precision == 1 && data->preclen == 0) ? 1 : 0;
	if (data->fillen > data->preclen && data->preclen >= 0)
	{
		space = data->fillen - data->nbsize - neg;
		if (data->preclen > data->nbsize)
			space = data->fillen - data->preclen - neg;
		ret = print_char(space + print, ' ') + data->nbsize + neg;
		zero = ret;
		if (neg == 1)
			ft_putchar('-');
		ret += print_char(data->fillen - zero, '0');
		if (print == 0)
			ft_putnbr(nb);
	}
	else
		ret = preclen_is_upper(data, nb, neg, 1);
	data->total += ret - print;
}

void	space_prec(t_flags *data, long long nb, int neg)
{
	int		space;
	int		zero;
	int		ret;
	int		print;

	print = (nb == 0 && data->precision == 1 && data->preclen == 0) ? 1 : 0;
	if (data->space > data->preclen)
	{
		space = data->space - data->nbsize - neg;
		if (data->preclen > data->nbsize)
			space = data->space - data->preclen - neg;
		ret = print_char(space + print, ' ') + data->nbsize + neg;
		zero = ret;
		if (neg == 1)
			ft_putchar('-');
		ret += print_char(data->space - zero, '0');
		if (print == 0)
			ft_putnbr(nb);
	}
	else
		ret = preclen_is_upper(data, nb, neg, 0);
	data->total += ret - print;
}

void	no_prec(t_flags *data, long long nb, int neg)
{
	int		len;
	int		ret;

	if (data->fill == 1)
	{
		len = data->fillen - neg - data->nbsize;
		if (neg == 1)
			ft_putchar('-');
		ret = print_char(len, '0');
	}
	else
	{
		len = data->space - neg - data->nbsize;
		ret = print_char(len, ' ');
		if (neg == 1)
			ft_putchar('-');
	}
	ft_putnbr(nb);
	data->total += ret + neg + data->nbsize;
}

void	int_conv(t_flags *data)
{
	long long	nb;
	int			neg;

	neg = 0;
	nb = va_arg(data->arg, int);
	if (nb < 0)
	{
		neg = 1;
		nb = ft_abs(nb);
	}
	data->nbsize = ft_longlen(nb);
	if (data->setspace == 1 && neg == 0 && data->plus == 0)
		set_space(data);
	if (data->plus == 1 && neg == 0)
		set_plus(data);
	if (data->align == 1)
		return (advanced_int_conv(data, nb, neg));
	if (data->precision == 0)
		no_prec(data, nb, neg);
	else if (data->precision == 1 && data->fill == 1 && data->space == 0)
		fill_prec(data, nb, neg);
	else if (data->precision == 1 && data->space > 0 && data->fill == 0)
		space_prec(data, nb, neg);
	else
		with_prec(data, nb, neg);
}
