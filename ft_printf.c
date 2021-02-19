/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:50:19 by agirona           #+#    #+#             */
/*   Updated: 2021/02/19 16:52:31 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	ft_putstr("Espace = ");
	ft_putnbr(data.space);
	ft_putchar('\n');
	ft_putchar('\n');
}

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

int		u_preclen_is_upper(t_flags *data, long long nb, char *tmp, int wich)
{
	int		print;
	int		ret;
	int		zero;
	int		nblen;

	nblen = data->nbsize;
	ret = 0;
	print = (nb == 0 && data->precision == 1 && data->preclen == 0) ? 1 : 0;
	zero = data->preclen - nblen;
	if (wich == 1 && data->preclen < 0)
		zero = data->fillen - nblen;
	if (wich == 2 && data->preclen < 0)
		zero = data->space - data->nbsize;
	if (wich != 2)
		ret = print_char(zero + print, '0');
	else if (wich == 2 && data->preclen > data->space)
		ret = print_char(zero + print, '0');
	else if (wich == 2)
		ret = print_char(zero + print, ' ');
	ret += nblen;
	if (print == 0)
		ft_putstr(tmp);
	return (ret);
}

int		ft_printf(const char *str, ...)
{
	va_list		arg;
	int			ret;
	t_flags		data;

	if (flags_init(&data.primlist, "cspdiuxX%", &data.seclist, "-0.*") == 0)
		return (0);
	va_start(arg, str);
	data.form = (char *)str;
	if (!data.form)
		return (0);
	ret = cut_flags(data, arg);
	free(data.primlist);
	free(data.seclist);
	va_end(arg);
	return (ret);
}
