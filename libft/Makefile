# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/04 11:57:59 by lnicosia          #+#    #+#              #
#    Updated: 2019/01/03 12:19:27 by lnicosia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_memccpy.c ft_memcpy.c ft_memset.c ft_bzero.c ft_memmove.c \
	   ft_isalpha.c ft_isalnum.c ft_isdigit.c ft_isascii.c ft_isprint.c \
	   ft_putchar_fd.c ft_putchar.c ft_putstr.c ft_putstr_fd.c ft_strlen.c \
	   ft_memchr.c ft_memcmp.c ft_strdup.c ft_strcpy.c ft_strncpy.c \
	   ft_strcat.c ft_strncat.c ft_strlcat.c ft_strrchr.c ft_strchr.c \
	   ft_strstr.c ft_strnstr.c ft_atoi.c ft_strcmp.c ft_strncmp.c \
	   ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c ft_strnew.c \
	   ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c \
	   ft_strmapi.c ft_strnequ.c ft_strequ.c ft_strsub.c ft_strjoin.c \
	   ft_strtrim.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c \
	   ft_strsplit.c ft_itoa.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c \
	   ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_lstlen.c ft_lstpushback.c \
	   ft_abs.c get_next_line.c ft_strjoin_free.c ft_min.c ft_max.c \
	   ft_fmin.c ft_fmax.c ft_count.c ft_fabs.c ft_atoi_base.c

INCLUDES = ../includes

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra -I $(INCLUDES)

RED := "\033[0;31m"
GREEN := "\033[0;32m"
BLUE := "\033[0;34m"
YELLOW := "\033[0;33m"
CYAN := "\033[0;36m"
RESET := "\033[0m"

all: $(NAME)

$(NAME) : $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo ${YELLOW}"[INFO] Created libft.a successfully!"${RESET}

clean :
	@/bin/rm -f $(OBJ)
	@echo ${CYAN}"[INFO] Removed .o from the libft"${RESET}

fclean : clean
	@/bin/rm -f $(NAME)
	@echo ${CYAN}"[INFO] Removed .o and libft.a from the libft"${RESET}

compil : all clean

re : fclean all

.SILENT: $(OBJ)
.PHONY: fclean all re clean
