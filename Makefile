# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jenlee <jenlee@studekl.edu.my>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/18 23:41:47 by yolim             #+#    #+#              #
#    Updated: 2026/06/11 15:51:39 by jenlee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----- Executable name -----
NAME = cub3D

# ----- OS Detection -----
UNAME_S := $(shell uname -s)
# print kernel name of operating system

# ----- Compiler and flags -----
CC = cc
CCFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

# ----- Directories -----
HEADER_DIR = includes
SRC_DIR = src
OBJ_DIR = obj

# ----- Header file -----
HEADER_LIB = $(HEADER_DIR)/cub3d.h

# ----- Source Files -----
SRC = $(shell find src -name "*.c")	#  need to change after all done!

# ----- Put .o Files in a dedicated folder -----
OBJS = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

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
# ifeq = if equal
# only linux need -lm bcos macOS's math library is bundled into libSystem.dylib which is always linked automatically

# ----- Rules -----
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CCFLAGS) $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)
	@echo "Done. Executable is '$(NAME)'"

# Rule to build libft library
$(LIBFT_LIB):
	@$(MAKE) -s -C $(LIBFT_DIR)

# Rule to build MiniLibX library
$(MLX_LIB):
	@$(MAKE) -s -C $(MLX_DIR)

# Rule to compile source files into object files (creates obj subfolders as needed)
# -I stands for "Include" & tells the compiler where to look for header files
# $< is the first prerequisite of the rule (main.c)
# $@ is the target of the rule (main.o)
$(OBJ_DIR)/%.o: src/%.c $(HEADER_LIB)
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAGS) -I$(HEADER_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

# ----- Bonus -----
bonus: all

# ----- Clean Rules -----
clean:
	@$(RM) $(OBJ_DIR)
	@echo "Object files cleaned."
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@echo "Object files in Libft cleaned."
	@$(MAKE) -s -C $(MLX_DIR) clean
	@echo "Object files in MLX cleaned."

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(MAKE) -s -C $(MLX_DIR) clean
	@echo "Full clean complete."

# ----- Rebuild Rules -----
re: fclean all

.PHONY: all clean fclean re bonus