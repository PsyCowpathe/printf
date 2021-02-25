/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:31:22 by agirona           #+#    #+#             */
/*   Updated: 2021/02/25 12:51:15 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	moin(t_flags *data, char *cut, int *i)
{
	(void)i;
	(void)cut;
	data->fill = 0;
	data->align = 1;
	data->space = 0;
	data->precision = 0;
}

void	zero(t_flags *data, char *cut, int *i)
{
	data->fill = 1;
	data->fillen = get_nb(data, cut, i);
	if (data->fillen < 0)
		data->align = 1;
	data->fillen = ft_abs(data->fillen);
}

void	dot(t_flags *data, char *cut, int *i)
{
	data->precision = 1;
	data->preclen = get_nb(data, cut, i);
}

void	asterisk(t_flags *data, char *cut, int *i)
{
	if (*i == 0 || (cut[*i - 1] != '.' && cut[*i - 1] != '0'))
	{
		data->space = va_arg(data->arg, int);
		if (data->space < 0)
			data->align = 1;
		data->space = ft_abs(data->space);
	}
}

void	nombre(t_flags *data, char *cut, int *i)
{
	data->space = ft_abs(get_nb(data, cut, i));
}
