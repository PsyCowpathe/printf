/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:22:06 by agirona           #+#    #+#             */
/*   Updated: 2021/02/04 12:37:21 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_percent(char *form, int *i)
{
	int		count;
	int		save;
	int		print;

	save = *i;
	count = 0;
	print = 0;
	while (form[*i] == '%')
	{
		count++;
		*i += 1;
	}
	if (count % 2 == 0)
	{
		while (count > 0)
		{
			ft_putchar('%');
			print++;
			count -= 2;
		}
		while (form[*i] && form[*i] != '%')
		{
			ft_putchar(form[*i]);
			print++;
			*i += 1;
		}
	}
	*i -= 1;
	return (print);
}

int		verif_flags(t_flags data, char *cut)
{
	int		i;

	i = 0;
	while (cut[i])
	{
		if (ft_ischar(data.primlist, cut[i]) == 1)
		{
			return (i);
		}
		if (ft_ischar(data.seclist, cut[i]) == 0 && !(cut[i] >= '0' && cut[i] <= '9'))
			return (-1);
		i++;
	}
	return (-1);
}

char	*ft_long_itoa(long long n)
{
	int		len;
	int		neg;
	long	nbr;
	char	*res;

	len = 1;
	nbr = n;
	while (nbr /= 10)
		len++;
	neg = (n < 0) ? 1 : 0;
	nbr = n;
	nbr = (nbr < 0) ? nbr * -1 : nbr;
	if ((res = malloc(sizeof(char) * len + neg + 1)) == NULL)
		return (NULL);
	res[0] = (neg == 1) ? '-' : '0';
	res[len + neg--] = '\0';
	while (len != 0)
	{
		res[len + neg] = nbr % 10 + '0';
		nbr /= 10;
		len--;
	}
	return (res);
}
