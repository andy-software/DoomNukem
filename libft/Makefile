#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/26 14:21:15 by apavlov           #+#    #+#              #
#    Updated: 2018/11/07 19:46:43 by apavlov          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc

NAME = libft.a

FLAGS = -O3 -Wall -Wextra -Werror

OBJ_DIR = ./obj/

SRC_DIR = ./

INC = libft.h

SRC = 	ft_atoi.c \
		ft_bzero.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c\
		ft_isodd.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_lstadd.c \
		ft_lstdel.c \
		ft_lstdelone.c\
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_max.c \
		ft_memdel.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memcpy.c \
		ft_memcmp.c \
		ft_memchr.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putchar.c \
		ft_putendl_fd.c \
		ft_putendl.c \
		ft_putnbr_fd.c \
		ft_putnbr.c \
		ft_putstr_fd.c\
		ft_putstr.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_strequ.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strnequ.c \
		ft_strnew.c \
		ft_strstr.c \
		ft_strchr.c \
		ft_strsplit.c \
		ft_strnstr.c \
		ft_strsub.c \
		ft_strtrim.c \
		ft_tolower.c\
		ft_toupper.c \
		get_next_line.c \
		ft_abs.c \
		ft_strrchr.c \
		ft_swap.c \
		percent.c \
		line_point.c \
		count_number.c \
		comp_real.c \
		ft_float_abs.c \

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: obj_dir $(NAME)

obj_dir:
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(INC)
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
