/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:50:19 by agirona           #+#    #+#             */
/*   Updated: 2021/02/28 15:57:30 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	if (primary == 0 && size != 0 && *i != (int)ft_strlen(form))
		data->noprim = 1;
	cut[size] = '\0';
	return (cut);
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

int		ft_printf(const char *str, ...)
{
	int			ret;
	t_flags		data;

	if (flags_init(&data.primlist, "cspdiuxX%", &data.seclist, "-0.*") == 0)
		return (0);
	va_start(data.arg, str);
	data.form = (char *)str;
	if (!data.form)
		return (0);
	data.noprim = 0;
	data.total = 0;
	ret = cut_flags(data);
	free(data.primlist);
	free(data.seclist);
	va_end(data.arg);
	return (ret);
}
