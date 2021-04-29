# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/28 18:19:17 by tvanelst          #+#    #+#              #
#    Updated: 2021/04/29 09:36:59 by tvanelst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	srcs/main.c

OBJS	=	${SRCS:.c=.o}

OBONUS	=	${BONUS:.c=.o}

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -Iincludes -Iminilibx_opengl_20191021

NAME	=	mini_rt

RM		=	rm -f


$(NAME)	:	${OBJS}
			$(MAKE) all -C libft
			$(MAKE) all -C minilibx_opengl_20191021
			${CC} ${OBJS} -Llibft -lft -Lminilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit -lz -o  ${NAME}

bonus	:	${NAME}

all		:	bonus

clean	:
			${RM} ${OBJS} ${OBONUS}
			$(MAKE) clean -C libft
			$(MAKE) clean -C minilibx_opengl_20191021

fclean	:	clean
			${RM} ${NAME}
			$(MAKE) fclean -C libft

re		:	fclean all