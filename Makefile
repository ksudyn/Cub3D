# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/25 20:00:22 by ksudyn            #+#    #+#              #
#    Updated: 2025/10/01 21:00:13 by pablalva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 

LIBFT_DIR = ./libft
MLX_DIR = ./minilibx-linux
INC_DIR = ./includes

SRCS =	src/parse/check_map.c\
		src/parse/dimensions.c\
		src/parse/flood_fill.c\
		src/parse/load_map.c\
		src/parse/normalize_map.c\
		src/parse/texture_color.c\
		src/parse/texture_line.c\
		src/parse/utils_parse.c\
		src/parse/validate_map.c\
		src/init.c\
		src/cub3d.c\
		src/load_textures.c\
		src/main.c\
		src/error.c\
		src/raycasting/collision.c\
		src/raycasting/math_utils.c\
		src/raycasting/player_move.c\
		src/raycasting/ray_player.c\
		src/raycasting/raycasting_cast.c\
		src/raycasting/raycasting_horiz.c\
		src/raycasting/raycasting_vert.c\
		src/raycasting/render_frame.c\
		src/mini_map.c\
		src/raycasting/player_rotate.c\
		src/raycasting/draw_vertical.c\
	

OBJS = $(SRCS:.c=.o)

INCLUDES = -I./includes -I./libft -I./minilibx-linux

LIBFT_LIB = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a
LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

$(MLX_LIB):
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
