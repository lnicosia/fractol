# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/06 15:56:21 by lnicosia          #+#    #+#              #
#    Updated: 2019/02/27 16:40:27 by lnicosia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

MAKEFILE = Makefile

SRC_DIR = src
OBJ_DIR = obj
INCLUDES_DIR = includes
BIN_DIR = .

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_RAW = main.c hook.c close_window.c julia.c mandelbrot.c init.c

HEADERS = fractol.h mlx_keycode.h hook.h

SRC = $(addprefix $(SRC_DIR)/, $(SRC_RAW))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_RAW:.c=.o))
INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(HEADERS))

CFLAGS =  -g3 -O3 -Wall -Wextra -Werror -I $(INCLUDES_DIR) \
		 -I $(LIBFT_DIR) -fsanitize=address

MLX = -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit

RED := "\033[0;31m"
GREEN := "\033[0;32m"
CYAN := "\033[0;36m"
RESET :="\033[0m"

all:
	@make -C $(LIBFT_DIR)
	@make $(BIN_DIR)/$(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES) $(MAKEFILE)
	@mkdir -p $(OBJ_DIR)
	@gcc -c $< -o $@ $(CFLAGS) 

$(BIN_DIR)/$(NAME): $(OBJ) $(LIBFT)
	@gcc $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)
	@echo ${GREEN}"[INFO] Compiled '$(NAME)' executable with success!"${RESET}

clean: 
	@rm -f $(OBJ)
	@rm -Rf $(OBJ_DIR)
	@make clean -C libft
	@echo ${CYAN}"[INFO] Removed [$(OBJ)] with success!"${RESET}
	@echo ${CYAN}"[INFO] Removed [$(OBJ_DIR)] with success!"${RESET}

fclean: clean
	@rm -Rf fractol
	@echo ${CYAN}"[INFO] Removed everything because SKIBIDI PA PA"${RESET}

re: fclean all

.PHONY: fclean all clean libft
