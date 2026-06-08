# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/04 13:32:58 by lchapot           #+#    #+#              #
#    Updated: 2026/06/08 14:03:30 by lchapot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME  = cub3d

SRCS := parse.c grid.c init.c map.c utils.c split.c free.c

OBJDIR   := .objs
SRC_FILES := $(SRCS)
OBJ_FILES := $(addprefix $(OBJDIR)/,$(notdir $(SRC_FILES:.c=.o)))

CC = cc
CFLAGS = -Wall -Wextra -Werror 

HEADER := parsing.h

GREEN := \033[0;32m
CYAN := \033[0;36m
RESET := \033[0m
BIG_GREEN :=\033[1;32m
On_Green=\033[42m
UBlack=\033[4;30m
Yellow=\033[0;33m

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(OBJ_FILES) -o $@
	@echo "⊹ ࣪ ﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏﹏ ࣪ ˖"
	@echo "$(UBlack)$(On_Green)Executable created ✔$(RESET)"

# Règle générique pour compiler .c → .o dans build/
$(OBJDIR)/%.o: %.c $(HEADER) Makefile | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BIG_GREEN)[OK] $(CYAN)Compilation $<$(RESET)"

$(OBJDIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJDIR) 
	@echo "$(CYAN)Objects cleaned ✔$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(CYAN)Full clean done ✔$(RESET)"

re: fclean all

.PHONY: all clean fclean re

# NAME        = cube3D
# CC          = cc
# CFLAGS      = -Wall -Wextra -Werror

# # Dossiers et Fichiers
# SRC_DIR     = .
# OBJ_DIR     = obj
# INC_DIR     = includes

# SRCS        = srcs/main.c \
# 			  srcs/init.c \
# 			  srcs/utils.c \
# 			  srcs/parsing/parse.c\
# 			  srcs/parsing/grid.c \
# 			  srcs/parsing/init.c \
# 			  srcs/parsing/map.c \
# 			  srcs/parsing/utils.c \
# 			  srcs/parsing/split.c \
# 			  srcs/parsing/free.c \
# # 			  srcs/draw_map.c \
# # 			  srcs/player.c \

# OBJS        = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# # Bibliothèques
# LIBFT_PATH  = ./libft
# LIBFT       = $(LIBFT_PATH)/libft.a

# MLX_PATH    = ./minilibx-linux
# MLX         = $(MLX_PATH)/libmlx_Linux.a

# # Flags d'inclusion (compilation)
# INCLUDES    = -I$(INC_DIR) -I$(LIBFT_PATH) -I$(MLX_PATH)

# # Flags de liaison (linker)
# LDFLAGS     = -L$(LIBFT_PATH) -lft -L$(MLX_PATH) -lmlx_Linux -lXext -lX11 -lm

# GREEN := \033[0;32m
# CYAN := \033[0;36m
# RESET := \033[0m
# BIG_GREEN :=\033[1;32m
# On_Green=\033[42m
# UBlack=\033[4;30m
# Yellow=\033[0;33m

# all: $(NAME)

# # Link final
# $(NAME): $(LIBFT) $(MLX) $(OBJS)
# 	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
# 	s@echo "$(UBlack)$(On_Green)Executable created ✔$(RESET)"

# # Compilation des objets + dépendance stricte au dossier 'includes'
# $(OBJ_DIR)/%.o: %.c $(INC_DIR)/cube3d.h
# 	@mkdir -p $(dir $@)
# 	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
# 	@echo "$(BIG_GREEN)[OK] $(CYAN)Compilation $<$(RESET)"

# # Build Libft
# $(LIBFT):
# 	@make --no-print-directory -C $(LIBFT_PATH) all

# $(MLX):
# 	@if [ ! -d "$(MLX_PATH)" ]; then \
# 		echo "Clonage de la MinilibX..."; \
# 		git clone https://github.com/42paris/minilibx-linux.git $(MLX_PATH); \
# 		rm -rf $(MLX_PATH)/.git; \
# 		echo "Dossier .git de la MLX supprimé avec succès."; \
# 	@make -C $(MLX_PATH) all

# clean:
# 	@make -C $(LIBFT_PATH) clean
# 	@if [ -d "$(MLX_PATH)" ]; then make -C $(MLX_PATH) clean; fi
# 	@rm -rf $(OBJ_DIR)
# 	@echo "$(CYAN)Objects cleaned ✔$(RESET)"

# fclean: clean
# 	@make -C $(LIBFT_PATH) fclean
# 	@rm -f $(NAME)
# 	@echo "$(CYAN)Full clean done ✔$(RESET)"
# 	@# Évite de supprimer le dossier MLX s'il fait partie de ton repo, on nettoie juste le binaire si besoin

# re: fclean all

# .PHONY: all clean fclean re
