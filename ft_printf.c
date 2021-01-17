/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:50:19 by agirona           #+#    #+#             */
/*   Updated: 2021/01/17 17:51:53 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>

int		flags_init(char **primary, char *plist, char **secondary, char *slist)
{
	int		i;

	i = -1;
	if ((*primary = malloc(sizeof(char) * FPRIMARY + 1)) == NULL)
		return (0);
	if ((*secondary = malloc(sizeof(char) * FSECONDARY + 1)) == NULL)
	{
		free(*primary);
		return (0);
	}
	while (plist[++i])
		primary[0][i] = plist[i];
	primary[0][i] = '\0';
	i = -1;
	while (slist[++i])
		secondary[0][i] = slist[i];
	secondary[0][i] = '\0';
	return (1);
}

int		is_vip(char *list, char c)
{
	int		i;

	i = 0;
	while (list[i])
	{
		if (c == list[i])
			return (1);
		i++;
	}
	return (0);
}

int		verif_flags(t_flags data, char *cut)
{
	int		i;

	i = 0;
	while (cut[i] && is_vip(data.primlist, cut[i]) != 1)
	{
		if (is_vip(data.seclist, cut[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	set_struct(t_flags data, va_list arg, char *cut)
{
	(void)data;
	(void)arg;
	(void)cut;
}

int		cut_flags(t_flags data, va_list arg)
{
	int		i;
	int		len;
	char	*cut;

	i = 0;
	while (data.form[i])
	{
		if (data.form[i] == '%')
		{
			len = 0;
			while (data.form[i + len + 1] && data.form[i + len + 1] != '%')
				len++;
			if ((cut = malloc(sizeof(char) * len + 1)) == NULL)
			{
				free(data.primlist);
				free(data.seclist);
				return (0);
			}
			len = 0;
			while (data.form[i] && data.form[i] != '%')
				cut[len++] = data.form[i++];
			ft_putstr(cut);
			if (verif_flags(data, cut) == 1)
				set_struct(data, arg, cut);
			else
				ft_putstr(cut);
		}
		i++;
	}
	return (1);
}

void	ft_printf(const char *str, ...)
{
	va_list		arg;
	t_flags		data;

	if (flags_init(&data.primlist, "cspdiuxX%", &data.seclist, "-0.*") == 0)
		return ;
	va_start(arg, str);
	data.form = (char *)str;
	if (cut_flags(data, arg) == 0)
		return ;
}

int		main(int argc, char **argv)
{
	(void)argc;
	ft_printf(argv[1], 58.123, "coucou", 456);
	ft_putchar('\n');
	printf(argv[1], 58.123, "coucou", 456);
}
