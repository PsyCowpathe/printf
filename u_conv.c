/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_conv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:41:36 by agirona           #+#    #+#             */
/*   Updated: 2021/02/17 13:21:00 by agirona          ###   ########lyon.fr   */
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
