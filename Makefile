#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/09 11:40:21 by apavlov           #+#    #+#              #
#    Updated: 2019/01/09 11:40:22 by apavlov          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc

FLAGS =  -Wall -g -O3 #-fsanitize=address #-Wextra -Werror

NAME = doom-nukem

SRC = main.c output.c init.c parser.c game_events.c player_events.c game.c math.c main_render.c plane_functions.c textureload.c skybox.c

INC = includes/doom.h

SRC_DIR = ./src/

OBJ_DIR = ./obj/

INC_DIR = ./includes/

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

FT = ./libft/

FT_LIB	= $(addprefix $(FT),libft.a)

LINKS = -L$(FT) -l ft

SDL_PATH = ./framework

INCLUDES = 		-I$(FT) -I$(INC_DIR) \
				-I./frameworks/SDL2.framework/Headers \
				-I./frameworks/SDL2_image.framework/Headers \
				-I./frameworks/SDL2_ttf.framework/Headers \
				-I./frameworks/SDL2_mixer.framework/Headers \
				-F./frameworks

FRAMEWORKS = 	-F./frameworks \
				-rpath ./frameworks \
				-framework AppKit -framework OpenGL \
				-framework SDL2 -framework SDL2_image \
				-framework SDL2_mixer -framework SDL2_ttf \

all: obj_dir $(FT_LIB) $(NAME)
	echo 'Compilated!'

obj_dir:
	mkdir -p $(OBJ_DIR)

clean_map_1:
	rm -rf map

map_1: clean_map_1
	$(CC) $(FLAGS) $(INCLUDES) $(FRAMEWORKS) src/first_map_creator.c  $(LINKS) -o map

clean_map_2:
	rm -rf map

map_2: clean_map_2
	$(CC) $(FLAGS) $(INCLUDES) $(FRAMEWORKS) src/second_map_creator.c  $(LINKS) -o map


clean_map_3:
	rm -rf map

map_3: clean_map_3
	$(CC) $(FLAGS) $(INCLUDES) $(FRAMEWORKS) src/third_map.c  $(LINKS) -o map

clean_map_4:
	rm -rf map

map_4: clean_map_4
	$(CC) $(FLAGS) $(INCLUDES) $(FRAMEWORKS) src/test_neightbors_ceil.c  $(LINKS) -o map

clean_map_5:
	rm -rf map

map_5: clean_map_5
	$(CC) $(FLAGS) $(INCLUDES) $(FRAMEWORKS) src/neighbor_map.c  $(LINKS) -o map


clean_map_6:
	rm -rf map

map_6: clean_map_6
	$(CC) $(FLAGS) $(INCLUDES) $(FRAMEWORKS) src/test_neightbor_floor.c  $(LINKS) -o map

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(FRAMEWORKS) $(OBJ) $(LINKS) -o $(NAME)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(INC)
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(FT) clean

fclean: clean
	rm -f $(NAME)
	make -C $(FT) fclean

re: fclean all
