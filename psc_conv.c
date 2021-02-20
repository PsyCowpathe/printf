/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psc_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:39:04 by agirona           #+#    #+#             */
/*   Updated: 2021/02/20 15:41:57 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		char_conv(t_flags *data)
{
	int		size;
	int		i;
	int		nb;

	size = (data->preclen > data->fillen) ? data->preclen : data->fillen;
	size = (data->space > size) ? data->space : size;
	i = 0;
	nb = va_arg(data->arg, int);
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

int			pre_string(t_flags *data, char *str, int *word, int *space)
{
	int		c;

	c = 0;
	*space = (data->fillen > data->space) ? data->fillen : data->space;
	*word = ft_strlen(str);
	if (data->precision == 1 && data->preclen >= 0 && data->preclen < *word)
		*word = data->preclen;
	*space = *space - *word;
	if (data->noprim == 1 && data->align == 1)
	{
		data->total++;
		ft_putchar('%');
	}
	while (data->align == 1 && c < *word)
		ft_putchar(str[c++]);
	return (c);
}

void		string_conv(t_flags *data, char *str)
{
	int		word;
	int		space;
	int		i;
	int		c;

	if (str == NULL)
		return (string_conv(data, "(null)"));
	i = 0;
	c = pre_string(data, str, &word, &space);
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
		ft_putchar(str[c++]);
	data->total += i + c + data->noprim;
}

long long	pre_address(t_flags *data, int *size, long long *cpy)
{
	long long	ptr;

	ptr = (unsigned long long)va_arg(data->arg, unsigned long long);
	*cpy = ptr;
	*size = (data->preclen > data->fillen) ? data->preclen : data->fillen;
	*size = (data->space > *size) ? data->space - 2 : *size - 2;
	if (data->align == 1)
	{
		ft_putstr("0x");
		data->total += 2;
		ft_llong_putnbr_base(ptr, "0123456789abcdef");
	}
	if (*cpy == LONG_MIN)
		*cpy = LONG_MAX;
	if (*cpy == -1)
	{
		data->total += 16;
		*size -= 16;
	}
	if (ptr == 0)
	{
		*size -= 1;
		data->total++;
	}
	return (ptr);
}

void		address_conv(t_flags *data)
{
	int			i;
	int			size;
	long long	ptr;
	long long	cpy;

	i = 0;
	ptr = pre_address(data, &size, &cpy);
	while (cpy > 0)
	{
		cpy /= 16;
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
