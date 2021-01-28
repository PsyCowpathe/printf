/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:50:19 by agirona           #+#    #+#             */
/*   Updated: 2021/01/28 15:46:07 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>
#include <limits.h>

void	print_struct(t_flags data)
{
	ft_putstr("Primary = ");
	ft_putchar(data.primary);	
	ft_putchar('\n');
	ft_putstr("Alignement = ");
	ft_putnbr(data.align);
	ft_putchar('\n');
	ft_putstr("Remplissage = ");
	ft_putnbr(data.fill);
	ft_putstr(" Len = ");
	ft_putnbr(data.fillen);
	ft_putchar('\n');
	ft_putstr("Precision = ");
	ft_putnbr(data.precision);
	ft_putstr(" Len = ");
	ft_putnbr(data.preclen);
	ft_putchar('\n');
	ft_putstr("Taille = ");
	ft_putnbr(data.size);
	ft_putstr(" Len = ");
	ft_putnbr(data.width);
	ft_putchar('\n');
	ft_putchar('\n');
}

void	ft_printf(const char *str, ...)
{
	va_list		arg;
	t_flags		data;

	if (flags_init(&data.primlist, "cspdiuxX%", &data.seclist, "-0.*") == 0)
		return ;
	va_start(arg, str);
	data.form = (char *)str;
	if (cut_flags(data, arg) == 0)
		return ;
}

int		main(int argc, char **argv)
{
	(void)argc;
	ft_printf(argv[1], 10, 156);
	printf(argv[1], 10, 156);
	ft_putchar('\n');
}
