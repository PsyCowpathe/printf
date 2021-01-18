/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:50:19 by agirona           #+#    #+#             */
/*   Updated: 2021/01/18 17:45:38 by agirona          ###   ########lyon.fr   */
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
	while (cut[i])
	{
		if (is_vip(data.primlist, cut[i]) == 1)
			return (1);
		if (is_vip(data.seclist, cut[i]) == 0 && !(cut[i] >= '0' && cut[i] <= '9'))
			return (0);
		i++;
	}
	return (0);
}

int		get_nb(char *cut, int *i)
{
	int		c;
	char	*tmp;

	c = *i + 1;
	while (cut[c] && (cut[c] >= '0' && cut[c] <= '9'))
		c++;
	if ((tmp = malloc(sizeof(char) * c)) == NULL)
	{			
		free(cut);
		return (-1);
	}
	c = 0;
	*i += 1;
	while (cut[*i] && (cut[*i] >= '0' && cut[*i] <= '9'))
	{
		tmp[c] = cut[*i];
		*i += 1;
		c++;
	}
	tmp[c] = '\0';
	c = ft_atoi(tmp);
	free(tmp);
	return (c);
}

void	print_struct(t_flags data)
{
	ft_putstr("Primary = ");
	ft_putchar(data.primary);	
	ft_putchar('\n');
	ft_putstr("Alignement = ");
	ft_putnbr(data.align);
	ft_putchar('\n');
	ft_putstr("Remplissage = ");
	ft_putnbr(data.fill);
	ft_putstr(" Len = ");
	ft_putnbr(data.fillen);
	ft_putchar('\n');
	ft_putstr("Precision = ");
	ft_putnbr(data.precision);
	ft_putstr(" Len = ");
	ft_putnbr(data.preclen);
	ft_putchar('\n');
	ft_putstr("Taille = ");
	ft_putnbr(data.size);
	ft_putstr(" Len = ");
	ft_putnbr(data.width);
	ft_putchar('\n');
	ft_putchar('\n');
}

int		set_struct(t_flags data, va_list arg, char *cut)
{
	(void)arg;
	int		i;

	i = 0;
	data.align = 0;
	data.fill = 0;
	data.precision = 0;
	data.size = 0;
	data.fillen = 0;
	data.preclen = 0;
	data.width = 0;
	while (cut[i])
	{
		if (cut[i] == '-')
			data.align = 1;
		else if (cut[i] == '0')
		{
			data.fill = 1;
			if ((data.fillen = get_nb(cut, &i)) == -1)
				return (0);
		}
		else if (cut[i] == '.')
		{
			data.precision = 1;
			if ((data.preclen = get_nb(cut, &i)) == -1)
				return (0);
		}
		else if (cut[i] == '*')
		{
			data.size = 1;
			if ((data.width = get_nb(cut, &i)) == -1)
				return (0);
		}
		i++;
	}
	data.primary = cut[i - 1];
	print_struct(data);
	return (1);
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
			i++;
			while (data.form[i + len] && data.form[i + len] != '%')
				len++;
			if ((cut = malloc(sizeof(char) * len + 1)) == NULL)
			{
				free(data.primlist);
				free(data.seclist);
				return (0);
			}
			len = 0;
			while (data.form[i] && data.form[i] != '%')
			{
				cut[len] = data.form[i];
				len++;
				i++;
			}
			cut[len] = '\0';
			if (verif_flags(data, cut) == 1)
			{
				if (set_struct(data, arg, cut) == 0)
					return (0);
			}
			else
				ft_putstr(cut);
			free(cut);
		}
		else
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
