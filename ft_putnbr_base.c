/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 04:58:17 by agirona           #+#    #+#             */
/*   Updated: 2021/02/10 14:36:55 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_check(char *str)
{
	int		i;
	int		d;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			return (0);
		c = str[i];
		d = i + 1;
		while (str[d])
		{
			if (str[d] == c)
				return (0);
			d++;
		}
		i++;
	}
	if (i == 0 || i == 1)
		return (0);
	return (1);
}

static void		ft_r_putnbr_base(long int nb, int div, char *base)
{
	if (nb >= div)
	{
		nb = nb / div;
		ft_r_putnbr_base(nb, div, base);
		ft_putchar(base[nb % div]);
	}
}

void			ft_long_putnbr_base(uintptr_t nbr, char *base)
{
	int			i;
	int			div;
	long int	nb;

	nb = nbr;
	i = 0;
	div = 0;
	if (ft_check(base) == 0)
		return ;
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
	}
	while (base[div])
		div++;
	ft_r_putnbr_base(nb, div, base);
	ft_putchar(base[nb % div]);
}

static void		ft_rl_putnbr_base(unsigned long long nb, int div, char *base)
{
	if (nb >= (unsigned long long)div)
	{
		nb = nb / div;
		ft_rl_putnbr_base(nb, div, base);
		ft_putchar(base[nb % div]);
	}
}

void			ft_llong_putnbr_base(unsigned long long nbr, char *base)
{
	int			i;
	unsigned long long	div;
	unsigned long long	nb;

	nb = nbr;
	i = 0;
	div = 0;
	if (ft_check(base) == 0)
		return ;
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
	}
	while (base[div])
		div++;
	ft_rl_putnbr_base(nb, div, base);
	ft_putchar(base[nb % div]);
}
