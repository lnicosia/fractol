# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/06 15:56:21 by lnicosia          #+#    #+#              #
#    Updated: 2023/02/15 18:53:12 by lumenthi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

MAKEFILE = Makefile

SRC_DIR = src
OBJ_DIR = obj
INCLUDES_DIR = includes
BIN_DIR = .

LIBFT_DIR = libft
LIBMFT_DIR = libmft
LIBFT = $(LIBFT_DIR)/libft.a
LIBMFT = $(LIBMFT_DIR)/libmft.a
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

SRC_RAW = main.c key_press.c close_window.c julia.c mandelbrot.c init.c ship.c \
		  export.c buddhabrot.c color.c burning_julia.c newton.c \
		  buddha2.c color_newton.c barnsley.c koch.c \
		  plot_line.c coord_utils.c print_color_data.c \
		  tricorn.c plot_line_aa.c math.c householder.c \
		  householder_fail.c householder_fail2.c swap_color_base.c \
		  swap_color_mode.c colorize_buddha.c color_outside.c \
		  put_fractal_to_window.c newton_utils.c print_outside_data.c \
		  key_release.c mouse.c

HEADERS = fractol.h mlx_keycode.h hook.h color_newton.h colorize_buddha.h \
		  print_color_data.h

SRC = $(addprefix $(SRC_DIR)/, $(SRC_RAW))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_RAW:.c=.o))
INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(HEADERS))

CFLAGS =  -Wall -Wextra -Werror -I $(INCLUDES_DIR) \
		  -I $(LIBFT_DIR)/$(INCLUDES_DIR) \
		  -I $(LIBMFT_DIR)/$(INCLUDES_DIR) \
		  -I $(MLX_DIR) \
		  -flto -Ofast \
		  #-g3 -fsanitize=address

DEBUG ?= 0

#ifeq ($(DEBUG), 1)
#	CFLAGS += -fsanitize=address
#endif

#MLX = -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit
MLX_FLAGS = -lX11 -lXext -lm -lpthread

#
# Color declarations
#

RED := "\e[0;31m"
GREEN := "\e[0;32m"
YELLOW := "\e[0;33m"
BLUE := "\e[0;34m"
MAGENTA := "\e[0;35m"
CYAN := "\e[0;36m"
RESET :="\e[0m"

all: 
	@make -C $(LIBFT_DIR)
	@make -C $(LIBMFT_DIR)
	@make $(BIN_DIR)/$(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES) $(MLX_INIT) $(LIBFT_INIT)
	@printf $(YELLOW)"Compiling $<\n"$(RESET)
	gcc -c $< -o $@ $(CFLAGS) 

$(BIN_DIR)/$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT) $(LIBMFT) $(MLX)
	@printf ${CYAN}"[INFO] Linking $(BIN_DIR)/$(NAME)...\n"${RESET}
	gcc $(CFLAGS) $(OBJ) $(LIBFT) $(LIBMFT) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@printf ${GREEN}"[INFO] Compiled $(BIN_DIR)/$(NAME) with success!\n"${RESET}

$(MLX_INIT):
	git submodule update --init

$(LIBFT_INIT):
	git submodule update --init

$(MLX): $(MLX_DIR)/mlx.h
	@make -C $(MLX_DIR)

clean: 
	@make clean -C libft
	@rm -f $(OBJ)
	@rm -Rf $(OBJ_DIR)
	@printf ${CYAN}"[INFO] Removed objs"${RESET}

fclean:
	@make fclean -C libft
	@rm -f $(OBJ)
	@rm -Rf $(OBJ_DIR)
	@printf ${CYAN}"[INFO] Removed objs\n"${RESET}
	@rm -Rf $(NAME)
	@printf ${CYAN}"[INFO] Removed $(BIN_DIR)/$(NAME)\n"${RESET}

re: fclean all

.PHONY: fclean all clean libft
