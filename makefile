# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/17 20:09:45 by matmagal          #+#    #+#              #
#    Updated: 2025/09/17 22:05:28 by matmagal         ###   ########.fr        #
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
MLX_DIR = ext/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_LIB	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRCS = 	$(SRC_DIR)/so_long.c \

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(PRINTF) -o $(NAME)
	
$(PRINTF):
	@$(MAKE) -s -C $(PRINTF_DIR)

$(MLX):
	@$(MAKE) -s -C $(MLX_DIR)

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
	@$(MAKE) -s -C $(MLX_DIR) fclean

re: fclean all

.PHONY: all clean fclean re