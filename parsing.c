/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:16:02 by agirona           #+#    #+#             */
/*   Updated: 2021/02/04 12:37:20 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		start_conv(t_flags *data, va_list arg)
{
	//print_struct(*data);
	if (data->primary == 's')
		string_conv(data, arg);
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

int		get_nb(va_list arg, char *cut, int *i)
{
	int		c;
	char	*tmp;

	c = *i + 1;
	if (cut[c] == '*')
		return(va_arg(arg, int));
	while (cut[c] && (cut[c] >= '0' && cut[c] <= '9'))
		c++;
	if ((tmp = malloc(sizeof(char) * c)) == NULL)
	{			
		free(cut);
		return (-1);
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
	while (ft_ischar(data->primlist, cut[i]) != 1)
	{
		if (cut[i] >= '1' && cut[i] <= '9')
		{
			if ((data->space = get_nb(arg, cut, &i)) == -1)
				return (0);
		}
		else if (cut[i] == '-')
		{
			data->align = 1;
		}
		else if (cut[i] == '0')
		{
			data->fill = 1;
			if ((data->fillen = get_nb(arg, cut, &i)) == -1)
				return (0);
		}
		else if (cut[i] == '.')
		{
			data->precision = 1;
			if ((data->preclen = get_nb(arg, cut, &i)) == -1)
				return (0);
		}
		else if (cut[i] == '*' && cut[i - 1] != '.' && cut[i - 1] != '0')
		{
			data->space = va_arg(arg, int);
			if (data->space < 0)
				data->align = 1;
			data->space = ft_abs(data->space);
		}
		i++;
	}
	data->primary = cut[i];
	if (start_conv(data, arg) == 0)
		return (0);
	ft_putstr(cut + i + 1);
	data->total += ft_strlen(cut) - i - 1;
	return (1);
}

char	*get_flags(char *form, int *i)
{
	char	*cut;
	int		size;

	size = 0;
	while (form[*i + size] && form[*i + size] != '%')
		size++;
	cut = malloc(sizeof(char) * size + 1);
	size = 0;
	while (form[*i] && form[*i] != '%')
	{
		cut[size] = form[*i];
		*i += 1;
		size++;
	}
	cut[size] = '\0';
	return (cut);
}

int		cut_flags(t_flags data, va_list arg)
{
	int		i;
	char	*cut;
	
	i = 0;
	data.total = 0;
	while (data.form[i])
	{
		if (data.form[i] == '%')
		{
			data.total += print_percent(data.form, &i);
			i = i + 1;
			if ((cut = get_flags(data.form, &i)) == NULL)
				return (data.total);
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
}
