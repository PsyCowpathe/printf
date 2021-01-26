# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agirona <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/26 16:22:31 by agirona           #+#    #+#              #
#    Updated: 2020/12/05 09:10:08 by agirona          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRCS	= ft_atoi.c ft_memcmp.c ft_putendl_fd.c ft_strchr.c ft_strmapi.c ft_substr.c \
		  ft_bzero.c ft_isdigit.c ft_memcpy.c ft_strdup.c ft_strncmp.c ft_tolower.c \
		  ft_calloc.c ft_isprint.c ft_memmove.c ft_putnbr_fd.c ft_strjoin.c \
		  ft_toupper.c ft_isalnum.c ft_itoa.c ft_memset.c ft_strlcat.c ft_strnstr.c \
		  ft_isalpha.c ft_memccpy.c ft_putstr_fd.c ft_strlcpy.c ft_strrchr.c \
		  ft_isascii.c ft_memchr.c ft_putchar_fd.c ft_split.c ft_strlen.c ft_strtrim.c \

BSRCS	= ft_ischar_bonus.c ft_strnew_bonus.c ft_putchar_bonus.c ft_putstr_bonus.c \
		  ft_putnbr_bonus.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		  ft_lstadd_back.c ft_lstdelone.c  ft_lstclear.c ft_lstiter.c ft_lstmap.c \
		  ft_sort_int_tab_bonus.c ft_swap_bonus.c ft_putstr_non_printable_bonus.c \
		  ft_putnbr_base_bonus.c ft_strncpy_bonus.c

OBJS	= ${SRCS:.c=.o}

BOBJS	= ${BSRCS:.c=.o}

INC		= libft.h

CFLAGS	= -Wall -Wextra -Werror -I ${INC} -c

%.o: %.c ${INC}
	gcc $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME) :	${OBJS}
			ar rc $(NAME) ${OBJS}

bonus	:	$(NAME) ${BOBJS}
			ar urc $(NAME) ${BOBJS}

clean:
			rm -f ${OBJS} ${BOBJS}

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
