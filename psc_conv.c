/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psc_conv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:39:04 by agirona           #+#    #+#             */
/*   Updated: 2021/02/08 17:47:51 by agirona          ###   ########lyon.fr   */
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
	int		i;
	int		c;
	int		space;
	int		slen;

	c = 0;
	if (str == NULL)
		return (string_conv(data, "(null)"));
	i = -1;
	space = (data->preclen > data->fillen) ? data->preclen : data->fillen;
	space = (data->space > space) ? data->space : space;
	slen = (data->precision == 1) ? data->preclen : ft_strlen(str);
	slen = (data->preclen < 0) ? ft_strlen(str) : slen;
	if (data->space > 0 && slen > (int)ft_strlen(str))
		space += slen - ft_strlen(str);
	space -= slen;
	if (data->align == 1)
	{
		while (str[c] && c < slen)
		{
			ft_putchar(str[c]);
			c++;
		}
	}
	while (++i < space)
		ft_putchar(' ');
	if (data->align == 0)
	{
		while (str[c] && c < slen)
		{
			ft_putchar(str[c]);
			c++;
		}
	}
	data->total += i + c;
}

void	address_conv(t_flags *data, va_list arg)
{
	int			i;
	int			size;
	uintptr_t	ptr;
	uintptr_t	cpy;

	i = 0;
	ptr = va_arg(arg, uintptr_t);
	cpy = ptr;
	size = (data->preclen > data->fillen) ? data->preclen : data->fillen;
	size = (data->space > size) ? data->space - 2 : size - 2;
	data->total += size + 2;
	if (data->align == 1)
	{
		ft_putstr("0x");
		ft_long_putnbr_base(ptr, "0123456789abcdef");
	}
	while (cpy > 0)
	{
		cpy /= 16;
		size--;
	}
	while (i++ < size)
		ft_putchar(' ');
	if (data->align == 0)
	{
		ft_putstr("0x");
		ft_long_putnbr_base(ptr, "0123456789abcdef");
	}
}
