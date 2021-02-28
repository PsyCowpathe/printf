/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:35:45 by agirona           #+#    #+#             */
/*   Updated: 2021/02/28 17:27:52 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	hashtag(t_flags *data, char *cut, int *i)
{
	(void)cut;
	(void)i;
	data->hashtag = 1;
}

void	plus(t_flags *data, char *cut, int *i)
{
	(void)cut;
	(void)i;
	data->plus = 1;
}

void	space(t_flags *data, char *cut, int *i)
{
	(void)cut;
	(void)i;
	data->setspace = 1;
}

void	set_space(t_flags *data)
{
	if (data->precision == 1 && data->fill == 1)
		data->fillen--;
	else if (data->fill == 1)
		data->fillen--;
	if (data->precision == 1 && data->space > 0)
		data->space--;
	else if (data->space > 0)
		data->space--;
	ft_putchar(' ');
	data->total += 1;
}

void	set_plus(t_flags *data, int neg)
{
	if (neg == 0)
	{
		if (data->precision == 1 && data->fill == 1)
			data->fillen--;
		else if (data->precision == 1 && data->space > 0)
			data->space--;
		if (data->fill == 1 && data->space == 0 && data->precision == 0)
			data->fillen--;
		if (data->space > 0 && data->fill == 0 && data->precision == 0)
			data->space--;
	}
	if (data->align == 1 && neg == 0)
	{
		ft_putchar('+');
		data->total += 1;
	}
	else if (neg == 0)
		data->total += 1;
}
