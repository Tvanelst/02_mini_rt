# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/28 18:19:17 by tvanelst          #+#    #+#              #
#    Updated: 2021/07/12 10:32:41 by tvanelst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c color.c user_event.c draw_pixel.c \
			add_element1.c sphere.c plane.c cylinder.c clean_exit.c

MAIN	=	process_input.c

BONUS	=	process_input_bonus.c

OBJS	=	${addprefix srcs/, ${SRCS:.c=.o}}

OMAIN	=	${addprefix srcs/, ${MAIN:.c=.o}}

OBONUS	=	${addprefix srcs/, ${BONUS:.c=.o}}

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -Iincludes -Ilibft -Iminilibx_mms_20200219

NAME	=	miniRT

RM		=	rm -f

$(NAME)	:	${OBJS} ${OMAIN}
			$(MAKE) all -C libft
			$(MAKE) all -C minilibx_mms_20200219
			mv minilibx_mms_20200219/libmlx.dylib libmlx.dylib
			${CC} ${OBJS} ${OMAIN} -L. -lmlx -Llibft -lft -framework OpenGL -framework AppKit -lz -o ${NAME}

bonus	:	${NAME} ${OBONUS}
			${CC} ${OBJS} ${OBONUS} -L. -lmlx -Llibft -lft -framework OpenGL -framework AppKit -lz -o ${NAME}

all		:	bonus

clean	:
			${RM} ${OBJS} ${OBONUS} ${OMAIN}
			$(MAKE) clean -C libft
			$(MAKE) clean -C minilibx_mms_20200219

fclean	:	clean
			${RM} ${NAME}
			${RM} libmlx.dylib
			$(MAKE) fclean -C libft

re		:	fclean all

.PHONY	:	all bonus clean fclean re