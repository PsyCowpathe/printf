/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_conv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:39:04 by agirona           #+#    #+#             */
/*   Updated: 2021/01/26 16:37:43 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		hex_size(int nb)
{
	int		i;

	i = 0;
	while (nb > 0)
	{
		nb = nb / 16;
		i++;
	}
	return (i);
}

void	hex_conv(t_flags data, va_list arg)
{
	int		nb;
	int		i;
	int		size;

	i = 0;
	nb = va_arg(arg, int);
	size = (data.fillen > data.preclen) ? data.fillen : data.preclen;
	if (data.fill == 1 && data.precision == 1)
	{
		while (i++ < data.fillen - data.preclen)
			ft_putchar(' ');
		i = (i - 1) + hex_size(nb);
		while (i++ < size)
			ft_putchar('0');
	}
	else
	{
		size = hex_size(nb);
		while (i++ < data.fillen - size || i < data.preclen - size)
			ft_putchar('0');
	}
	if (data.primary == 'X')
		ft_putnbr_base(nb, "0123456789ABCDEF");
	else
		ft_putnbr_base(nb, "0123456789abcdef");
}

void	advanced_address_conv(t_flags data, va_list arg, uintptr_t ptr)
{
	(void)data;
	(void)arg;
	(void)ptr;
	int		i;

	i = 0;
	ft_putstr("0x");
	while (i < data.preclen - 9)
	{
		ft_putchar('0');
		i++;
	}
	ft_long_putnbr_base(ptr, "0123456789abcdef");
	while (i < data.fillen - 9 - 2)
	{
		ft_putchar(' ');
		i++;
	}
}

void	address_conv(t_flags data, va_list arg)
{
	uintptr_t	ptr;
	int			i;

	i = 0;
	ptr = va_arg(arg, uintptr_t);
	if (data.align == 1)
	{
		advanced_address_conv(data, arg, ptr);
		return ;
	}
	if (data.fill == 1 && data.precision == 1 && data.preclen >= 9)
		while (i++ < data.fillen - data.preclen - 2)
			ft_putchar(' ');
	else if (data.fill == 1 && data.precision == 1)
		while (i++ < data.fillen - 9 - 2)
			ft_putchar(' ');
	if (data.fill == 1 && data.precision == 1)
		i--;
	ft_putstr("0x");
	while (i++ < data.preclen - 9)
		ft_putchar('0');
	i--;
	while (i++ < data.fillen - 9 - 2)
		ft_putchar('0');
	ft_long_putnbr_base(ptr, "0123456789abcdef");
	return ;
}
