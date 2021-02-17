/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psc_conv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:39:04 by agirona           #+#    #+#             */
/*   Updated: 2021/02/17 18:02:06 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	char_conv(t_flags *data, va_list arg)
{
	int		size;
	int		i;
	int		nb;

	size = (data->preclen > data->fillen) ? data->preclen : data->fillen;
	size = (data->space > size) ? data->space : size;
	i = 0;
	nb = va_arg(arg, int);
	if (data->align == 1)
	{
		ft_putchar(nb);
		data->total++;
	}
	while (i < size - 1)
	{
		ft_putchar(' ');
		i++;
	}
	if (data->align == 0)
	{
		ft_putchar(nb);
		data->total++;
	}
	data->total += i;
}

void	string_conv(t_flags *data, char *str)
{
	int		word;
	int		space;
	int		i;
	int		c;

	if (str == NULL)
		return (string_conv(data, "(null)"));
	space = (data->fillen > data->space) ? data->fillen : data->space;
	word = ft_strlen(str);
	i = 0;
	c = 0;
	if (data->precision == 1 && data->preclen >= 0 && data->preclen < word)
		word = data->preclen;
	space = space - word;
	if (data->noprim == 1 && data->align == 1)
	{
		data->total++;
		ft_putchar('%');
	}
	while (data->align == 1 && c < word)
	{
		ft_putchar(str[c++]);
	}
	while (i + data->noprim < space)
	{
		if (data->fill == 1)
			ft_putchar('0');
		else
			ft_putchar(' ');
		i++;
	}
	if (data->noprim == 1 && data->align == 0)
	{
		data->total++;
		ft_putchar('%');
	}
	while (data->align == 0 && c < word)
	{
		ft_putchar(str[c++]);
	}
	data->total += i + c + data->noprim;
}


/*void	string_conv(t_flags *data, char *str)
{
	int		i;
	int		c;
	int		space;
	int		slen;

	c = 0;
	if (str == NULL)
		return (string_conv(data, "(null)"));
	i = -1;
	space = (data->space > data->fillen) ? data->space : data->fillen;
	//space = (data->space > space) ? data->space : space;
	slen = (data->precision == 1) ? data->preclen : ft_strlen(str);
	slen = (data->preclen < 0) ? ft_strlen(str) : slen;
	if (data->space > 0 && data->space >= data->preclen && slen > (int)ft_strlen(str))
	{
		space += slen - ft_strlen(str);
	}
	space -= slen;
	if (data->align == 1)
	{
		while (str[c] && c < slen)
		{
			ft_putchar(str[c]);
			c++;
		}
	}
	if (data->noprim == 1)
	{
		if (data->align == 1)
			ft_putchar('%');
		data->total++;
		i++;
	}
	while (++i < data->space - (int)ft_strlen(str))
	{
		ft_putchar((data->fill == 1 ) ? '0' : ' ');
	}
	if (data->noprim == 1 && data->align == 0)
		ft_putchar('%');
	if (data->align == 0)
	{
		while (str[c] && c < slen)
		{
			ft_putchar(str[c]);
			c++;
		}
	}
	data->total += i + c;
}*/

#include <stdio.h>

void	address_conv(t_flags *data, va_list arg)
{
	int			i;
	int			size;
	long long	ptr;
	long long	cpy;

	i = 0;
	ptr = (unsigned long long)va_arg(arg, unsigned long long);
	cpy = ptr;
	size = (data->preclen > data->fillen) ? data->preclen : data->fillen;
	size = (data->space > size) ? data->space - 2 : size - 2;
	if (data->align == 1)
	{
		ft_putstr("0x");
		data->total += 2;
		ft_llong_putnbr_base(ptr, "0123456789abcdef");
	}
	if (cpy == LONG_MIN)
		cpy = LONG_MAX;
	if (cpy == -1)
	{
		data->total += 16;
		size -= 16;
	}
	while (cpy > 0)
	{
		cpy /= 16;
		size--;
		data->total++;
	}
	if (ptr == 0)
	{
		size--;
		data->total++;
	}
	while (i++ < size)
		ft_putchar(' ');
	if (data->align == 0)
	{
		ft_putstr("0x");
		data->total += 2;
		ft_llong_putnbr_base(ptr, "0123456789abcdef");
	}
	data->total += i - 1;
}
