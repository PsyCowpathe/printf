/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:16:02 by agirona           #+#    #+#             */
/*   Updated: 2021/02/11 14:37:57 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		start_conv(t_flags *data, va_list arg)
{
	int		save;

	save = data->preclen;
	data->preclen = ft_abs(data->preclen);
	//print_struct(*data);
	if (data->noprim == 1)
	{
		string_conv(data, "");
		//data->noprim = 0;
	}
	if (data->primary == 's')
	{
		data->preclen = save;
		string_conv(data, va_arg(arg, char *));
	}
	else if (data->primary == 'd')
	{
		data->preclen = save;
		int_conv(data, arg);
	}
	else if (data->primary == 'i')
	{
		data->preclen = save;
		int_conv(data, arg);
	}
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
	{
		tmp[c] = cut[*i];
		*i += 1;
		c++;
	}
	if (cut[*i] < '0' || cut[*i] > '9')
		*i -= 1;
	tmp[c] = '\0';
	c = ft_atoi(tmp);
	free(tmp);
	return (c);
}

int		set_struct(t_flags *data, va_list arg, char *cut)
{
	int		i;

	i = 0;
	struct_init(data);
	while (cut[i] && ft_ischar(data->primlist, cut[i]) != 1)
	{
		if (cut[i] >= '1' && cut[i] <= '9')
		{
			data->space = ft_abs(get_nb(data, arg, cut, &i));
			if (data->error == 1)
				return (0);
		}
		else if (cut[i] == '-')
		{
			data->align = 1;
		}
		else if (cut[i] == '0')
		{
			data->fill = 1;
			data->fillen = get_nb(data, arg, cut, &i);
			if (data->error == 1)
				return (0);
			if (data->fillen < 0)
				data->align = 1;
			data->fillen = ft_abs(data->fillen);
		}
		else if (cut[i] == '.')
		{
			data->precision = 1;
			data->preclen = get_nb(data, arg, cut, &i);
			if (data->error == 1)
				return (0);
		}
		else if (cut[i] == '*' && (i == 0 || (cut[i - 1] != '.' && cut[i - 1] != '0')))
		{
			data->space = va_arg(arg, int);
			if (data->space < 0)
				data->align = 1;
			data->space = ft_abs(data->space);
		}
		i++;
	}
	data->primary = cut[i];
	//print_struct(*data);
	if (start_conv(data, arg) == 0)
		return (0);
	ft_putstr(cut + i + 1);
	data->total += ft_strlen(cut) - i - 1;
	return (1);
}

char	*get_flags(t_flags *data, char *form, int *i)
{
	char	*cut;
	int		size;
	int		primary;

	size = 0;
	primary = 1;
	while (form[*i + size] && form[*i + size] != '%')
		size++;
	cut = malloc(sizeof(char) * size + 1);
	size = 0;
	while (form[*i] && form[*i] != '%')
	{
		if (ft_ischar(data->primlist, form[*i]) == 1)
			primary = 0;
		cut[size] = form[*i];
		*i += 1;
		size++;
	}
	if (primary == 1 && size != 0)
		data->noprim = 1;
	cut[size] = '\0';
	return (cut);
}

int		cut_flags(t_flags data, va_list arg)
{
	int		i;
	char	*cut;
	(void)arg;

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

/*int		cut_flags(t_flags data, va_list arg)
{
	int		i;
	char	*cut;
	
	i = 0;
	data.total = 0;
	data.get_arg = 1;
	while (data.form[i])
	{
		if (data.form[i] == '%')
		{
			data.total += print_percent(data.form, &i);
			i = i + 1;
			if ((cut = get_flags(&data, data.form, &i)) == NULL)
				return (data.total);
			if (data.get_arg == 0 && i != (int)ft_strlen(data.form))
				i++;
			if (verif_flags(data, cut) >= 0)
			{
				if (set_struct(&data, arg, cut) == 0)
					return (data.total);
			}
			else
			{
				data.total += ft_strlen(cut);
				ft_putstr(cut);
			}
			free(cut);
		}
		else
		{
			ft_putchar(data.form[i++]);
			data.total++;
		}
	}
	return (data.total);
}*/
