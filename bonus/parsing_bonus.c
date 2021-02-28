/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:16:02 by agirona           #+#    #+#             */
/*   Updated: 2021/02/28 15:57:29 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int		start_conv(t_flags *data)
{
	if (data->noprim == 1)
		string_conv(data, "");
	if (data->primary == 's')
		string_conv(data, va_arg(data->arg, char *));
	else if (data->primary == 'd')
		int_conv(data);
	else if (data->primary == 'i')
		int_conv(data);
	else if (data->primary == 'c')
		char_conv(data);
	else if (data->primary == 'u')
		unsigned_conv(data);
	else if (data->primary == 'p')
		address_conv(data);
	else if (data->primary == 'x' || data->primary == 'X')
		hex_conv(data);
	return (1);
}

int		endset(t_flags *d, void (***t)(t_flags *d, char*, int*), char *c, int i)
{
	d->primary = c[i];
	if (d->primary == '\0' && d->noprim == 0)
		return (0);
	if (start_conv(d) == 0)
	{
		free((*t));
		return (0);
	}
	ft_putstr(c + i + 1);
	d->total += ft_strlen(c) - i - 1;
	free((*t));
	return (1);
}

int		set_struct(t_flags *data, char *cut)
{
	void	(**tabft)(t_flags*, char*, int*);
	char	*cs;
	int		i;
	int		c;

	i = -1;
	cs = "-0.*#+ 123456789";
	if (((tabft) = struct_init(data)) == NULL)
		return (0);
	while (cut[++i] && ft_ischar(data->primlist, cut[i]) != 1)
	{
		c = 0;
		while (cs[c] && cut[i] != cs[c])
			c++;
		if (c > 7 && c <= 15)
			c = 7;
		if (c <= 15)
			(*tabft[c])(data, cut, &i);
		if (data->error == 1)
		{
			free((tabft));
			return (0);
		}
	}
	return (endset(data, &tabft, cut, i));
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
