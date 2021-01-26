/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 04:56:56 by agirona           #+#    #+#             */
/*   Updated: 2020/12/04 04:57:05 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i != n)
	{
		dest[i] = src[i];
		i++;
	}
	if ((i = ft_strlen(src)) < n)
	{
		while (i < n)
			dest[i++] = '\0';
	}
	return (dest);
}
