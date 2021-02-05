/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_conv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:41:36 by agirona           #+#    #+#             */
/*   Updated: 2021/02/05 16:49:51 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	advanced_unsign_conv(t_flags *data, int size, unsigned int nb)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < data->preclen - ft_longlen(nb))
	{
		ft_putchar('0');
		i++;
	}
	tmp = ft_long_itoa(nb);
	ft_putstr(tmp);
	while (i < size)
	{
		ft_putchar(' ');
		i++;
	}
	free(tmp);
}

void	unsigned_conv(t_flags *data, va_list arg)
{
	int				size;
	int				i;
	unsigned int	nb;
	char			*tmp;

	nb = (unsigned int)va_arg(arg, unsigned int);
	size = (data->preclen > data->fillen) ? data->preclen : data->fillen;
	size = (data->space > size) ? data->space : size;
	size -= ft_longlen(nb);
	i = 0;
	if (data->align == 1)
		return (advanced_unsign_conv(data, size, nb));
	while (i < size)
	{
		if ((data->precision == 1 && i < data->fillen - data->preclen)
		|| i < data->space - data->preclen)
			ft_putchar(' ');
		else
			ft_putchar('0');
		i++;
	}
	tmp = ft_long_itoa(nb);
	ft_putstr(tmp);
	free(tmp);
}

void	advanced_int_conv(t_flags *data, int size, int nb)
{
	int		i;
	int		max;

	//ft_putstr("advanced");
	i = 0;
	max = data->preclen - ft_longlen(nb);
	while (i < max)
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
	data->total += i + ft_longlen(nb);
}

/*void	int_conv(t_flags *data, va_list arg)
{
	int		size;
	int		i;
	int		nb;

	nb = (int)va_arg(arg, int);
	if (data->precision == 1 && data->preclen == 0)
		return ;
	i = 0;
	size = (data->preclen > data->fillen) ? data->preclen : data->fillen;
	size = (data->space > size) ? data->space : size;
	size -= ft_longlen(nb);
	if (nb < 0)
	{
		ft_putchar('-');
		nb = ft_abs(nb);
		data->total++;
	}
	if (data->align == 1)
		return (advanced_int_conv(data, size, nb));
	while (i < size)
	{
		if ((data->precision == 1 && i < data->fillen - data->preclen)
		|| i < data->space - data->preclen)
			ft_putchar(' ');
		else
			ft_putchar('0');
		i++;	
	}
	ft_putnbr(nb);
	data->total += i + ft_longlen(nb);
}*/

/*void	int_conv(t_flags *data, va_list arg)
{
	int		i;
	int		size;
	int		nb;
	int		neg;

	i = 0;
	neg = 0;
	if ((nb = (int)va_arg(arg, int)) < 0)
	{
		nb = ft_abs(nb);
		neg = 1;
	}
	size = (data->preclen > data->fillen) ? data->preclen : data->fillen;
	size = (data->space > size) ? data->space : size;
	size = size - ft_longlen(nb);
	if (data->align == 1)
		return (advanced_int_conv(data, size, nb));
	if (data->fillen > data->preclen)
		size--;
	while (i < (data->fillen - data->preclen) - neg)
	{
		ft_putchar(' ');
		i++;
	}
	while (i < (data->preclen - data->fillen) - neg)
	{
		ft_putchar(' ');
		i++;
	}
	if (neg == 1)
		ft_putchar('-');
	while (i < size)
	{
		ft_putchar('0');
		i++;
	}
	if (data->precision == 1 && data->preclen == 0 && nb == 0)
		data->total--;
	else
		ft_putnbr(nb);
	data->total += i + ft_longlen(nb) + neg;
}*/

void	int_conv(t_flags *data, va_list arg)
{
	int		i;
	int		size;
	int		nb;
	int		neg;

	i = 0;
	neg = 0;
	nb = (int)va_arg(arg, int);
	if (nb < 0)
	{
		nb = ft_abs(nb);
		neg = 1;
	}
	size = (data->preclen > data->fillen) ? data->preclen : data->fillen;
	size = (data->space > size) ? data->space : size;
	size = size - ft_longlen(nb) - neg;
	if (data->precision == 1 && data->fill == 0 && data->space > 0)
	{
		if (neg == 1 && data->space <= data->preclen)
			size++;
		while (i < size)
		{
			if (i < data->space - data->preclen - neg)
				ft_putchar(' ');
			else
			{
				if (--neg == 0)
					ft_putchar('-');
				ft_putchar('0');
			}
			i++;
		}
	}
	if (data->precision == 1 && data->fill == 1 && data->space == 0)
	{
		if (neg == 1 && data->preclen >= data->fillen)
			size++;
		while (i < size)
		{
			if (i < data->fillen - data->preclen - neg)
				ft_putchar(' ');
			else
			{
				if (--neg == 0)
					ft_putchar('-');
				ft_putchar('0');
			}
			i++;
		}
	}
	ft_putnbr(nb);
	/*
	if (data->prec == 0 && data->fill == 1 && data->space > 0)
	if (data->prec == 0 && data->fill == 1 && data->space == 0)
	if (data->prec == 1 && data->fill == 0 && data->space == 0)
	if (data->prec == 0 && data->fill == 0 && data->space > 0)*/

}

#include <stdio.h>
#include <limits.h>

void	mainprintf()
{
	int		ret;
	int		nb;
	char	param[] = "%020.10i";
	nb = 1;

	ft_putstr("Moi = ");
	ret = ft_printf(param, 1011);
	ft_putstr("| retour = ");
	ft_putnbr(ret);
	ft_putchar('\n');
	ft_putstr("Lui = ");
	ret = dprintf(1, param, 1011);
	ft_putstr("| retour = ");
	ft_putnbr(ret);
}

int		main(void)
{
	mainprintf();
	//while (1);
	return (1);
}

