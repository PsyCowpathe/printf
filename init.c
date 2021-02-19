/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 06:32:22 by agirona           #+#    #+#             */
/*   Updated: 2021/02/19 16:52:28 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	moin(t_flags *data, va_list arg, char *cut, int *i)
{
	(void)i;
	(void)cut;
	(void)arg;
	data->align = 1;
}

void	zero(t_flags *data, va_list arg, char *cut, int *i)
{
	data->fill = 1;
	data->fillen = get_nb(data, arg, cut, i);
	if (data->fillen < 0)
		data->align = 1;
	data->fillen = ft_abs(data->fillen);
}

void	dot(t_flags *data, va_list arg, char *cut, int *i)
{
	data->precision = 1;
	data->preclen = get_nb(data, arg, cut, i);
}

void	asterisk(t_flags *data, va_list arg, char *cut, int *i)
{
	if (i == 0 || (cut[*i - 1] != '.' && cut[*i - 1] != '0'))
	{
		data->space = va_arg(arg, int);
		if (data->space < 0)
			data->align = 1;
		data->space = ft_abs(data->space);
	}
}

void	nombre(t_flags *data, va_list arg, char *cut, int *i)
{
	data->space = ft_abs(get_nb(data, arg, cut, &i));
}

void	struct_init(t_flags *data)
{
	data->align = 0;
	data->fill = 0;
	data->precision = 0;
	data->fillen = 0;
	data->preclen = 0;
	data->space = 0;
	data->error = 0;
}
