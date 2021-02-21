/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_u_conv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 15:26:15 by agirona           #+#    #+#             */
/*   Updated: 2021/02/21 15:06:26 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	u_advanced_no_prec(t_flags *data, char *tmp)
{
	int		len;
	int		ret;

	ft_putstr(tmp);
	ret = 0;
	if (data->fill == 1)
	{
		len = data->fillen - data->nbsize;
		ret = print_char(len, '0');
	}
	if (data->space > 0)
	{
		len = data->space - data->nbsize;
		ret = print_char(len, ' ');
	}
	data->total += ret + data->nbsize;
}

void	u_advanced_prec_fill(t_flags *data, char *tmp, long long nb)
{
	int		ret;
	int		zero;
	int		print;

	print = 0;
	if (nb == 0 && data->precision == 1 && data->preclen == 0)
		print = 1;
	if (data->fillen > data->preclen)
	{
		zero = data->preclen - data->nbsize;
		ret = print_char(zero, '0');
		if (print == 0)
			ft_putstr(tmp);
		zero = data->fillen - data->nbsize - ret;
		ret += print_char(zero + print, ' ');
		ret += data->nbsize;
	}
	else
		ret = u_preclen_is_upper(data, nb, tmp, 0);
	data->total += ret - print;
}

void	u_advanced_prec_space(t_flags *data, char *tmp, long long nb)
{
	int		ret;
	int		zero;
	int		print;

	print = 0;
	if (nb == 0 && data->precision == 1 && data->preclen == 0)
		print = 1;
	if (data->space > data->preclen)
	{
		zero = data->preclen - data->nbsize;
		ret = print_char(zero, '0');
		if (print == 0)
			ft_putstr(tmp);
		zero = data->space - data->nbsize - ret;
		ret += print_char(zero + print, ' ');
		ret += data->nbsize;
	}
	else
		ret = u_preclen_is_upper(data, nb, tmp, 0);
	data->total += ret - print;
}

void	u_advanced_prec(t_flags *data, char *tmp, long long nb)
{
	int		print;
	int		zero;
	int		ret;

	print = 0;
	if (nb == 0 && data->preclen == 0)
		print = 1;
	zero = data->preclen - data->nbsize;
	ret = print_char(zero + print, '0');
	if (print == 0)
		ft_putstr(tmp);
	ret += print_char(data->space - data->nbsize , ' ');
	data->total += ret + data->nbsize - print;
}

void	advanced_unsigned_conv(t_flags *data, long long nb)
{
	char	*tmp;

	tmp = ft_long_itoa(nb);
	if (data->precision == 0)
		u_advanced_no_prec(data, tmp);
	else if (data->precision == 1 && data->fill == 1 && data->space == 0)
		u_advanced_prec_fill(data, tmp, nb);
	else if (data->precision == 1 && data->fill == 0 && data->space > 0)
		u_advanced_prec_space(data, tmp, nb);
	else
		u_advanced_prec(data, tmp, nb);
	free(tmp);
}
