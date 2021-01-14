/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:32:45 by agirona           #+#    #+#             */
/*   Updated: 2021/01/14 17:26:20 by agirona          ###   ########lyon.fr   */
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

int		parsing(const char *str, char *primary, char *secondary)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (check_flag(str, &i, primary, secondary) == 0)
				return (0);
		}
		else
			i++;
	}
	return (1);
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

int		ft_printf(const char *str, ...)
{
	va_list		param;
	char		*primary;
	char		*secondary;
	
	if (init_flag(&primary, "cspdiuxX%", &secondary, "-0.*") == 0)
		return (0);
	va_start(param, str);
	if (parsing(str, primary, secondary) == 0)
	{
		ft_putstr("bad flag");
		return (0);
	}
	else
	{
		ft_putstr("good flag");
	}
	return (1);
}

int		main()
{
	printf("%40d", 123);
	ft_putchar('\n');
	ft_printf("%c.", 123, "coucou");
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

