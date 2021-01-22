/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:50:19 by agirona           #+#    #+#             */
/*   Updated: 2021/01/22 17:44:22 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>
#include <limits.h>

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
			return (i);
		if (is_vip(data.seclist, cut[i]) == 0 && !(cut[i] >= '0' && cut[i] <= '9'))
			return (-1);
		i++;
	}
	return (-1);
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
	*i -= 1;
	tmp[c] = '\0';
	c = ft_atoi(tmp);
	free(tmp);
	return (c);
}

int		advanced_int_conv(t_flags data, int size, int nb)
{
	int		i;
	int		c;
	char	*res;
	char	*tmp;

	i = 0;
	c = 0;
	if (nb < 0)
		i = 1;
	if ((res = malloc(sizeof(char) * size + i + 1)) == NULL)
		return (0);
	while (i < data.preclen - ft_nblen(nb))
		res[i++] = '0';
	tmp = ft_itoa(nb);
	while (tmp[c])
		res[i++] = tmp[c++];
	while (i < data.fillen)
		res[i++] = ' ';
	res[i] = '\0';
	ft_putstr(res);
	return (1);
}

int		int_conv(t_flags data, va_list arg)
{
	char	*res;
	int		size;
	int		nb;
	int		i;
	int		c;

	size = (data.preclen > data.fillen) ? data.preclen : data.fillen;
	nb = (int)va_arg(arg, int);
	i = 0;
	if (data.align == 1)
		return (advanced_int_conv(data, size, nb));
	if (nb < 0)
		i = 1;
	if ((res = malloc(sizeof(char) * size + i + 1)) == NULL)
		return (0);
	if (nb < 0)
		res[i] = '-';
	c = (data.fill = 1 && data.precision == 0) ? ft_nblen(nb) - 1 : -1;
	if (nb < 0 && data.fillen > data.preclen)
		c++;
	while (++c < data.fillen - data.preclen)
		res[i++] = (data.fill == 1 && data.precision == 0) ? '0' : ' ';
	while (c++ < size - ft_nblen(nb))
		res[i++] = '0';
	res[i] = '\0';
	ft_putstr(res);
	ft_putnbr(ft_abs(nb));
	return (1);
}

void	string_conv(t_flags data, va_list arg)
{
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	tmp = va_arg(arg, char *);
	res = malloc(sizeof(char) * data.fillen + 1);
	while (i < data.fillen - ft_strlen(tmp))
		res[i++] = (data.align == 1) ? ' ' : '0';
	res[i] = '\0';
	if (data.align == 1)
	{
		ft_putstr(tmp);
		ft_putstr(res);
	}
	else
	{
		ft_putstr(res);
		ft_putstr(tmp);
	}
	free(res);
}

int		start_conv(t_flags data, va_list arg)
{
	int		nb;

	if (data.primary == 's')
	{
		string_conv(data, arg);
	}
	else if (data.primary == 'd')
	{
		nb = va_arg(arg, int);
		ft_putnbr(nb);
	}
	else if (data.primary == 'i')
	{
		if (int_conv(data, arg) == 0)
			return (0);
	}
	else if (data.primary == 'c')
	{
		nb = (int)va_arg(arg, int);
		ft_putchar(nb);
	}
	else
	{
		ft_putstr("pas encore fais");
		va_arg(arg, void*);
	}
	return (0);
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
		{
			data.align = 1;
		}
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
	if (start_conv(data, arg) == 0)
		return (0);
	//print_struct(data); //delete la fonction aussi
	return (1);
}

int		cut_flags(t_flags data, va_list arg)
{
	int		i;
	int		len;
	int		ret;
	char	*cut;
	char	*save;


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
			if ((ret = verif_flags(data, cut)) >= 0)
			{
				save = NULL;
				if (ret != ft_strlen(cut))
				{
					save = ft_strdup(cut + ret + 1);
					cut[ret + 1] = '\0';
				}
				if (set_struct(data, arg, cut) == 0)
				{
					if (save != NULL)
						free(save);
					free(cut);
					return (0);
				}
				ft_putstr(save);
				if (save != NULL)
					free(save);
			}
			else
				ft_putstr(cut);
			free(cut);
		}
		else
	//	ft_putchar('\n');
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
	ft_printf(argv[1], 456);
	printf(argv[1], 456);
	ft_putchar('\n');
}
