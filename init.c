/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 06:32:22 by agirona           #+#    #+#             */
/*   Updated: 2021/02/22 17:58:46 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	moin(t_flags *data, char *cut, int *i)
{
	(void)i;
	(void)cut;
	data->align = 1;
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

void	*struct_init(t_flags *data)
{
	void	(**tabft)(t_flags*, char*, int*);

	if (((tabft) = malloc(sizeof(void*) * (FSECONDARY + 1))) == NULL)
		return (NULL);
	data->align = 0;
	data->fill = 0;
	data->precision = 0;
	data->fillen = 0;
	data->preclen = 0;
	data->space = 0;
	data->error = 0;
	data->hashtag = 0;
	data->plus = 0;
	data->setspace = 0;
	(tabft[0]) = &moin;
	(tabft[1]) = &zero;
	(tabft[2]) = &dot;
	(tabft[3]) = &asterisk;
	(tabft[4]) = &hashtag;
	(tabft[5]) = &plus;
	(tabft[6]) = &space;
	(tabft[7]) = &nombre;
	return (tabft);
}
