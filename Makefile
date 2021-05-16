# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/28 18:19:17 by tvanelst          #+#    #+#              #
#    Updated: 2021/05/15 10:52:03 by tvanelst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c color.c process_input.c user_event.c draw_pixel.c save_bmp.c \
			add_element1.c triangle.c sphere.c plane.c square.c cylinder.c \
			rotations.c clean_exit.c

OBJS	=	${addprefix srcs/, ${SRCS:.c=.o}}

OBONUS	=	${BONUS:.c=.o}

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -Iincludes -Iminilibx_mms_20200219 -g

NAME	=	mini_rt

RM		=	rm -f

$(NAME)	:	${OBJS}
			$(MAKE) all -C libft
			$(MAKE) all -C minilibx_mms_20200219
			mv minilibx_mms_20200219/libmlx.dylib libmlx.dylib
			${CC} ${OBJS} -L. -lmlx -Llibft -lft -framework OpenGL -framework AppKit -lz -o  ${NAME}

bonus	:	${NAME}

all		:	bonus

clean	:
			${RM} ${OBJS} ${OBONUS}
			$(MAKE) clean -C libft
			$(MAKE) clean -C minilibx_mms_20200219

fclean	:	clean
			${RM} ${NAME}
			${RM} libmlx.dylib
			$(MAKE) fclean -C libft

re		:	fclean all