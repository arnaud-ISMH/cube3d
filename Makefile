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

NAME        = cube3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

# Dossiers et Fichiers
SRC_DIR     = .
OBJ_DIR     = obj
INC_DIR     = includes

SRCS        = srcs/main.c \
			  srcs/init.c \
			  srcs/utils.c \
			  srcs/draw_map.c \
			  srcs/player.c

OBJS        = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Bibliothèques
LIBFT_PATH  = ./libft
LIBFT       = $(LIBFT_PATH)/libft.a

MLX_PATH    = ./minilibx-linux
MLX         = $(MLX_PATH)/libmlx_Linux.a

# Flags d'inclusion (compilation)
INCLUDES    = -I$(INC_DIR) -I$(LIBFT_PATH) -I$(MLX_PATH)

# Flags de liaison (linker)
LDFLAGS     = -L$(LIBFT_PATH) -lft -L$(MLX_PATH) -lmlx_Linux -lXext -lX11 -lm

# --- RÈGLES ---

all: $(NAME)

# Link final
$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

# Compilation des objets + dépendance stricte au dossier 'includes'
$(OBJ_DIR)/%.o: %.c $(INC_DIR)/cube3d.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build Libft
$(LIBFT):
	@make -C $(LIBFT_PATH) all

$(MLX):
	@if [ ! -d "$(MLX_PATH)" ]; then \
		echo "Clonage de la MinilibX..."; \
		git clone https://github.com/42paris/minilibx-linux.git $(MLX_PATH); \
		rm -rf $(MLX_PATH)/.git; \
		echo "Dossier .git de la MLX supprimé avec succès."; \
	fi
	@make -C $(MLX_PATH) all
clean:
	@make -C $(LIBFT_PATH) clean
	@if [ -d "$(MLX_PATH)" ]; then make -C $(MLX_PATH) clean; fi
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)
	@# Évite de supprimer le dossier MLX s'il fait partie de ton repo, on nettoie juste le binaire si besoin

re: fclean all

.PHONY: all clean fclean re
