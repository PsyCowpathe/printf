# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agirona <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/04 07:55:45 by agirona           #+#    #+#              #
#    Updated: 2021/02/19 15:42:53 by agirona          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

SRCS	= ft_printf.c parsing.c init.c printf_utils.c hex_conv.c id_conv.c \
		  advanced_id_conv.c u_conv.c psc_conv.c ft_putnbr_base.c \
		  advanced_u_conv.c

OBJS	= ${SRCS:.c=.o}

INC		= libft.h

CFLAGS	= -Wall -Wextra -Werror -I ${INC} -c

%.o: %.c ${INC}
	gcc $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME) :	${OBJS} 
			$(MAKE)	-C libft
			cp libft/libft.a $(NAME)
			ar rc $(NAME) ${OBJS}

clean:
			rm -f ${OBJS} ${BOBJS}
			$(MAKE)	-C libft clean

fclean:		clean
			rm -f $(NAME)
			$(MAKE)	-C libft fclean

re:			fclean all
			$(MAKE)	-C libft re

.PHONY:		all clean fclean re
