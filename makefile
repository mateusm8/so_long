# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/17 20:09:45 by matmagal          #+#    #+#              #
#    Updated: 2025/09/21 12:53:55 by matmagal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -I$(PRINTF_DIR) -I$(MLX_DIR) 
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
PRINTF_DIR = ext/ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a
MLX_DIR = ext/minilibx
MLX = $(MLX_DIR)/libmlx.a

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	MLX_DIR = ext/minilibx
	MLX = $(MLX_DIR)/libmlx.a
	MLX_LIB	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
else ifeq ($(UNAME_S),Darwin)
	MLX_DIR = ext/minilibx
	MLX = $(MLX_DIR)/libmlx.dylib
	MLX_LIB	= -L$(MLX_DIR) -lmlx -framework Metal -framework MetalKit -framework AppKit
endif

SRCS = 	$(SRC_DIR)/so_long.c \
		$(SRC_DIR)/get_next_line.c \
		$(SRC_DIR)/get_next_line_utils.c \

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(PRINTF) -o $(NAME)
	
$(PRINTF):
	@$(MAKE) -s -C $(PRINTF_DIR)

ifeq ($(UNAME_S),Linux)
$(MLX):
	@$(MAKE) -s -C $(MLX_DIR)
else ifeq ($(UNAME_S),Darwin)
$(MLX):
	@echo "MLX Metal já pronta, nada a compilar"
endif

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(RM) $(OBJS)
	@$(MAKE) -s -C $(PRINTF_DIR) clean
	@$(MAKE) -s -C $(MLX_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(PRINTF_DIR) fclean
	@$(MAKE) -s -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re
