/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:31:43 by agirona           #+#    #+#             */
/*   Updated: 2021/01/28 15:46:06 by agirona          ###   ########lyon.fr   */
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

void	print_hex(int nb, char c)
{
	if (c == 'X')
		ft_putnbr_base(nb, "0123456789ABCDEF");
	else
		ft_putnbr_base(nb, "0123456789abcdef");

}

void	advanced_hex_conv(t_flags data, int nb)
{
	int		i;
	int		size;

	size = (data.fillen > data.preclen) ? data.fillen : data.preclen;
	if (data.fill == 1 && data.precision == 0)
		print_hex(nb, data.primary);
	i = hex_size(nb) - 1;
	if (data.fillen > data.preclen)
	{
		while (++i < data.preclen)
			ft_putchar('0');
		if (data.fill == 1 && data.precision == 1)
			print_hex(nb, data.primary);
		while (i++ < data.fillen)
			ft_putchar(' ');
	}
	else
	{
		while (++i < size)
			ft_putchar((data.fillen > data.preclen) ? ' ' : '0');
		if (!(data.fill == 1 && data.precision == 0))
			print_hex(nb, data.primary);
	}
}

void	hex_conv(t_flags data, va_list arg)
{
	int		i;
	int		size;
	int		nb;
	int		wich;

	nb = va_arg(arg, int);
	i = hex_size(nb);
	size = (data.fillen > data.preclen) ? data.fillen : data.preclen;
	wich = data.fillen - (data.preclen - hex_size(nb));
	if (data.align == 1)
	{
		advanced_hex_conv(data, nb);
		return ;
	}
	while (i < size)
	{
		if (data.fill == 1 && data.precision == 0)
			ft_putchar('0');
		else
			ft_putchar((i < wich) ? ' ' : '0');
		i++;
	}
	if (data.primary == 'X')
		ft_putnbr_base(nb, "0123456789ABCDEF");
	else
		ft_putnbr_base(nb, "0123456789abcdef");
}

