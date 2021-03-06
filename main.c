/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 09:27:11 by agirona           #+#    #+#             */
/*   Updated: 2021/02/22 17:58:44 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>


/*
   printf("percent 1 %012%");
   printf("percent 2 %12%");
   printf("percent 3 %-12%");
   printf("percent 4 %0%");
   */

void	mainprintf(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	int		ret1 = 5;
	int		ret2;
	int		nb;
	int		v;
	int		a = -15;
	int		b = 4;
//	int		c = 8;
//	int		i = -10;
//	int		c = 97;
//	int		j = -12;
//	int		k = 123456789;
//	int		l = 8;
//	int		m = -12345678;
//	int		d = 2147483647;
//	int		e = -2147483648;
	//char	*n = "abcdefghijklmnop";

	char	param[] = "%-04*.6i";
	nb = 1;
	v = 0;
	ft_putstr(param);
//	while (a < 5)
//	{
//		b = -2;
//		while (b < 5)
//		{
		ft_putstr(" | with a = ");
		ft_putnbr(a);
		ft_putstr(" b = ");
		ft_putnbr(b);
		ft_putchar('\n');
		ret1 = ft_printf(param, 15, 4, 4);
		ft_putstr("| retour = ");
		ft_putnbr(ret1);
		ft_putchar('\n');
		ret2 = dprintf(1, "%-04*.6i", 15, 4, 4);
		ft_putstr("| retour = ");
		ft_putnbr(ret2);
		//if (ret1 != ret2)
		//	ft_putstr("***************error*************************");
		//ret = dprintf(1, param, l);
		ft_putchar('\n');
		//while (1);
//		b++;
//		}
//		a++;
//	}
}

%-04*.6i | with a = -15 b = 4$
000004| retour = 6$
000004         | retour = 15$i



int		main(int argc, char **argv)
{
	mainprintf(argc, argv);
	//while (1);
	return (1);
}

/*int		mainprintf()
  {

  int		nb = 's';

  ft_putstr("***1*** espace");
  ft_putchar('\n');
  ft_printf("20%20i%%%%", nb);
  ft_putchar('\n');
  ft_putnbr(dprintf(1, "20%20i%%%%", nb));
  ft_putchar('\n');
  ft_putchar('\n');
  ft_putstr("***2*** espace + retourner");
  ft_putchar('\n');
  ft_printf("20%-25i", nb); 	ft_putchar('\n');
  ft_putnbr(dprintf(1, "20%-25i", nb));
  ft_putchar('\n');
  ft_putchar('\n');
  ft_putstr("***3*** precision");
  ft_putchar('\n');
  ft_printf("20%.3i", nb); 
  ft_putchar('\n');
  ft_putnbr(dprintf(1, "20%.3i", nb));
  ft_putchar('\n');
  ft_putchar('\n');
  ft_putstr("***4*** precision + retourner");
  ft_putchar('\n');
  ft_printf("20%-.3i", nb); 	
  ft_putchar('\n');
  ft_putnbr(dprintf(1, "20%-.3i", nb));
  ft_putchar('\n');
  ft_putchar('\n');
  ft_putstr("***5*** fill");
  ft_putchar('\n');
  ft_printf("20%03i", nb); 
  ft_putchar('\n');
  ft_putnbr(dprintf(1, "20%03i", nb));
  ft_putchar('\n');
  ft_putchar('\n');
  ft_putstr("***6*** fill + precision egal");
  ft_putchar('\n');
  ft_printf("20%05.5i", nb); 
  ft_putchar('\n');
  ft_putnbr(dprintf(1, "20%05.5i", nb));
  ft_putchar('\n');
  ft_putchar('\n');
  ft_putstr("***7*** fill + precision inferieur");
  ft_putchar('\n');
  ft_printf("20%010.5i", nb); 
  ft_putchar('\n');
  ft_putnbr(dprintf(1, "20%010.5i", nb));
  ft_putchar('\n');
  ft_putchar('\n');
  ft_putstr("***8*** fill + precision superieur");
  return (1);
  ft_putchar('\n');
  ft_printf("20%05.10i", nb); 
  ft_putchar('\n');
  ft_putnbr(dprintf(1, "20%05.10i", nb));
  ft_putchar('\n');
  ft_putchar('\n');
  ft_putstr("***9*** espace + precision egal");
  ft_putchar('\n');
  ft_printf("20%5.5i", nb); 
  ft_putchar('\n');
  ft_putnbr(dprintf(1, "20%5.5i", nb));
  ft_putchar('\n');
  ft_putchar('\n');
  ft_putstr("***10*** espace + precision inferieur");
  ft_putchar('\n');
  ft_printf("20%15.5i", nb); 
ft_putchar('\n');
ft_putnbr(dprintf(1, "20%15.5i", nb));
ft_putchar('\n');
ft_putchar('\n');
ft_putstr("***11*** espace + precision superieur");
ft_putchar('\n');
ft_printf("20%7.10i", nb);
ft_putchar('\n');
ft_putnbr(dprintf(1, "20%7.10i", nb));
ft_putchar('\n');
ft_putchar('\n');
ft_putstr("***12*** espace + precision egal + retourner");
ft_putchar('\n');
ft_printf("20%5.5i", nb);
ft_putchar('\n');
ft_putnbr(dprintf(1, "20%5.5i", nb));
ft_putchar('\n');
ft_putchar('\n');
ft_putstr("***13*** espace + precision inferieur + retourner");
ft_putchar('\n');
ft_printf("20%15.5i", nb);
ft_putchar('\n');
ft_putnbr(dprintf(1, "20%15.5i", nb));
ft_putchar('\n');
ft_putchar('\n');
ft_putstr("***14*** espace + precision superieur + retourner");
ft_putchar('\n');
ft_printf("20%5.10i", nb);
ft_putchar('\n');
ft_putnbr(dprintf(1, "20%5.10i", nb));
ft_putchar('\n');
return (1);
}*/
