# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 20:11:52 by yadereve          #+#    #+#              #
#    Updated: 2024/03/11 17:23:56 by yadereve         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC_DIR = sources
SRC = $(wildcard $(SRC_DIR)/*.c)
LIBFT = libft/libft.a
OBJ_DIR = objects
OBJ = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))
COMPRESS = ar rcs
RM = rm -rf
KEY = press_key

#colors
GREEN = \033[1;32m
RED = \033[1;31m
BLUE = \033[1;34m
ORANGE = \033[0;33m
RESET = \033[0;0m

#MacOS
#MLX_DIR = minilibx/minilibx_opengl_20191021
#MLX_LIB = $(MLX_DIR)/libmlx.a
#MLX_INC = -I$(MLX_DIR) -I$(MLX_DIR)/libmlx
#MLX_FLAGS = -L$(MLX_DIR) -Lmlx -lmlx -framework OpenGL -framework AppKit

# Linux
MLX_DIR = minilibx/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
MLX_INC = -I$(MLX_DIR) -I$(MLX_DIR)/linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) $(LIBFT) -o $(NAME)
	@echo "$(BLUE)                  __"
	@echo ".-----.-----.    |  |.-----.-----.-----."
	@echo "|__ --|  _  |    |  ||  _  |     |  _  |"
	@echo "|_____|_____|____|__||_____|__|__|___  |"
	@echo "           |______|              |_____|$(RESET)"
	@echo "\ncreate:\t$(GREEN)$(OBJ_DIR)\n\tlibft$(RESET)"
	@echo "\ncreate:\t$(GREEN)$(OBJ_DIR)\n\t$@$(RESET)"
	@echo "---- Type: % ./so_long ./maps/a.ber"

$(LIBFT):
	@$(MAKE) -C ./libft --no-print-directory

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C ./libft clean --no-print-directory
	@echo "remove:\t$(RED)$(OBJ_DIR)$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C ./libft fclean --no-print-directory
	@echo "\t$(RED)"libft.a"$(RESET)"
	@echo "\t$(RED)$(NAME)$(RESET)"

re: fclean all

#Identify the keys pressed
press_key: $(OBJ_DIR) $(OBJ)
	@$(CC) $(CFLAGS) $(KEY).c $(MLX_FLAGS) -o $(KEY)
	@echo "create:\t$(ORANGE)$@$(RESET)"
	@./$(KEY)

clean_press_key:
	@$(RM) $(KEY)
	@echo "remove:\t$(RED)$(KEY)$(RESET)"

#Compiles and runs the program
play: all
	@./$(NAME) ./maps/a.ber

git:
		git add .
		git commit -m "done"
		git push

.PHONY: all clean fclean re
