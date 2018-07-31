# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmervin <tmervin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/11 13:50:29 by tmervin           #+#    #+#              #
#    Updated: 2018/07/24 18:12:11 by jostraye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= rtv1

SRC_PATH	:= src
SRC_NAME	:=	main.c								\
				images.c							\
				init.c								\
				intersections.c						\
				maths_vectors.c						\
				shadows.c							\
				color_helpers.c						\
				color_helpers2.c					\
				raytracer.c							\
				keyboard.c							\
				parser.c							\
				parser_errors.c						\
				parser_functions.c					\
				free_functions.c					\
				usage.c								\
				maths_rot.c							\
				maths_functions.c					\
				create_bmp.c						\
				filters.c							\
				texture_parser.c					\
				textures_cylinder_cone.c			\
				textures_sphere_plane.c				\
				textures.c							\
				antialiasing.c						\
				cartooning.c						\
				normal_vectors.c					\
				palette.c							\
				blind_lights.c

OBJ_PATH	:= obj
HEAD_PATH	:= ./includes


UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	MLX_DIR	=	minilibx_linux
endif
ifeq ($(UNAME_S), Darwin)
	MLX_DIR	=	minilibx_macos
endif

CPPFLAGS	:= -Iincludes -I./libft/includes -I ./$(MLX_DIR)

LDFLAGS		:= -Llibft/
LDLIBS		:= -lft
ifeq ($(UNAME_S), Linux)
	MLX_PATH := ./minilibx_linux
	MINILIBX :=	-L./minilibx_linux -lmlx -lXext -lX11 -lm -pthread
endif
ifeq ($(UNAME_S), Darwin)
	MLX_PATH := ./minilibx_macos
	MINILIBX	:= -L ./minilibx_macos/ -lmlx -framework OpenGL -framework Appkit
endif

CC			:= gcc -Werror -Wall -Wextra -fsanitize=address -fno-omit-frame-pointer
# CC			:= gcc -Werror -Wall -Wextra
OBJ_NAME	:= $(SRC_NAME:.c=.o)

SRC			:= $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ			:= $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	make -C $(MLX_PATH)
	$(CC) $^ $(LDFLAGS) $(LDLIBS) $(MINILIBX) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CPPFLAGS) -o $@ -c $<

norm:
	norminette $(HEAD_PATH)
	norminette $(SRC)

clean:
	make clean -C libft/
	make clean -C $(MLX_PATH)
	rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	make fclean -C libft/
	rm -fv $(NAME)

re: fclean all

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)
