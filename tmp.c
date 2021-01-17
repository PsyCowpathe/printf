/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:32:45 by agirona           #+#    #+#             */
/*   Updated: 2021/01/17 16:55:07 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include "ft_printf.h"

#define FPRIMARY 9
#define FSECONDARY 4
#include <unistd.h>
#include <stdlib.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		ft_putchar(str[i++]);
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		ft_putchar('-');
		ft_putnbr(214748364);
		ft_putchar(8 + 48);
	}
	else if (nb < 0)
	{
		ft_putchar('-');
		ft_putnbr(nb * -1);
	}
	else if (nb < 10)
	{
		ft_putchar(nb + 48);
	}
	else
	{
		ft_putnbr(nb / 10);
		ft_putchar(nb % 10 + 48);
	}
}

int		ft_atoi(char *str)
{
	int		i;
	int		count;
	int		neg;
	int		res;

	count = 0;
	i = 0;
	res = 0;
	while (str[i] == '\r' || str[i] == '\n' || str[i] == '\v'
	|| str[i] == '\t' || str[i] == '\f' || str[i] == ' ')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			count++;
	}
	neg = (count % 2 == 0) ? 1 : -1;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * neg);
}

int		is_prim(char c, char *primary)
{
	int		i;

	i = 0;
	while (primary[i])
	{
		if (c == primary[i])
			return (1);
		i++;
	}
	return (0);
}

int		is_sec(char c, char *secondary)
{
	int		i;

	i = 0;
	while (secondary[i])
	{
		if (c == secondary[i] || (c >= '0' && c <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int		init_flag(char **primary, char *fprim, char **secondary, char *fsec)
{
	int		i;

	i = -1;
	if ((*primary = malloc(sizeof(char) * FPRIMARY + 1)) == NULL)
		return (0);
	if ((*secondary = malloc(sizeof(char) * FSECONDARY + 1)) == NULL)
	{
		free(*secondary);
		return (0);
	}
	while (fprim[++i])
		primary[0][i] = fprim[i];
	primary[0][i] = '\0';
	i = -1;
	while (fsec[++i])
		secondary[0][i] = fsec[i];
	secondary[0][i] = '\0';
	return (1);
}


void	print_flag(t_flags data, va_list param)
{
	char	*str;
	int		nb;

	if (data.primary == 's')
	{
		str = va_arg(param, char*);
		ft_putstr(str);
	}
	else if (data.primary == 'd')
	{
		nb = va_arg(param, int);
		ft_putnbr(nb);
	}
	else if (data.primary == 'i')
	{
		nb = (int)va_arg(param, int);
		ft_putnbr(nb);
	}
	else if (data.primary == 'c')
	{
		nb = (int)va_arg(param, int);
		ft_putchar(nb);
	}
	else
	{
		ft_putstr("pas encore fais");
		va_arg(param, void*);
	}
	ft_putchar('\n');
}

int		get_nb(char *flag)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = 0;
	tmp = NULL;
	while (flag[i] >= '0' && flag[i++] <= '9')
		len++;
	tmp = malloc(sizeof(char) * len + 1);
	i = i - len - 1;
	len = 0;
	while (flag[i] >= '0' && flag[i] <= '9')
	{
		tmp[len] = flag[i];
		len++;
		i++;
	}
	tmp[len] = '\0';
	len = ft_atoi(tmp);
	free(tmp);
	return (len);
}

void	split_flag(t_flags data, char *flag, va_list param)
{
	int		i;

	i = 0;
	data.align = 0;
	data.fill = 0;
	data.precision = 0;
	data.fillen = 0;
	data.preclen = 0;
	while (flag[i])
	{
		if (flag[i] == '-')
			data.align = 1;
		if (flag[i] == '0')
		{
			data.fill = 1;
			data.fillen = get_nb(flag + i);
		}
		if (flag[i] == '.')
		{
			data.precision = 1;
			data.preclen = get_nb(flag + i);
		}
		i++;
	}
	data.len = i;
	data.primary = flag[i - 1];
	print_flag(data, param);
}

void	get_flag(char *str, va_list param, t_flags data)
{
	int		i;
	int		d;
	int		len;
	char	*flag;
	int		c;
	(void)data;

	i = 0;
	d = 0;
	c = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			d = i + 1;
			while (str[d] && str[d] != '%')
			{
				len++;
				d++;
			}
			flag = malloc(sizeof(char) * len + 1);
			d = i + 1;
			while (str[d] && str[d] != '%')
				flag[c++] = str[d++];
			flag[len] = '\0';
			split_flag(data, flag, param);
			//print_flag(flag, param);
			free(flag);
			return ;
		}
		i++;
	}
}

int		check_flag(const char *str, int *i, char *primary, char *secondary)
{
	int		c;

	c = 0;
	*i += 1;
	while (str[*i] && is_prim(str[*i], primary) == 0)
	{
		if (is_sec(str[*i], secondary) == 0)
			return (0);
		*i += 1;
	}
	if (str[*i] == '\0')
		return (0);
	return (1);
}

int		parsing(t_flags data, va_list param)
{
	int		i;
	int		save;

	i = 0;
	while (data.form[i])
	{
		if (data.form[i] == '%')
		{
			if (data.form[i + 1] == '%')
				ft_putchar('%');
			save = i;
			if (check_flag(data.form, &i, data.primlist, data.seclist) == 0)
			{
				while (data.form[save] && data.form[++save] != '%')
					ft_putchar(data.form[save]);
			}
			else
				get_flag(data.form + save, param, data);
		}
		else
			i++;
	}
	return (1);
}

int		ft_printf(const char *str, ...)
{
	va_list		param;
	t_flags		data;

	if (init_flag(&data.primlist, "cspdiuxX%", &data.seclist, "-0.*") == 0)
		return (0);
	data.form = (char *)str;
	va_start(param, str);
	parsing(data, param);
	return (1);
}

int		main(int argc, char **argv)
{
	(void)argc;
	ft_printf(argv[1], 58.123, "coucou", 123);
	ft_putchar('\n');
	printf(argv[1], 58.123, "coucou", 123);
	return (0);
}


/*	printf("%.5d \n", 20); //00020
	printf("%.*d \n", 5,  -20); //00020
	printf("%.5s\n", "coucou"); //couco
	printf("%.3d", 20); //020
	printf("%c", 0);
	printf("%d", 1); //1
	printf("%d", 0); //
	*/

