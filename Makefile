# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/30 08:13:49 by adeflers          #+#    #+#              #
#    Updated: 2025/05/30 08:13:49 by adeflers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cube3D

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c \
	   fun.c \
	   init.c \
	   utils.c

OBJ_DIR = obj

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

MLX_PATH = ./minilibx-linux
MLX = $(MLX_PATH)/libmlx_Linux.a

INCLUDES = -I$(LIBFT_PATH) -I$(MLX_PATH)

all: 		$(NAME)

$(NAME):	$(LIBFT) $(MLX) $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) $(INCLUDES) -lXext -lX11 -lm

$(OBJ_DIR)/%.o: %.c
			mkdir -p $(OBJ_DIR)
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
		make -C $(LIBFT_PATH) all

$(MLX):
		git clone https://github.com/42paris/minilibx-linux.git $(MLX_PATH) || true
		make -C $(MLX_PATH) all

clean:
		make -C $(LIBFT_PATH) clean
		make -C $(MLX_PATH) clean
		rm -rf $(OBJ_DIR)
		rm -rf $(MLX_PATH)

fclean:		clean
		make -C $(LIBFT_PATH) fclean
		rm -rf $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
