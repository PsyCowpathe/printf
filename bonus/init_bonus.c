/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 06:32:22 by agirona           #+#    #+#             */
/*   Updated: 2021/02/25 12:13:19 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

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

void	*struct_init(t_flags *data)
{
	void	(**tabft)(t_flags*, char*, int*);

	if (((tabft) = malloc(sizeof(void*) * (FSECONDARY + 1))) == NULL)
		return (NULL);
	data->align = 0;
	data->fill = 0;
	data->precision = 0;
	data->fillen = 0;
	data->preclen = 0;
	data->space = 0;
	data->error = 0;
	data->hashtag = 0;
	data->plus = 0;
	data->setspace = 0;
	(tabft[0]) = &moin;
	(tabft[1]) = &zero;
	(tabft[2]) = &dot;
	(tabft[3]) = &asterisk;
	(tabft[4]) = &hashtag;
	(tabft[5]) = &plus;
	(tabft[6]) = &space;
	(tabft[7]) = &nombre;
	return (tabft);
}
