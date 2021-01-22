/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:53:32 by agirona           #+#    #+#             */
/*   Updated: 2021/01/22 13:43:34 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		ft_putchar(str[i++]);
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		ft_putchar('-');
		ft_putnbr(214748364);
		ft_putchar(8 + 48);
	}
	else if (nb < 0)
	{
		ft_putchar('-');
		ft_putnbr(nb * -1);
	}
	else if (nb < 10)
	{
		ft_putchar(nb + 48);
	}
	else
	{
		ft_putnbr(nb / 10);
		ft_putchar(nb % 10 + 48);
	}
}

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int		ft_atoi(char *str)
{
	int		i;
	int		count;
	int		neg;
	int		res;

	count = 0;
	i = 0;
	res = 0;
	while (str[i] == '\r' || str[i] == '\n' || str[i] == '\v'
	|| str[i] == '\t' || str[i] == '\f' || str[i] == ' ')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			count++;
	}
	neg = (count % 2 == 0) ? 1 : -1;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * neg);
}

void	ft_bzero(void *s, size_t n)
{
	size_t i;

	i = 0;
	while (i != n)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*data;

	if (!(data = (malloc(count * size))))
		return (NULL);
	ft_bzero(data, count * size);
	return (data);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	if ((str = ft_calloc(ft_strlen((char *)s1) + 1, 1)) == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
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

int		ft_abs(int nb)
{
	if (nb < 0)
		return (nb * -1);
	else
		return (nb); 
}

int		ft_nblen(int nb)
{
	int		len;

	len = 0;
	nb = ft_abs(nb);
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

