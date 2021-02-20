/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:31:43 by agirona           #+#    #+#             */
/*   Updated: 2021/02/20 15:42:02 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>

int		hex_size(unsigned int nb)
{
	int		i;

	i = 0;
	if (nb < 0)
		nb = 4294967295 - nb;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 16;
		i++;
	}
	return (i);
}

void	print_hex(long long nb, char c)
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
	if (nb == 0 && data->precision == 1 && data->preclen == 0)
		i--;
	else
		print_hex(nb, data->primary);
	while (i < size)
	{
		ft_putchar(' ');
		i++;
	}
	data->total += i + hex_size(nb);
}

int		pre_hex(t_flags *data, int *size, int *i)
{
	int		nb;

	nb = (unsigned int)va_arg(data->arg, unsigned int);
	*size = (data->preclen > data->fillen) ? data->preclen : data->fillen;
	*size = (data->space > *size) ? data->space : *size;
	*size -= hex_size(nb);
	if (nb == 0 && data->precision == 1 && data->preclen == 0)
		*i -= 1;
	return (nb);
}

void	hex_conv(t_flags *data)
{
	unsigned int	nb;
	int				i;
	int				size;

	i = 0;
	nb = pre_hex(data, &size, &i);
	if (data->align == 1)
		return (advanced_hex_conv(data, size, nb));
	while (i < size)
	{
		if (data->fill == 1 && data->preclen < 0
		&& i <= data->fillen - data->preclen)
			ft_putchar('0');
		else if ((data->precision == 1 && i < data->fillen - data->preclen)
		|| i < data->space - data->preclen)
			ft_putchar(' ');
		else
			ft_putchar('0');
		i++;
	}
	data->total += i + hex_size(nb);
	if (!(nb == 0 && data->precision == 1 && data->preclen == 0))
		print_hex(nb, data->primary);
}
