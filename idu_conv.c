/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_conv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:41:36 by agirona           #+#    #+#             */
/*   Updated: 2021/02/15 18:08:44 by agirona          ###   ########lyon.fr   */
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

int		print_char(int len, char c)
{
	int		i;

	i = 0;
	while (i < len)
	{
		ft_putchar(c);
		i++;
	}
	return (i);
}

void	no_prec(t_flags *data, long long nb, int neg)
{
	int		len;
	int		ret;

	len = 0;
	if (data->fill == 1)
	{
		len = data->fillen - neg - ft_longlen(nb);
		if (neg == 1)
			ft_putchar('-');
		ret = print_char(len, '0');
	}
	else
	{
		len = data->space - neg - ft_longlen(nb);
		ret = print_char(len, ' ');
		if (neg == 1)
			ft_putchar('-');
	}
	ft_putnbr(nb);
	data->total += ret + neg + ft_longlen(nb);
}

void	fill_prec(t_flags *data, long long nb, int neg)
{
	int		space;
	int		zero;
	int		ret;

	if (data->fillen > data->preclen)
	{
		if (data->preclen > ft_longlen(nb))
			space = data->fillen - data->preclen - neg;
		else
			space = data->fillen - ft_longlen(nb) - neg;
		ret = print_char(space, ' ') + ft_longlen(nb) + neg;
		zero = ret;
		if (neg == 1)
			ft_putchar('-');
		ret += print_char(data->fillen - zero, '0');
		ft_putnbr(nb);
	}
	else
	{
		zero = data->preclen - ft_longlen(nb);
		if (neg == 1)
			ft_putchar('-');
		ret = print_char(zero, '0');
		ret += neg + ft_longlen(nb);
		ft_putnbr(nb);
	}
	data->total += ret;
}

void	space_prec(t_flags *data, long long nb, int neg)
{
	int		space;
	int		zero;
	int		ret;

	if (data->space > data->preclen)
	{
		if (data->preclen > ft_longlen(nb))
			space = data->space - data->preclen - neg;
		else
			space = data->space - ft_longlen(nb) - neg;
		ret = print_char(space, ' ') + ft_longlen(nb) + neg;
		zero = ret;
		if (neg == 1)
			ft_putchar('-');
		ret += print_char(data->space - zero, '0');
		ft_putnbr(nb);
	}
	else
	{
		zero = data->preclen - ft_longlen(nb);
		if (neg == 1)
			ft_putchar('-');
		ret = print_char(zero, '0');
		ret += neg + ft_longlen(nb);
		ft_putnbr(nb);
	}
	data->total += ret;
}

void	advanced_no_prec(t_flags *data, long long nb, int neg)
{
	int		space;
	int		ret;

	if (neg == 1)
		ft_putchar('-');
	ft_putnbr(nb);
	space = data->fillen - neg - ft_longlen(nb);
	ret = print_char(space, ' ');
	data->total += ret + neg + ft_longlen(nb);
}

void	advanced_fill_prec(t_flags *data, long long nb, int neg)
{
	int		ret;
	int		zero;

	ret = 0;
	zero = 0;
	if (data->fillen > data->preclen)
	{
		if (neg == 1)
			ft_putchar('-');
		zero = data->preclen - ft_longlen(nb);
		ret = print_char(zero, '0');
		ft_putnbr(nb);
		ret += print_char(data->fillen - ft_longlen(nb) - neg - ret, ' ');
	}
	else
	{
		if (neg == 1)
			ft_putchar('-');
		zero = data->preclen - ft_longlen(nb);
		ret = print_char(zero, '0');
		ft_putnbr(nb);
	}
	data->total += ret + ft_longlen(nb) + neg;;
}

void	advanded_space_prec(t_flags *data, long long nb, int neg)
{
	int		space;
	int		zero;
	int		ret;

	if (data->space > data->preclen)
	{
		if (neg == 1)
			ft_putchar('-');
		if (data->preclen > ft_longlen(nb))
			zero = data->preclen - ft_longlen(nb);
		else
			zero = 0;
		ret = print_char(zero, '0') + ft_longlen(nb) + neg;
		ft_putnbr(nb);
		space = ret;
		ret += print_char(data->space - space, ' ');
	}
	else
	{
		zero = data->preclen - ft_longlen(nb);
		if (neg == 1)
			ft_putchar('-');
		ret = print_char(zero, '0');
		ret += neg + ft_longlen(nb);
		ft_putnbr(nb);
	}
	data->total += ret;

}

void	advanced_int_conv(t_flags *data, long long nb, int neg)
{
	if (data->precision == 0)
		advanced_no_prec(data, nb, neg);
	else if (data->precision == 1 && data->fill == 1 && data->space == 0)
	  advanced_fill_prec(data, nb, neg);
	else if (data->precision == 1 && data->space > 0 && data->fill == 0)
	  advanded_space_prec(data, nb, neg);
}

void	int_conv(t_flags *data, va_list arg)
{
	long long	nb;
	int			neg;

	neg = 0;
	nb = va_arg(arg, int);
	if (nb < 0)
	{
		neg = 1;
		nb = ft_abs(nb);
	}
	if (data->align == 1)
		return (advanced_int_conv(data, nb, neg));
	if (data->precision == 0)
		no_prec(data, nb, neg);
	else if (data->precision == 1 && data->fill == 1 && data->space == 0)
		fill_prec(data, nb, neg);
	else if (data->precision == 1 && data->space > 0 && data->fill == 0)
		space_prec(data, nb, neg);
}

/*void	advanced_int_conv(t_flags *data, long long nb, int neg)
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
	}*/
