/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:32:45 by agirona           #+#    #+#             */
/*   Updated: 2021/01/15 19:36:52 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>

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
		if (c == secondary[i])
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

void	print_flag(char *flag, va_list param)
{
	char	*str;
	int		nb;

	if (flag[0] == 's')
	{
		str = va_arg(param, char*);
		ft_putstr(str);
	}
	else if (flag[0] == 'd')
	{
		nb = va_arg(param, int);
		ft_putnbr(nb);
	}
	else
		va_arg(param, void*);
	ft_putchar('\n');

}

void	get_flag(char *str, va_list param)
{
	int		i;
	int		d;
	int		len;
	char	*flag;
	int		c;

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
			print_flag(flag, param);
			free(flag);
			return ;
		}
		i++;
	}
}

int		parsing(const char *str, char *primary, char *secondary, va_list param)
{
	int		i;
	int		save;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '%')
				ft_putchar('%');
			save = i;
			if (check_flag(str, &i, primary, secondary) == 0)
			{
				while (str[save] && str[++save] != '%')
					ft_putchar(str[save]);
			}
			else
			{
				//ft_putstr((char *)str + save);
				get_flag((char *)str + save, param);
			}
		}
		else
			i++;
	}
	return (1);
}


int		ft_printf(const char *str, ...)
{
	va_list		param;
	char		*primary;
	char		*secondary;
	
	if (init_flag(&primary, "cspdiuxX%", &secondary, "-0.*") == 0)
		return (0);
	va_start(param, str);
	parsing(str, primary, secondary, param);
	return (1);
}

int		main(int argc, char **argv)
{
	(void)argc;
	ft_printf(argv[1], "salut", "coucou", 123);
	ft_putchar('\n');
	printf(argv[1], "salut", "coucou", 123);
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

