/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 06:32:22 by agirona           #+#    #+#             */
/*   Updated: 2021/02/04 12:37:22 by agirona          ###   ########lyon.fr   */
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

void	struct_init(t_flags *data)
{
	data->align = 0;
	data->fill = 0;
	data->precision = 0;
	data->fillen = 0;
	data->preclen = 0;
	data->space = 0;
}
