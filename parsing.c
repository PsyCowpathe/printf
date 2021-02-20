/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:16:02 by agirona           #+#    #+#             */
/*   Updated: 2021/02/20 16:11:44 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

int		get_nb(t_flags *data, char *cut, int *i)
{
	int		c;
	char	*tmp;

	c = *i + 1;
	if (cut[c] == '*')
		return (va_arg(data->arg, int));
	while (cut[c] && (cut[c] >= '0' && cut[c] <= '9'))
		c++;
	if ((tmp = malloc(sizeof(char) * c + 1)) == NULL)
	{
		free(cut);
		data->error = 1;
		return (0);
	}
	c = 0;
	if (cut[*i] < '0' || cut[*i] > '9')
		*i += 1;
	while (cut[*i] && (cut[*i] >= '0' && cut[*i] <= '9'))
		tmp[c++] = cut[(*i)++];
	if (cut[*i] < '0' || cut[*i] > '9')
		*i -= 1;
	tmp[c] = '\0';
	c = ft_atoi(tmp);
	free(tmp);
	return (c);
}

char	*get_flags(t_flags *data, char *form, int *i)
{
	char	*cut;
	int		size;
	int		primary;

	size = 0;
	primary = 0;
	while (form[*i + size] && form[*i + size] != '%')
		size++;
	cut = malloc(sizeof(char) * size + 1);
	size = 0;
	while (form[*i] && form[*i] != '%')
	{
		if (ft_ischar(data->primlist, form[*i]) == 1)
			primary = 1;
		cut[size] = form[*i];
		*i += 1;
		size++;
	}
	if (primary == 0 && size != 0)
		data->noprim = 1;
	cut[size] = '\0';
	return (cut);
}

int		endset(t_flags *d, void (***t)(t_flags *d, char*, int*), char *c, int i)
{
	d->primary = c[i];
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
	cs = "-0.*123456789";
	if (((tabft) = struct_init(data)) == NULL)
		return (0);
	while (cut[++i] && ft_ischar(data->primlist, cut[i]) != 1)
	{
		c = 0;
		while (cs[c] && cut[i] != cs[c])
			c++;
		if (c > 4 && c <= 12)
			c = 4;
		if (c <= 12)
			(*tabft[c])(data, cut, &i);
		if (data->error == 1)
		{
			free((tabft));
			return (0);
		}
	}
	return (endset(data, &tabft, cut, i));
}

int		cut_flags(t_flags data)
{
	int		i;
	char	*cut;

	i = 0;
	while (i < (int)ft_strlen(data.form))
	{
		if (data.form[i] == '%' && data.form[i + 1] == '%' && ++data.total)
		{
			ft_putchar('%');
			i += 2;
		}
		else if (data.form[i] == '%')
		{
			i++;
			cut = get_flags(&data, data.form, &i);
			if (verif_flags(data, cut) >= 0 || data.noprim == 1)
				set_struct(&data, cut);
			if (data.noprim == 1)
				i++;
			free(cut);
		}
		else if (++data.total)
			ft_putchar(data.form[i++]);
	}
	return (data.total);
}
