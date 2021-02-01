/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_conv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:41:36 by agirona           #+#    #+#             */
/*   Updated: 2021/02/01 17:49:54 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	advanced_unsign_conv(t_flags data, int size, unsigned int nb)
{
	int		i;

	i = 0;
	while (i < data.preclen - ft_nblen(nb))
	{
		ft_putchar('0');
		i++;
	}
	ft_putstr(ft_long_itoa(nb));
	while (i < size)
	{
		ft_putchar(' ');
		i++;
	}
}

void	unsigned_conv(t_flags data, va_list arg)
{
	int				size;
	int				i;
	unsigned int	nb;

	nb = (unsigned int)va_arg(arg, unsigned int);
	size = (data.preclen > data.fillen) ? data.preclen : data.fillen;
	size = (data.space > size) ? data.space : size;
	size -= ft_nblen(nb);
	i = 0;
	if (data.align == 1)
		return (advanced_unsign_conv(data, size, nb));
	while (i < size)
	{
		if ((data.precision == 1 && i < data.fillen - data.preclen)
		|| i < data.space - data.preclen)
			ft_putchar(' ');
		else
			ft_putchar('0');
		i++;
	}
	ft_putstr(ft_long_itoa(nb));
}

void	advanced_int_conv(t_flags data, int size, int nb)
{
	int		i;

	i = 0;
	while (i < data.preclen - ft_nblen(nb))
	{
		ft_putchar('0');
		i++;
	}
	ft_putnbr(nb);
	while (i < size)
	{
		ft_putchar(' ');
		i++;
	}
}

void	int_conv(t_flags data, va_list arg)
{
	int		size;
	int		i;
	int		nb;

	nb = (int)va_arg(arg, int);
	i = 0;
	size = (data.preclen > data.fillen) ? data.preclen : data.fillen;
	size = (data.space > size) ? data.space : size;
	size -= ft_nblen(nb);
	if (nb < 0)
		size--;
	if (data.align == 1)
		return (advanced_int_conv(data, size, nb));
	while (i < size)
	{
		if ((data.precision == 1 && i < data.fillen - data.preclen)
				|| i < data.space - data.preclen)
			ft_putchar(' ');
		else
			ft_putchar('0');
		i++;	
	}
	ft_putnbr(nb);
}
