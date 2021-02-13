/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_conv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:41:36 by agirona           #+#    #+#             */
/*   Updated: 2021/02/13 17:09:12 by agirona          ###   ########lyon.fr   */
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
			size = data->space - ft_longlen(nb);
		ft_putstr(tmp);
		while (++i < size)
			ft_putchar(' ');
	}
	else
	{
		while (++i < size)
		{
			if (i < data->preclen - ft_longlen(nb))
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
	data->total += i + ft_longlen(nb);
	if (nb == 0 && data->space == 0 && data->precision == 1 && data->preclen == 0 && data->fill == 0)
		data->total--;
	free(tmp);
}

void	unsigned_conv(t_flags *data, va_list arg)
{
	int			i;
	int			size;
	int			print;
	long long	nb;
	char		*tmp;

	i = 0;
	print = 1;
	nb = (unsigned int)va_arg(arg, unsigned int);
		size = (data->preclen > data->fillen) ? data->preclen : data->fillen;
	size = (data->space > size) ? data->space : size;
	size = size - ft_longlen(nb);
	if (data->align == 1)
		return (advanced_unsign_conv(data, size, nb));
	tmp = ft_long_itoa(nb);
	if ((data->precision == 1 && data->fill == 0 && data->space > 0)
	|| (data->precision == 1 && data->fill == 1 && data->space == 0))
	{
		if (nb == 0 && data->preclen == 0)
		{
			print = 0;
			i--;
		}
		while (i < size)
		{
			if (data->fill == 1 && data->preclen < 0 && i <= data->fillen - data->preclen)
				ft_putchar('0');
			else if ((data->space > 0 && i < data->space - data->preclen) 
			|| (data->fill == 1 && i < data->fillen - data->preclen))
				ft_putchar(' ');
			else
				ft_putchar('0');
			i++;
		}
	}
	if ((data->precision == 0 && data->fill == 1 && data->space == 0)
	|| (data->precision == 1 && data->fill == 0 && data->space == 0))
	{
		if (data->precision == 1 && data->fill == 0 && data->space == 0)
			if (data->preclen == 0 && nb == 0)
			{
				free(tmp);
				return ;
			}
		while (i < size)
		{
			ft_putchar('0');
			i++;
		}
	}
	if (data->precision == 0 && data->fill == 0 && data->space > 0)
		while (i < size)
		{
			ft_putchar(' ');
			i++;
		}
	if (print == 1)
		ft_putstr(tmp);
	if (i == -1)
		i++;
	if (data->precision == 1 && data->fill == 1 && data->preclen == 0 && data->fillen == 0 && nb == 0)
		data->total--;
	data->total += i + ft_longlen(nb);
	free(tmp);
}

/*void	advanced_int_conv(t_flags *data, int size, int nb, int neg)
{
	int		i;
	int		print;

	i = -1;
	print = 1;
	if (neg == 1)
		ft_putchar('-');
	if (nb == 0 && data->preclen == 0)
	{
		i--;
		print = 0;
	}
	if (data->precision == 1 && data->fill == 0 && data->space == 0)
	{
		if (neg == 1)
			size++;
		while (++i < size)
			ft_putchar('0');
		if (print == 1)
			ft_putnbr(ft_abs(nb));
		if (nb < 0)
			data->total--;
	}
	else if (data->precision == 0 && data->fill == 1 && data->space > 0)
	{
		if (data->space < data->fillen)
			size = data->space - ft_longlen(nb) - neg;
		ft_putnbr(nb);
		while (++i < size)
			ft_putchar(' ');
	}
	else
	{
		if ((neg == 1 && data->space > 0 && data->preclen >= data->space)
		|| (neg == 1 && data->fill == 1 && data->preclen >= data->fillen))
				size++;
		while (++i < size)
		{
			if (i < data->preclen - ft_longlen(nb))
				ft_putchar('0');
			else
			{
				if (--print == 0)
					ft_putnbr(nb);
				ft_putchar(' ');
			}
		}
		if (print == 1 || (data->fill == 1 && data->precision == 0 && data->space == 0) || (data->fill == 0 && data->precision == 0 && data->space == 0) || ((data->fill == 0 && data->precision == 0 && data->space > 0)))
			ft_putnbr(ft_abs(nb));
	}
	if (i == -1)
		i++;
	data->total += i + ft_longlen(nb);
}*/

/*void	int_conv(t_flags *data, va_list arg)
{
	int			i;
	int			size;
	int			print;
	long long	nb;
	int			neg;

	i = -1;
	print = 1;
	neg = 0;
	nb = (int)va_arg(arg, int);
	if (nb < 0 && ++neg && ++data->total)
		nb = ft_abs(nb);
	size = (data->preclen > data->fillen) ? data->preclen : data->fillen;
	size = (data->space > size) ? data->space : size;
	size = size - ft_longlen(nb) - neg;
	if (data->align == 1)
		return (advanced_int_conv(data, size, nb, neg));
	if ((data->precision == 1 && data->fill == 0 && data->space > 0)
	|| (data->precision == 1 && data->fill == 1 && data->space == 0))
	{
		if (nb == 0 && data->preclen == 0)
		{
			print = 0;
			i--;
		}
		if ((neg == 1 && data->space > 0 && data->space <= data->preclen)
		|| (neg == 1 && data->fill == 1 && data->preclen >= data->fillen))
			size++;
		while (++i < size)
		{
			if ((data->space > 0 && i < data->space - data->preclen - neg) 
			|| (data->fill == 1 && i < data->fillen - data->preclen - neg))
				ft_putchar(' ');
			else
			{
				if (--neg == 0)
					ft_putchar('-');
				ft_putchar('0');
			}
		}
	}
	if ((data->precision == 0 && data->fill == 1 && data->space == 0)
	|| (data->precision == 1 && data->fill == 0 && data->space == 0))
	{
		if (data->precision == 0 && data->fill == 1 && data->space == 0
		&& neg-- == 1)
			ft_putchar('-');
		if (data->precision == 1 && data->fill == 0 && data->space == 0)
		{
			if (data->preclen == 0 && nb == 0)
				return ;
			if (neg == 1)
				size++;
			if (neg-- == 1)
				ft_putchar('-');
		}
		while (++i < size)
			ft_putchar('0');
	}
	if (data->precision == 0 && data->fill == 0 && data->space > 0)
		while (++i < size)
			ft_putchar(' ');
	if (neg == 1)
		ft_putchar('-');
	if (print == 1)
		ft_putnbr(nb);
	if (i == -1)
		i++;
	data->total += i + ft_longlen(nb);
	if (nb == 0 && data->precision == 1 && data->preclen == 0 && data->space == 0 && data->fillen == 0)
		data->total -= ft_longlen(nb);
}*/

void	advanced_int_conv(t_flags *data, long long nb, int neg)
{
	int		i;
	int		space;
	int		size;
	int		print;

	i = 0;
	print = 1;
	size = (data->space > data->fillen) ? data->space : data->fillen;
	space = size;
	if (data->preclen >= size)
		size = data->preclen + neg;
	if (nb == 0 && data->precision == 1 && data->preclen == 0)
		size++;
	if (neg == 1)
		ft_putchar('-');
	//print_struct(*data);
	if (data->precision == 0 || (data->space > 0 && data->precision == 1 && data->preclen <= 0)
	|| (data->fill == 1 && data->precision == 1 && data->preclen <= 0)
	|| (data->precision == 1 && data->preclen == 1 && data->space == 3))
	{
		if (!(data->preclen == 0 && data->precision == 1 && nb == 0))	
			ft_putnbr(nb);
		else
			data->total--;
		print = 0;
	}
	while (i < size - ft_longlen(nb) - neg)
	{
		if (print == 1 && (i == data->preclen - ft_longlen(nb) || (data->preclen == 1 && i <= data->preclen - neg)))
		{
			ft_putnbr(nb);
			print = 0;
		}
		if (i < data->preclen - ft_longlen(nb))
			ft_putchar('0');
		else
			ft_putchar(' ');
		i++;
	}
	if (print == 1 && !(nb == 0 && data->precision == 1 && data->preclen == 0))
		ft_putnbr(nb);
	else if (print == 1)
		data->total--;
	data->total += i + neg + ft_longlen(nb);
}

void	int_conv(t_flags *data, va_list arg)
{
	int			i;
	long long	nb;
	int			size;
	int			neg;
	int			space;
	int			print;

	i = 0;
	neg = 0;
	print = 0;
	nb = (int)va_arg(arg, int);
	if (nb < 0)
	{
		nb = ft_abs(nb);
		neg = 1;
	}
	if (data->align == 1)
		return (advanced_int_conv(data, nb, neg));
	size = (data->space > data->fillen) ? data->space : data->fillen;
	space = size;
	if (data->preclen >= size)
		size = data->preclen + neg;
	if (nb == 0 && data->precision == 1 && data->preclen == 0)
		i--;
	if (data->precision == 0 && data->space == 0 && neg == 1)
	{
		ft_putchar('-');
		print = 1;
	}
	while (i < size - ft_longlen(nb) - neg)
	{
		if (neg == 1 && (i == size - data->preclen - neg
		|| (data->fill == 1 && data->preclen < 0 && i <= data->fillen - data->preclen)))
		{
			print = 1;
			ft_putchar('-');
		}
		if (data->fill == 1 && data->preclen < 0 && i <= data->fillen - data->preclen)
			ft_putchar('0');
		else if ((data->precision == 1 || data->fill == 0) && i < size - data->preclen - neg)
			ft_putchar(' ');
		else
			ft_putchar('0');
		i++;
	}
	if (print == 0 && neg == 1)
		ft_putchar('-');
	if (!(nb == 0 && data->precision == 1 && data->preclen == 0))
		ft_putnbr(nb);
	data->total += i + neg + ft_longlen(nb);
}
