# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/26 13:13:47 by rbenjami          #+#    #+#              #
#    Updated: 2015/02/27 10:38:29 by rbenjami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include			libft/Makefile.sources

export	CC		=	cc

export	INC		=	-I $(PWD)/libft -I $(PWD)/lib3d

NAME			=	fractol

CFLAGS			=	-Wall -Wextra -Werror -O3 -g -pedantic

INC				+=	-I includes -I/usr/X11R6/include

HEAD			=	includes/$(NAME).h

SRC_DIR			=	srcs/

FILES			=	$(NAME).c			\
					core_engine.c		\
					core_engine_loop.c	\
					core_engine_hooks.c	\
					image.c				\
					utils.c				\
					object.c			\
					window.c			\
					mandelbrot.c		\
					julia.c				\
					burning_ship.c		\
					dragon.c			\
					julia3d.c			\
					julia3d_render.c	\

SRC				=	$(addprefix $(SRC_DIR)/, $(FILES))

OBJ				=	$(SRC:.c=.o)

LIB				=	-L./ -L/usr/X11/lib -lft -lmlx -lXext -lX11

OBJ_LIBFT		=	$(libft/SRC_LIB:.c=.o)

HEAD_LIBFT		=	libft/libft.h libft/get_next_line.h

all:			libft.a $(NAME)

libft.a:		libft/$(OBJ_LIBFT) $(HEAD_LIBFT)
	@make -C libft

$(NAME):		$(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)
	@echo ""
	@echo "\033[33m"compilation of $(NAME) : "\033[32m"Success"\033[0m"

$(OBJ):			$(HEAD) libft.a

%.o:			%.c $(HEAD)
	@echo -n .
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	@/bin/rm -f $(OBJ)
	@echo "\033[31m"Objects of $(NAME) : deleted"\033[0m"

fclean:			clean
	@/bin/rm -f $(NAME)
	@echo "\033[31m"$(NAME) : deleted"\033[0m"
	@make fclean -C libft
re:				fclean all

.PHONY:			all clean fclean re

