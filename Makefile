# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jenlee <jenlee@studekl.edu.my>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/18 23:41:47 by yolim             #+#    #+#              #
#    Updated: 2026/10/29 23:00:00 by jenlee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----- Executable names -----
NAME = cub3D
NAME_BONUS = cub3D_bonus

# ----- OS Detection -----
UNAME_S := $(shell uname -s)

# ----- Compiler and flags -----
CC = cc
CCFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

# ----- Directories -----
HEADER_DIR = includes
SRC_DIR = src
OBJ_DIR = obj
OBJ_BONUS_DIR = obj_bonus

# ----- Header file -----
HEADER_LIB = $(HEADER_DIR)/cub3d.h

# ----- Mandatory Source Files -----
SRCS = src/main.c \
       src/drawing/ceiling_and_floor.c \
       src/drawing/mlx_tools.c \
       src/parse/map_validation.c \
       src/parse/map_validation_utils.c \
       src/parse/parse.c \
       src/parse/parse_element.c \
       src/parse/parse_map.c \
       src/parse/parse_utils.c \
       src/parse/player_setting.c \
       src/parse/space_handling.c \
       src/raycast/raycast_main.c \
       src/raycast/raycast_textures.c \
       src/textures/texture.c \
       src/utils/cleanup.c \
       src/utils/controls.c \
       src/utils/exit.c

# ----- Bonus Source Files -----
SRCS_BONUS = $(SRCS) \
             src/bonus/minimap_bonus.c

# ----- Object Files -----
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS = $(SRCS_BONUS:src/%.c=$(OBJ_BONUS_DIR)/%.o)

# ----- Libft -----
LIBFT_DIR = Libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# ----- MiniLibX -----
ifeq ($(UNAME_S), Darwin)
MLX_DIR = minilibx_macos_opengl
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else ifeq ($(UNAME_S), Linux)
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
endif

# ----- Rules -----
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CCFLAGS) $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)
	@echo "Done. Mandatory executable is '$(NAME)'"

# ----- Bonus Rule -----
bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CCFLAGS) $(OBJS_BONUS) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME_BONUS)
	@echo "Done. Bonus executable is '$(NAME_BONUS)'"

# Rule to build libft library
$(LIBFT_LIB):
	@$(MAKE) -s -C $(LIBFT_DIR)

# Rule to build MiniLibX library
$(MLX_LIB):
	@$(MAKE) -s -C $(MLX_DIR)

# Compile mandatory object files
$(OBJ_DIR)/%.o: src/%.c $(HEADER_LIB)
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAGS) -I$(HEADER_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

# Compile bonus object files
$(OBJ_BONUS_DIR)/%.o: src/%.c $(HEADER_LIB)
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAGS) -DBONUS=1 -I$(HEADER_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

# ----- Clean Rules -----
clean:
	@$(RM) $(OBJ_DIR) $(OBJ_BONUS_DIR)
	@echo "Object files cleaned."
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@echo "Object files in Libft cleaned."
	@$(MAKE) -s -C $(MLX_DIR) clean
	@echo "Object files in MLX cleaned."

fclean: clean
	@$(RM) $(NAME) $(NAME_BONUS)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(MAKE) -s -C $(MLX_DIR) clean
	@echo "Full clean complete."

# ----- Rebuild Rules -----
re: fclean all

.PHONY: all clean fclean re bonus
