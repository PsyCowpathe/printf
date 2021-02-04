/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:31:43 by agirona           #+#    #+#             */
/*   Updated: 2021/02/04 12:37:20 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		hex_size(unsigned int nb)
{
	int		i;

	i = 0;
	if (nb < 0)
		nb = 4294967295 - nb;
	while (nb > 0)
	{
		nb = nb / 16;
		i++;
	}
	return (i);
}

void	print_hex(unsigned int nb, char c)
{
	if (c == 'X')
		ft_long_putnbr_base(nb, "0123456789ABCDEF");
	else
		ft_long_putnbr_base(nb, "0123456789abcdef");
}

void	advanced_hex_conv(t_flags *data, int size, unsigned int nb)
{
	int		i;

	i = 0;
	while (i < data->preclen - hex_size(nb))
	{
		ft_putchar('0');
		i++;
	}
	print_hex(nb, data->primary);
	while (i < size)
	{
		ft_putchar(' ');
		i++;
	}
}

void	hex_conv(t_flags *data, va_list arg)
{
	unsigned int	nb;
	int				i;
	int				size;

	i = 0;
	nb = (unsigned int)va_arg(arg, unsigned int);
	size = (data->preclen > data->fillen) ? data->preclen : data->fillen;
	size = (data->space > size) ? data->space : size;
	data->total += size;
	size -= hex_size(nb);
	if (data->align == 1)
		return (advanced_hex_conv(data, size, nb));
	while (i < size)
	{
		if ((data->precision == 1 && i < data->fillen - data->preclen)
		|| i < data->space - data->preclen)
			ft_putchar(' ');
		else
			ft_putchar('0');
		i++;
	}
	print_hex(nb, data->primary);
}
