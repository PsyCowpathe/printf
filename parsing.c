/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:16:02 by agirona           #+#    #+#             */
/*   Updated: 2021/02/19 16:52:30 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		start_conv(t_flags *data, va_list arg)
{
	if (data->noprim == 1)
		string_conv(data, "");
	if (data->primary == 's')
		string_conv(data, va_arg(arg, char *));
	else if (data->primary == 'd')
		int_conv(data, arg);
	else if (data->primary == 'i')
		int_conv(data, arg);
	else if (data->primary == 'c')
		char_conv(data, arg);
	else if (data->primary == 'u')
		unsigned_conv(data, arg);
	else if (data->primary == 'p')
		address_conv(data, arg);
	else if (data->primary == 'x' || data->primary == 'X')
		hex_conv(data, arg);
	return (1);
}

int		get_nb(t_flags *data, va_list arg, char *cut, int *i)
{
	int		c;
	char	*tmp;

	c = *i + 1;
	if (cut[c] == '*')
		return (va_arg(arg, int));
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

int		set_struct(t_flags *data, va_list arg, char *cut)
{
	void	(*tabft[5])(t_flags*, va_list, char*, int*);
	char	*cs;
	int		i;
	int		c;

	i = 0;
	cs = "-0.*123456789";
	struct_init(data);
	(tabft[0]) = &moin;
	(tabft[1]) = &zero;
	(tabft[2]) = &dot;
	(tabft[3]) = &asterisk;
	(tabft[4]) = &nombre;
	while (cut[i] && ft_ischar(data->primlist, cut[i]) != 1)
	{
		c = 0;
		while (cs[c] && cut[i] != cs[c])
			c++;
		if (c > 4)
			c = 4;
		(*tabft[c])(data, arg, cut, &i);
		if (data->error == 1)
			return (0);
		i++;
	}
	data->primary = cut[i];
	if (start_conv(data, arg) == 0)
		return (0);
	ft_putstr(cut + i + 1);
	data->total += ft_strlen(cut) - i - 1;
	return (1);
}

int		cut_flags(t_flags data, va_list arg)
{
	int		i;
	char	*cut;

	i = 0;
	data.noprim = 0;
	data.total = 0;
	while (i < (int)ft_strlen(data.form))
	{
		if (data.form[i] == '%' && data.form[i + 1] == '%')
		{
			data.total++;
			ft_putchar('%');
			i += 2;
		}
		else if (data.form[i] == '%')
		{
			i++;
			cut = get_flags(&data, data.form, &i);
			if (verif_flags(data, cut) >= 0 || data.noprim == 1)
				set_struct(&data, arg, cut);
			if (data.noprim == 1)
				i++;
			free(cut);
		}
		else
		{
			ft_putchar(data.form[i++]);
			data.total++;
		}
	}
	return (data.total);
}
