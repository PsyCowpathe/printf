/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:33:07 by agirona           #+#    #+#             */
/*   Updated: 2021/01/17 17:51:54 by agirona          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define FPRIMARY 9
# define FSECONDARY 4

# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct	s_flags
{
	char		*form;
	char		*primlist;
	char		*seclist;
	char		primary;
	int			len;
	bool		align;
	bool		fill;
	int			fillen;
	bool		precision;
	int			preclen;
}				t_flags;

void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putnbr(int nb);
int		ft_atoi(char *str);

#endif
