/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_conv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:39:04 by agirona           #+#    #+#             */
/*   Updated: 2021/02/02 17:17:17 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	char_conv(t_flags data, va_list arg)
{
	int		size;
	int		i;
	int		nb;

	size = (data.preclen > data.fillen) ? data.preclen : data.fillen;
	size = (data.space > size) ? data.space : size;
	i = 0;
	nb = va_arg(arg, int);
	if (data.align == 1)
		ft_putchar(nb);
	while (i < size - 1)
	{
		ft_putchar(' ');
		i++;
	}
	if (data.align == 0)
		ft_putchar(nb);
}

void	string_conv(t_flags data, va_list arg)
{
	int		i;
	int		c;
	char	*tmp;
	int		size;

	c = 0;
	tmp = va_arg(arg, char *);
	i = -1;
	size = (data.preclen > data.fillen) ? data.preclen : data.fillen;
	size = (data.space > size) ? data.space : size;
	if (data.space > 0 && data.precision == 1 && data.fill == 0)
		size = data.space;
	while (data.align == 1 && tmp[c] && c < size)
		ft_putchar(tmp[c++]);
	while (++i + (int)ft_strlen(tmp) < size)
		ft_putchar(' ');
	while (data.align == 0 && c + i < size)
		ft_putchar(tmp[c++]);
}

void	address_conv(t_flags data, va_list arg)
{
	int			i;
	int			size;
	uintptr_t	ptr;
	uintptr_t	cpy;

	i = 0;
	ptr = va_arg(arg, uintptr_t);
	cpy = ptr;
	size = (data.preclen > data.fillen) ? data.preclen : data.fillen;
	size = (data.space > size) ? data.space - 2 : size - 2;
	if (data.align == 1)
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
	if (data.align == 0)
	{
		ft_putstr("0x");
		ft_long_putnbr_base(ptr, "0123456789abcdef");
	}
}
