/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:16:02 by agirona           #+#    #+#             */
/*   Updated: 2021/02/02 17:17:16 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

int		start_conv(t_flags data, va_list arg)
{
	if (data.primary == 's')
		string_conv(data, arg);
	else if (data.primary == 'd')
		int_conv(data, arg);
	else if (data.primary == 'i')
		int_conv(data, arg);
	else if (data.primary == 'c')
		char_conv(data, arg);
	else if (data.primary == 'u')
		unsigned_conv(data, arg);
	else if (data.primary == 'p')
		address_conv(data, arg);
	else if (data.primary == 'x' || data.primary == 'X')
		hex_conv(data, arg);
	return (1);
}

int		set_struct(t_flags data, va_list arg, char *cut)
{
	int		i;

	i = 0;
	data.align = 0;
	data.fill = 0;
	data.precision = 0;
	data.size = 0;
	data.fillen = 0;
	data.preclen = 0;
	data.width = 0;
	data.space = 0;
	while (cut[i])
	{
		if (cut[i] >= '1' && cut[i] <= '9')
		{
			if ((data.space = get_nb(arg, cut, &i)) == -1)
				return (0);
		}
		else if (cut[i] == '-')
		{
			data.align = 1;
		}
		else if (cut[i] == '0')
		{
			data.fill = 1;
			if ((data.fillen = get_nb(arg, cut, &i)) == -1)
				return (0);
		}
		else if (cut[i] == '.')
		{
			data.precision = 1;
			if ((data.preclen = get_nb(arg, cut, &i)) == -1)
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

/*int		cut_flags(t_flags data, va_list arg)
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
				if (ret != (int)ft_strlen(cut))
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
			ft_putchar(data.form[i++]);
	}
	return (1);
}*/
