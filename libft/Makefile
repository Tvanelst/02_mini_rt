# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/05 17:48:42 by tvanelst          #+#    #+#              #
#    Updated: 2021/05/01 13:29:21 by tvanelst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_isalpha.c ft_memccpy.c ft_memmove.c ft_strlcpy.c ft_strrchr.c \
			ft_atoi.c ft_isascii.c ft_memchr.c  ft_memset.c  ft_strlen.c  \
			ft_tolower.c ft_bzero.c ft_isdigit.c ft_memcmp.c  ft_strchr.c \
			ft_strncmp.c ft_toupper.c ft_isalnum.c ft_isprint.c ft_memcpy.c \
			ft_strlcat.c ft_strnstr.c ft_calloc.c ft_strdup.c ft_substr.c \
			ft_strjoin.c ft_strtrim.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
			ft_strmapi.c ft_split.c ft_itoa.c ft_putnbr_fd.c get_next_line.c \
			get_next_line_utils.c ft_atod.c ft_atov.c

BONUS	=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
			ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_vec_sum.c \
			ft_vec_difference.c ft_vec_product.c ft_vec_quotient.c \
			ft_vec_scalar_product.c ft_vec_norm2.c ft_vec_normalise.c \
			ft_vec_get_normalised.c ft_is_space.c

OBJS	=	${SRCS:.c=.o}

OBONUS	=	${BONUS:.c=.o}

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

NAME	=	libft.a

RM		=	rm -f

$(NAME)	:	${OBJS}
			ar rc ${NAME} ${OBJS}
			ranlib ${NAME}

bonus	:	${NAME} ${OBONUS}
			ar rc ${NAME} ${OBONUS}
			ranlib ${NAME}

all		:	bonus

clean	:
			${RM} ${OBJS} ${OBONUS}

fclean	:	clean
			${RM} ${NAME}

re		:	fclean all