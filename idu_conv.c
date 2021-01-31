/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_conv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:41:36 by agirona           #+#    #+#             */
/*   Updated: 2021/01/31 18:00:03 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		advanced_unsign_conv(t_flags data, int size, unsigned int nb)
{
	int		i;
	int		c;
	char	*res;
	char	*tmp;

	i = 0;
	c = 0;
	if (nb < 0)
		i = 1;
	if ((res = malloc(sizeof(char) * size + i + 1)) == NULL)
		return (0);
	if (nb < 0)
		res[0] = '-';
	while (c++ < data.preclen - ft_nblen(nb))
		res[i++] = '0';
	tmp = ft_long_itoa(nb);
	c = 0;
	if (nb < 0)
		c++;
	while (tmp[c])
		res[i++] = tmp[c++];
	while (i < data.fillen)
		res[i++] = ' ';
	res[i] = '\0';
	ft_putstr(res);
	return (1);
}

int		unsigned_conv(t_flags data, va_list arg)
{
	char			*res;
	int				size;
	int				i;
	int				c;
	unsigned int	nb;

	size = (data.preclen > data.fillen) ? data.preclen : data.fillen;
	nb = (unsigned int)va_arg(arg, unsigned int);
	i = 0;
	if (data.align == 1)
		return (advanced_unsign_conv(data, size, nb));
	if (nb < 0)
		i = 1;
	if ((res = malloc(sizeof(char) * size + i + 1)) == NULL)
		return (0);
	if (nb < 0)
		res[i] = '-';
	c = (data.fill == 1 && data.precision == 0) ? ft_nblen(nb) - 1 : -1;
	if (nb < 0 && data.fillen > data.preclen)
		c++;
	while (++c < data.fillen - data.preclen)
		res[i++] = (data.fill == 1 && data.precision == 0) ? '0' : ' ';
	while (c++ < size - ft_nblen(nb))
		res[i++] = '0';
	res[i] = '\0';
	ft_putstr(res);
	ft_putstr(ft_long_itoa(nb));
	return (1);
}

/*int		advanced_int_conv(t_flags data, int size, int nb)
  {
  int		i;
  int		c;
  char	*res;
  char	*tmp;

  i = 0;
  c = 0;
  if (nb < 0)
  i = 1;
  if ((res = malloc(sizeof(char) * size + i + 1)) == NULL)
  return (0);
  if (nb < 0)
  res[0] = '-';
  while (c++ < data.preclen - ft_nblen(nb))
  res[i++] = '0';
  tmp = ft_long_itoa(nb);
  c = 0;
  if (nb < 0)
  c++;
  while (tmp[c])
  res[i++] = tmp[c++];
  while (i < data.fillen)
  res[i++] = ' ';
  res[i] = '\0';
  ft_putstr(res);
  return (1);
  }*/

int		advanced_int_conv(t_flags data, int size, int nb)
{
	int		i;
	(void)data;
	(void)nb;
	(void)size;

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
	return (1);
}

int		int_conv(t_flags data, va_list arg)
{
	int		size;
	int		i;
	int		nb;

	nb = (int)va_arg(arg, int);
	i = 0;
	size = (data.preclen > data.fillen) ? data.preclen : data.fillen;
	size = (data.space > size) ? data.space : size;
	size -= ft_nblen(nb);
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
	return (1);
}
