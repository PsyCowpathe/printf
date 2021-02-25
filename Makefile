# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agirona <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/04 07:55:45 by agirona           #+#    #+#              #
#    Updated: 2021/02/25 17:38:36 by agirona          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

SRCS	= ft_printf.c parsing.c init.c printf_utils.c hex_conv.c id_conv.c \
		  advanced_id_conv.c u_conv.c psc_conv.c ft_putnbr_base.c \
		  advanced_u_conv.c secondary.c

BSRCS	= ft_printf_bonus.c parsing_bonus.c init_bonus.c printf_utils_bonus.c \
		  hex_conv_bonus.c id_conv_bonus.c advanced_id_conv_bonus.c \
		  u_conv_bonus.c psc_conv_bonus.c ft_putnbr_base_bonus.c \
		  advanced_u_conv_bonus.c secondary_bonus.c bonus.c

OBJS	= ${SRCS:.c=.o}

BOBJS	= ${BSRCS:.c=.o}

BDIR	= bonus

BOBJS_PATH	= $(addprefix $(BDIR)/, $(BOBJS))

INC		= libft.h

CFLAGS	= -Wall -Wextra -Werror -I ${INC} -c

%.o: %.c ${INC}
	gcc $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME) :	${OBJS} 
			$(MAKE)	-C libft
			cp libft/libft.a $(NAME)
			ar rc $(NAME) ${OBJS}

bonus:		${BOBJS_PATH}
			$(MAKE)	-C libft
			cp libft/libft.a $(NAME)
			ar rc $(NAME) $(BOBJS_PATH)

clean:
			rm -f ${OBJS} ${BOBJS_PATH}
			$(MAKE)	-C libft clean

fclean:		clean
			rm -f $(NAME)
			$(MAKE)	-C libft fclean

re:			fclean all
			$(MAKE)	-C libft re

.PHONY:		all clean fclean re bonus
