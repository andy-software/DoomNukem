# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/09 11:40:21 by apavlov           #+#    #+#              #
#    Updated: 2019/08/19 19:32:27 by myuliia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS =  -Wall -O3 -Wextra -Ofast -flto -pipe #-fsanitize=address  #-Werror

NAME = doom-nukem

SRC =	main.c output.c init.c parser.c game_events.c player_events.c\
		game.c math.c main_render.c plane_functions.c textureload.c skybox.c\
		sprites.c sorting.c editor.c editor2.c brezen.c threads.c sound.c\
		interface.c changes.c menus.c keys.c painting.c sprite_render.c\
		sprite_events.c paint_events.c game_mod_for_map_editor.c \
		map_editor_first_person_view.c editor_check.c editor_floor_ceil.c \
		editor_prepare.c editor_write_read.c editor_render.c editor_key.c \
		editor_key_texture.c editor_ft.c editor_mouse.c editor_sprites_change.c \
		editor_change_scale.c editor_info_in_term.c editor_interface.c \
		editor_player_events.c editor_init_window.c editor_point_lie.c \
		editor_save_del.c editor_add_items.c free_game.c editor_write_sprites.c \
		editor_write_sprites2.c editor_write_sprites3.c

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

clean_map:
	rm -rf map

map: clean_map
	$(CC) $(FLAGS) $(INCLUDES) $(FRAMEWORKS) src/TEST_MUST_BE_ONE.c src/plane_functions.c src/math.c src/changes.c $(LINKS) -o map

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
