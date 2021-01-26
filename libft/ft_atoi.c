/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:15:49 by agirona           #+#    #+#             */
/*   Updated: 2020/12/04 18:46:51 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int				i;
	int				neg;
	long int		res;
	long int		tmp;

	i = 0;
	res = 0;
	tmp = 0;
	while (str[i] == '\r' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\t' || str[i] == '\f' || str[i] == ' ')
		i++;
	neg = (str[i] == '-') ? -1 : 1;
	i = (str[i] == '-' || str[i] == '+') ? i + 1 : i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - 48;
		if (res < tmp && neg == -1)
			return (0);
		else if (res < tmp)
			return (-1);
		tmp = res;
		i++;
	}
	return (res * neg);
}
