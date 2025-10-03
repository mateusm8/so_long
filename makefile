# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/17 20:09:45 by matmagal          #+#    #+#              #
#    Updated: 2025/10/03 01:09:26 by matmagal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -I$(PRINTF_DIR) -I$(MLX_DIR)
SRC_DIR = src
OBJ_DIR = obj
PRINTF_DIR = ext/ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a
MLX_DIR = ext/minilibx

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	MLX = $(MLX_DIR)/libmlx.a
	MLX_LIB = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
else ifeq ($(UNAME_S),Darwin)
	MLX = $(MLX_DIR)/libmlx.dylib
	MLX_LIB = -framework Metal -framework MetalKit -framework AppKit
endif

SRCS = 	$(SRC_DIR)/so_long.c \
		$(SRC_DIR)/get_next_line.c \
		$(SRC_DIR)/get_next_line_utils.c \
		$(SRC_DIR)/parsing.c \
		$(SRC_DIR)/ft_free.c \
		$(SRC_DIR)/utility_functions.c \
		$(SRC_DIR)/utility_functions_2.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(PRINTF) -o $(NAME)

$(PRINTF):
	@$(MAKE) -C $(PRINTF_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(PRINTF_DIR) clean
ifeq ($(UNAME_S),Linux)
	@$(MAKE) -C $(MLX_DIR) clean
endif

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(PRINTF_DIR) fclean
ifeq ($(UNAME_S),Linux)
	@$(MAKE) -C $(MLX_DIR) clean
endif

re: fclean all

.PHONY: all clean fclean re
