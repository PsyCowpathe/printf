/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_conv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:41:36 by agirona           #+#    #+#             */
/*   Updated: 2021/02/21 17:29:28 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	u_no_prec(t_flags *data, char *tmp)
{
	int		len;
	int		ret;

	if (data->fill == 1)
	{
		len = data->fillen - data->nbsize;
		ret = print_char(len, '0');
	}
	else
	{
		len = data->space - data->nbsize;
		ret = print_char(len, ' ');
	}
	ft_putstr(tmp);
	data->total += data->nbsize + ret;
}

void	prec_space(t_flags *data, char *tmp, long long nb)
{
	int		space;
	int		zero;
	int		ret;
	int		print;

	print = 0;
	if (nb == 0 && data->preclen == 0)
		print = 1;
	if (data->space >= data->preclen && data->preclen >= 0)
	{
		space = data->space - data->nbsize;
		if (data->preclen > data->nbsize)
			space = data->space - data->preclen;
		ret = print_char(space + print, ' ') + data->nbsize;
		zero = ret;
		ret += print_char(data->space - zero, '0');
		if (print == 0)
			ft_putstr(tmp);
	}
	else
		ret = u_preclen_is_upper(data, nb, tmp, 2);
	data->total += ret - print;
}

void	prec_fill(t_flags *data, char *tmp, long long nb)
{
	int		space;
	int		zero;
	int		ret;
	int		print;

	print = 0;
	if (nb == 0 && data->preclen == 0)
		print = 1;
	if (data->fillen > data->preclen && data->preclen >= 0)
	{
		space = data->fillen - data->nbsize;
		if (data->preclen > data->nbsize)
			space = data->fillen - data->preclen;
		ret = print_char(space + print, ' ') + data->nbsize;
		zero = ret;
		ret += print_char(data->fillen - zero, '0');
		if (print == 0)
			ft_putstr(tmp);
	}
	else
		ret = u_preclen_is_upper(data, nb, tmp, 1);
	data->total += ret - print;
}

void	u_prec(t_flags *data, char *tmp, long long nb)
{
	int		space;
	int		ret;
	int		print;

	print = 0;
	if (nb == 0 && data->precision == 1 && data->preclen == 0)
		print = 1;
	space = data->preclen - data->nbsize;
	ret = print_char(space + print, '0');
	if (print == 0)
		ft_putstr(tmp);
	data->total += ret + data->nbsize - print;
}

void	unsigned_conv(t_flags *data)
{
	long long	nb;
	char		*tmp;

	nb = (unsigned int)va_arg(data->arg, unsigned int);
	data->nbsize = ft_longlen(nb);
	if (data->align == 1)
		return (advanced_unsigned_conv(data, nb));
	tmp = ft_long_itoa(nb);
	if (data->precision == 0)
		u_no_prec(data, tmp);
	else if (data->precision == 1 && data->fill == 1 && data->space == 0)
		prec_fill(data, tmp, nb);
	else if (data->precision == 1 && data->fill == 0 && data->space > 0)
		prec_space(data, tmp, nb);
	else
		u_prec(data, tmp, nb);
	free(tmp);
}
