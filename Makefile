# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/30 08:13:49 by adeflers          #+#    #+#              #
#    Updated: 2026/06/11 15:36:16 by lchapot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cube3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3 #-fsanitize=address

# Dossiers et Fichiers
SRC_DIR     = .
OBJ_DIR     = obj
INC_DIR     = includes

SRCS        = srcs/main.c \
			  srcs/exec/init.c \
			  srcs/exec/utils.c \
			  srcs/exec/utils2.c \
			  srcs/exec/utils3.c \
			  srcs/exec/draw_map.c \
			  srcs/exec/minimap.c \
			  srcs/exec/raycasting.c \
			  srcs/exec/raycasting2.c \
			  srcs/exec/player.c \
			  srcs/exec/monster.c \
			  srcs/exec/monster2.c \
			  srcs/parsing/parse.c\
			  srcs/parsing/grid.c \
			  srcs/parsing/init.c \
			  srcs/parsing/map.c \
			  srcs/parsing/checkcub.c \
			  srcs/parsing/utils.c \
			  srcs/parsing/utils2.c \
			  srcs/parsing/bonus.c

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

GREEN := \033[0-;32m
CYAN := \033[0;36m
RESET := \033[0m
BIG_GREEN :=\033[1;32m
On_Green=\033[42m
UBlack=\033[4;30m
Yellow=\033[0;33m

all: $(NAME)

# Link final
$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo -e "$(UBlack)$(On_Green)Executable created ✔$(RESET)"

# Compilation des objets + dépendance stricte au dossier 'includes'
$(OBJ_DIR)/%.o: %.c $(INC_DIR)/cube3d.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo -e "$(BIG_GREEN)[OK] $(CYAN)Compilation $<$(RESET)"

# Build Libft
$(LIBFT):
	@make --no-print-directory -C $(LIBFT_PATH) all

$(MLX):
	@if [ ! -d "$(MLX_PATH)" ]; then \
		echo "Clonage de la MinilibX..."; \
		git clone https://github.com/42paris/minilibx-linux.git $(MLX_PATH); \
		rm -rf $(MLX_PATH)/.git; \
		echo "Dossier .git de la MLX supprimé avec succès."; \
	fi
	@make --no-print-directory -C $(MLX_PATH) all

clean:
	@make --no-print-directory -C $(LIBFT_PATH) clean
	@if [ -d "$(MLX_PATH)" ]; then make --no-print-directory -C $(MLX_PATH) clean; fi
	@rm -rf $(OBJ_DIR)
	@echo -e "$(CYAN)Objects cleaned ✔$(RESET)"

fclean: clean
	@make --no-print-directory -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)
	@echo -e "$(CYAN)Full clean done ✔$(RESET)"
	@# Évite de supprimer le dossier MLX s'il fait partie de ton repo, on nettoie juste le binaire si besoin

re: fclean all

.PHONY: all clean fclean re
