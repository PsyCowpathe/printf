/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:22:06 by agirona           #+#    #+#             */
/*   Updated: 2021/02/18 17:48:20 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_char(int len, char c)
{
	int		i;

	i = 0;
	while (i < len)
	{
		ft_putchar(c);
		i++;
	}
	return (i);
}

int		verif_flags(t_flags data, char *cut)
{
	int		i;

	i = 0;
	while (cut[i])
	{
		if (ft_ischar(data.primlist, cut[i]) == 1)
			return (i);
		if (ft_ischar(data.seclist, cut[i]) == 0
		&& !(cut[i] >= '0' && cut[i] <= '9'))
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

int		preclen_is_upper(t_flags *data, long long nb, int neg, int wich)
{
	int		print;
	int		ret;
	int		zero;
	int		nblen;

	nblen = ft_longlen(nb);
	print = (nb == 0 && data->precision == 1 && data->preclen == 0) ? 1 : 0;
	zero = data->preclen - nblen;
	if (wich == 1 && data->preclen < 0)
		zero = data->fillen - nblen - neg;
	if (neg == 1)
		ft_putchar('-');
	ret = print_char(zero + print, '0');
	ret += neg + nblen;
	if (print == 0)
		ft_putnbr(nb);
	return (ret);
}
