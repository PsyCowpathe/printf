/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:50:19 by agirona           #+#    #+#             */
/*   Updated: 2021/01/26 14:09:04 by agirona          ###   ########lyon.fr   */
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
	ft_printf(argv[1], "salut");
	printf(argv[1], "salut");
	ft_putchar('\n');
}
