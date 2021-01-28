/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_conv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:39:04 by agirona           #+#    #+#             */
/*   Updated: 2021/01/28 14:32:52 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	string_conv(t_flags data, va_list arg)
{
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	tmp = va_arg(arg, char *);
	res = malloc(sizeof(char) * data.fillen + 1);
	while (i < data.fillen - (int)ft_strlen(tmp))
		res[i++] = (data.align == 1) ? ' ' : '0';
	res[i] = '\0';
	if (data.align == 1)
	{
		ft_putstr(tmp);
		ft_putstr(res);
	}
	else
	{
		ft_putstr(res);
		ft_putstr(tmp);
	}
	free(res);
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
