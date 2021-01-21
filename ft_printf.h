/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agirona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:33:07 by agirona           #+#    #+#             */
/*   Updated: 2021/01/21 15:39:53 by agirona          ###   ########lyon.fr   */
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
	bool		size;
	int			width;
}				t_flags;

void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putnbr(int nb);
int		ft_strlen(char *str);
int		ft_atoi(char *str);
char	*ft_strdup(const char *s1);
char	*ft_itoa(int n);

#endif
