/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:50:19 by agirona           #+#    #+#             */
/*   Updated: 2021/02/02 17:17:17 by agirona          ###   ########lyon.fr   */
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
	(void)argv;

	int		nb = 's';

	ft_putstr("***1*** espace");
	ft_putchar('\n');
	ft_printf("20%20c%%%%", nb);
	ft_putchar('\n');
	dprintf(1, "20%20c%%%%", nb);
	ft_putchar('\n');
	ft_putchar('\n');
	/*ft_putstr("***2*** espace + retourner");
	ft_putchar('\n');
	ft_printf("20%-25c", nb); 	ft_putchar('\n');
	dprintf(1, "20%-25c", nb);
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putstr("***3*** precision");
	ft_putchar('\n');
	ft_printf("20%.3c", nb); 
	ft_putchar('\n');
	dprintf(1, "20%.3c", nb);
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putstr("***4*** precision + retourner");
	ft_putchar('\n');
	ft_printf("20%-.3c", nb); 	
	ft_putchar('\n');
	dprintf(1, "20%-.3c", nb);
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putstr("***5*** fill");
	ft_putchar('\n');
	ft_printf("20%03c", nb); 
	ft_putchar('\n');
	dprintf(1, "20%03c", nb);
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putstr("***6*** fill + precision egal");
	ft_putchar('\n');
	ft_printf("20%05.5c", nb); 
	ft_putchar('\n');
	dprintf(1, "20%05.5c", nb);
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putstr("***7*** fill + precision inferieur");
	ft_putchar('\n');
	ft_printf("20%010.5c", nb); 
	ft_putchar('\n');
	dprintf(1, "20%010.5c", nb);
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putstr("***8*** fill + precision superieur");
	ft_putchar('\n');
	ft_printf("20%05.10c", nb); 
	ft_putchar('\n');
	dprintf(1, "20%05.10c", nb);
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putstr("***9*** espace + precision egal");
	ft_putchar('\n');
	ft_printf("20%5.5c", nb); 
	ft_putchar('\n');
	dprintf(1, "20%5.5c", nb);
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putstr("***10*** espace + precision inferieur");
	ft_putchar('\n');
	ft_printf("20%15.5c", nb); 
	ft_putchar('\n');
	dprintf(1, "20%15.5c", nb);
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putstr("***11*** espace + precision superieur");
	ft_putchar('\n');
	ft_printf("20%7.10c", nb);
	ft_putchar('\n');
	dprintf(1, "20%7.10c", nb);
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putstr("***12*** espace + precision egal + retourner");
	ft_putchar('\n');
	ft_printf("20%5.5c", nb);
	ft_putchar('\n');
	dprintf(1, "20%5.5c", nb);
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putstr("***13*** espace + precision inferieur + retourner");
	ft_putchar('\n');
	ft_printf("20%15.5c", nb);
	ft_putchar('\n');
	dprintf(1, "20%15.5c", nb);
	ft_putchar('\n');
	ft_putchar('\n');
	ft_putstr("***14*** espace + precision superieur + retourner");
	ft_putchar('\n');
	ft_printf("20%5.10c", nb);
	ft_putchar('\n');
	dprintf(1, "20%5.10c", nb);
	ft_putchar('\n');*/
}
