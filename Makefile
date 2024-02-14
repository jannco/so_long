# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile1                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 20:11:52 by yadereve          #+#    #+#              #
#    Updated: 2024/02/14 16:45:20 by yadereve         ###   ########.fr        #
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

MLX_DIR = minilibx/minilibx_opengl_20191021
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_INC = -I$(MLX_DIR) -I$(MLX_DIR)/libmlx
MLX_FLAGS = -L$(MLX_DIR) -Lmlx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C ./libft --no-print-directory

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C ./libft clean --no-print-directory

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
