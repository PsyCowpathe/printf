/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:47:26 by agirona           #+#    #+#             */
/*   Updated: 2021/01/31 18:00:06 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_flags(char *form, int *i)
{
	char	*cut;
	int		size;

	size = 0;
	if (!form)
		return (NULL);
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
	while (data.form[i])
	{
		if (data.form[i] == '%')
		{
			i = i + 1;
			if ((cut = get_flags(data.form, &i)) == NULL)
				return (0);
			if (verif_flags(data, cut) >= 0)
				set_struct(data, arg, cut);
			else
				ft_putstr(cut);
		}
		else
			ft_putchar(data.form[i++]);
	}
	return (1);
}
