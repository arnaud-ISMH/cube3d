# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/04 13:32:58 by lchapot           #+#    #+#              #
#    Updated: 2026/06/04 15:07:00 by lchapot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME  = cub3d

SRCS := parse.c grid.c init.c map.c utils.c

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
