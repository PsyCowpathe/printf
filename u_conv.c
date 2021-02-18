/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_conv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:41:36 by agirona           #+#    #+#             */
/*   Updated: 2021/02/18 17:48:19 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	advanced_unsign_conv(t_flags *data, int size, unsigned int nb)
{
	int		i;
	int		print;
	char	*tmp;

	i = -1;
	print = 1;
	tmp = ft_long_itoa(nb);
	if (nb == 0 && data->precision == 1 && data->preclen == 0)
	{
		i--;
		print = 0;
	}
	if (data->precision == 1 && data->fill == 0 && data->space == 0)
	{
		while (++i < size)
			ft_putchar('0');
		if (print == 1)
			ft_putstr(tmp);
	}
	else if (data->precision == 0 && data->fill == 1 && data->space > 0)
	{
		if (data->space < data->fillen)
			size = data->space - data->nbsize;
		ft_putstr(tmp);
		while (++i < size)
			ft_putchar(' ');
	}
	else
	{
		while (++i < size)
		{
			if (i < data->preclen - data->nbsize)
				ft_putchar('0');
			else
			{
				if (--print == 0)
					ft_putstr(tmp);
				ft_putchar(' ');
			}
		}
		if (print == 1 || (data->fill == 0 && data->precision == 0 && data->space == 0))
			ft_putstr(tmp);
	}
	if (i == -1)
		i++;
	data->total += i + data->nbsize;
	if (nb == 0 && data->space == 0 && data->precision == 1 && data->preclen == 0 && data->fill == 0)
		data->total--;
	free(tmp);
}

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

int		u_preclen_is_upper(t_flags *data, long long nb, int wich)
{
	int		print;
	int		ret;
	int		zero;
	int		nblen;

	nblen = data->nbsize;
	print = (nb == 0 && data->precision == 1 && data->preclen == 0) ? 1 : 0;
	zero = data->preclen - nblen;
	if (wich == 1 && data->preclen < 0)
		zero = data->fillen - nblen;
	ret = print_char(zero + print, '0');
	ret += nblen;
	if (print == 0)
		ft_putnbr(nb);
	return (ret);
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
			space = data->space - data->preclen ;
		ret = print_char(space + print, ' ') + data->nbsize;
		zero = ret;
		ret += print_char(data->space - zero, '0');
		if (print == 0)
			ft_putstr(tmp);
	}
	else
	{
		zero = data->preclen - data->nbsize;
		if (data->preclen < 0)
			zero = data->space - data->nbsize;
		if (data->preclen > data->space)
			ret = print_char(zero + print, '0');
		else
			ret = print_char(zero + print, ' ');
		ret += data->nbsize;
		if (print == 0)
			ft_putnbr(nb);
	}
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
			space = data->fillen - data->preclen ;
		ret = print_char(space + print, ' ') + data->nbsize;
		zero = ret;
		ret += print_char(data->fillen - zero, '0');
		if (print == 0)
			ft_putstr(tmp);
	}
	else
		ret = u_preclen_is_upper(data, nb, 1);
	data->total += ret - print;
}

void	u_with_prec(t_flags *data, char *tmp, long long nb)
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

void	u_advanced_no_prec(t_flags *data, char *tmp)
{
	int		len;
	int		ret;

	ft_putstr(tmp);
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
	data->total += ret + data->nbsize;
}

void	u_advanced_prec_fill(t_flags *data, char *tmp, long long nb)
{
	int		ret;
	int		zero;
	int		print;

	print = 0;
	if (nb == 0 && data->precision == 1 && data->preclen == 0)
		print = 1;
	if (data->fillen > data->preclen)
	{
		zero = data->preclen - data->nbsize;
		ret = print_char(zero, '0');
		if (print == 0)
			ft_putstr(tmp);
		zero = data->fillen - data->nbsize - ret;
		ret += print_char(zero + print, ' ');
		ret += data->nbsize;
	}
	else
		ret = u_preclen_is_upper(data, nb, 0);
	data->total += ret - print;
}

void	u_advanced_prec_space(t_flags *data, char *tmp, long long nb)
{
	int		ret;
	int		zero;
	int		print;

	print = 0;
	if (nb == 0 && data->precision == 1 && data->preclen == 0)
		print = 1;
	if (data->space > data->preclen)
	{
		zero = data->preclen - data->nbsize;
		ret = print_char(zero, '0');
		if (print == 0)
			ft_putstr(tmp);
		zero = data->space - data->nbsize - ret;
		ret += print_char(zero + print, ' ');
		ret += data->nbsize;
	}
	else
		ret = u_preclen_is_upper(data, nb, 0);
	data->total += ret - print;
}


void	advanced_unsigned_conv(t_flags *data, long long nb)
{
	char	*tmp;

	tmp = ft_long_itoa(nb);
	if (data->precision == 0)
	   u_advanced_no_prec(data, tmp);
	else if (data->precision == 1 && data->fill == 1 && data->space == 0)
		u_advanced_prec_fill(data, tmp, nb);
	else if (data->precision == 1 && data->fill == 0 && data->space > 0)
		u_advanced_prec_space(data, tmp, nb);
	free(tmp);
}

void	unsigned_conv(t_flags *data, va_list arg)
{
	(void)data;
	(void)arg;
	long long	nb;
	char		*tmp;

	nb = (unsigned int)va_arg(arg, unsigned int);
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
		u_with_prec(data, tmp, nb);
	free(tmp);
}
