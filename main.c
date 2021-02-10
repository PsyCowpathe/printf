/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 09:27:11 by agirona           #+#    #+#             */
/*   Updated: 2021/02/10 14:36:58 by agirona          ###   ########lyon.fr   */
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
	int		ret;
	int		nb;
	int		v;
	int		l = 0;
	char	*param = "%-1d";
	nb = 1;
	ret = 0;
	v = 0;
	ft_putstr(param);
	//while (v < 20)
//	{
		ft_putchar('\n');
		ft_putstr("Moi =");
		ret = ft_printf(param, l);
		ft_putstr("| retour = ");
		ft_putnbr(ret);
		ft_putchar('\n');
		ft_putstr("Lui =");
		ret = dprintf(1, param, l);
		ft_putstr("| retour = ");
		ft_putnbr(ret);
		v++;
	//}
}

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
