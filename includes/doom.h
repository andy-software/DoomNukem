/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 16:26:42 by apavlov           #+#    #+#             */
/*   Updated: 2019/03/09 16:26:43 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <fcntl.h>
# include "../libft/libft.h"
# include <math.h>
# include <pthread.h>
# include "../frameworks/SDL2.framework/Headers/SDL.h"
# include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
# include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "../frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
# include <errno.h>
# include <stdio.h>
//add network

# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define SKY_W 4096
# define SKY_H 2048
# define WALL_TEXT_W 256	
# define WALL_TEXT_H 512
# define SPEED_ROTATION 0.03f
# define SPEED_ROTATION_Z 0.05f
# define MAX_Z_ANGLE 5
# define MOVE_SPEED 0.2f
# define SIT_EYE_HEIGHT 3
# define EYE_HEIGHT 6
# define HEAD_HEIGHT 1
# define KNEE_HEIGHT 2
# define BIG_VALUE 9e9
# define MAX_SECTORS_RENDERED 32  //must be the power of 2
# define COUNT_FPS_NUMBERS 4
# define MAX_SPEED_UPWARD 1
# define NUM_OF_THRD 4
# define MIN_SLICE_WIDTH 40
# define MAX_THREADS_IN_RENDER	4
# define MAX_THREADS_IN_SKY	4
# define GREATER 46 // keycode of >
# define LESER 44 // <
# define PAUSE 96 // §
# define COUNT_OF_MOVES 2

# define MAX_SPRITES_COUNT	128

# define HFOV (WIN_WIDTH / 2 * 1.455) //tg 55.5 make fov =~ 69 grad
# define VFOV (0.2 * WIN_HEIGHT)
# define STRAIGHT 1
# define STRAFE 2
# define min(a,b)				(((a) < (b)) ? (a) : (b))
# define max(a,b)				(((a) > (b)) ? (a) : (b))
# define clamp(a, mi,ma)		min(max(a,mi),ma) //put a between min and max
# define vxs(x0,y0, x1,y1)		((x0)*(y1) - (x1)*(y0)) //cross vector product
# define dvp(x0,y0, x1,y1)		((x0)*(x1) + (y0)*(y1)) //dot vector product
# define Overlap(a0,a1,b0,b1)	\
	(min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))

# define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3) \
	(Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3))

# define PointSide(px,py, x0,y0, x1,y1) \
	(vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0)))

//CROSS_THE_LINE
#define CTL(x0, y0, x1, y1, x2, y2, x3, y3) \
	(IntersectBox(x0, y0, x1, y1, x2, y2, x3, y3) && \
		PointSide(x1, y1, x2, y2, x3, y3) < 0)

# define Fix(a)  				((a) * (1LL<<8))
# define UnFix(a) 				((a) / (float)(1LL<<8))
# define FixMult(a, b) 			((((a) * (b)) >> 8))
# define FixDiv(a, b) 			((((a) << 8) / (b)))

/* EDITOR */
# define NB_BUTTONS 16
# define NB_IMAGES 8
# define EXIST doom->editor.images[doom->editor.ind_img].exist
# define NUM_WALL 7 // 3
# define ESC (key == SDLK_ESCAPE)
# define FLOOR 1
# define CEIL 2
# define p(x) printf(x)
# define MAX_NUM_SECTORS 20

/*  BREZEN NORM */
# define BDX doom->editor.brezen.dx
# define BDY doom->editor.brezen.dy
# define BSTARTX doom->editor.brezen.startx
# define BSTARTY doom->editor.brezen.starty

/*  TEXT COLOR  */
# define TNULL "\x1B[0m"
# define TRED  "\x1B[31m"
# define TGRE  "\x1B[32m"
# define TYEL  "\x1B[33m"
# define TBLU  "\x1B[34m"
# define TPIN  "\x1B[35m"
# define TCYN  "\x1B[36m"
# define TWHY  "\x1B[37m"
/***/

typedef struct s_doom		t_doom;

typedef struct s_sdl		t_sdl;
typedef struct s_option		t_option;

typedef struct s_map		t_map;
typedef struct s_vertex		t_vertex;
typedef struct s_sector		t_sector;
typedef struct s_player		t_player;
typedef struct s_line		t_line;
typedef struct s_game		t_game;
typedef struct s_vector		t_vector;
typedef struct s_render		t_render;
typedef struct	s_ceil_cal	t_ceil_cal;
typedef struct	s_floor_cal	t_floor_cal;
typedef struct s_plane		t_plane;
typedef struct s_ui			t_ui;
typedef struct	s_rend_sector	t_rend_sector;

typedef struct s_texture	t_texture;
typedef struct s_skybox		t_skybox;
typedef struct s_sprite		t_sprite;
typedef struct	s_sprite_render	t_sprite_render;
typedef struct	s_sprite_list	t_sprite_list;
typedef	struct	s_painting		t_painting;
typedef	struct	s_font			t_font;
typedef	struct	s_sound			t_sound;

/* EDITOR */
typedef struct s_editor	t_editor;
typedef struct s_brezen	t_brezen;
typedef struct s_interface	t_interface;
typedef struct s_vertex_int	t_vertex_int;
typedef struct s_images t_images;
typedef	struct s_buttons t_buttons;
typedef struct s_title	t_title;
typedef	struct s_fline 	t_fline;
typedef	struct s_thread	t_thread;


/***/

struct	s_plane
{
	float			a;
	float			b;
	float			c;
	float			h;
};

struct	s_vector
{
	float			x;
	float			y;
	float			z;
};

struct	s_vertex
{
	float			x;
	float			y;
};

struct	s_player
{
	t_vector		coord; //earlier was t_vertex could cause some troubles
	Uint32			sector;
	float			angle;
	float			anglesin;
	float			anglecos;
	float			angle_z; // angle of player z view
};

struct	s_line
{
	int 			wall;
	int				bot;
	int				top;

	float			x_w_scale;
	int				x_w_shift;
	float			y_w_scale;
	int				y_w_shift;

	float			x_b_scale;
	int				x_b_shift;
	float			y_b_scale;
	int				y_b_shift;

	float			x_t_scale;
	int				x_t_shift;
	float			y_t_scale;
	int				y_t_shift;
};

struct	s_sector
{	
	Uint32			num;
	Uint32			num_vert;
	t_line			*lines; //same numeration as vert
	t_vertex		*vert;
	char			*neighbors;

	int				render_ceil; //bool value that means if ceil should be rendered
	t_plane			ceil_plane;
	int				ceil_tex;
	float			x_c_scale;
	int				x_c_shift;
	float			y_c_scale;
	int				y_c_shift;

	t_plane			floor_plane;
	int				floor_tex;
	float			x_f_scale;
	int				x_f_shift;
	float			y_f_scale;
	int				y_f_shift;

	int				volume_lvl;
	int				sound_num;

	int				light_lvl;
};

struct	s_sprite
{
	int		spr_num;
	int		text_no;
	t_vector	coord;
	float	width;
	float	end_z; //end_z - start_z its height of sprite
	float	start_z; //if sprite is flying unit then its non equil to 0
	int		sector_no;
	int		mob;
	int		draw;
	int		live; //only if mob affected
	float	anglesin;
	float	anglecos;
	float	angle;

	float	speed_x;
	float	speed_y;
	float	move_speed;

	int		own_moves;
	float	vision_forward;
	float	vision_backward;
};

struct	s_painting
{
	int		text_no;
	t_vector	v1;
	t_vector	v2;
	int		w;
	int		h;
	int		sector_no;
};

struct	s_sprite_list
{
	SDL_Surface	**sprites;
	int			c_sprt;
	int			w;
	int			h;
	struct	s_sprite_list	*next;
};

struct	s_sprite_render
{
	t_sector		*curr_sect;
	t_rend_sector	*begin;
	t_rend_sector	*tmp;
	t_sprite		*sprites; //to sort by y-distance //all sprites thats need to be rendered
	int				c_paint;
	t_painting		*paint;
	t_map			*map;
	t_vector		t1;
	t_vector		t2;
	t_vector		v1;
	t_vector		v2;
	float			xscale1_p;
	float			xscale2_p;
	float			x1_p;
	float			x2_p;
	float			percent;
	float			d_percent;
	float			percent_of_wall;
	float			d_percent_of_wall;
	SDL_Surface		*surr;

	float			d_y;
	float			x_text;
	float			d_x_text;
	int				y_text;
	Uint32			color;

	int				clmp_top;
	int				clmp_bot;

	int				t1_1_line;
	int				t1_2_line;
	int				t2_1_line;
	int				t2_2_line;

	int				pos;
	Uint32			time_from_loop_start;
	Uint32			prev_frame;

	t_vertex		i1;
	t_vertex		i2;

	int				i;
	t_rend_sector	*now;
	int				c_sprt;
	float			begin_x;
	float			end_x;
	float			y;
	float			za;
	float			zb;
	float			d_za;
	float			d_zb;
	int				nza;
	int				nzb;
	float			x1;
	float			x2;
	float			z1;
	float			z2;
	int				z1a;
	int				z1b;
	int				z2a;
	int				z2b;
	int				c_za;
	int				c_zb;
	float			win_x;
	float			zscale1;
	float			zscale2;
	float			xscale1;
	float			xscale2;

	int				win_y;
};

struct	s_map
{
	Uint32			num_vert;
	t_vertex		*vertex; //delete this doesnt useful
	Uint32			num_sect;
	t_sector		*sectors;
	Uint32			num_sprites;
	t_sprite		sprites[MAX_SPRITES_COUNT]; //it will be a little bigger then real count of sprites to add things like grenade or projectiles
												// but still static
	Uint32			num_paint;
	t_painting		*paint; //always same count
	int				fog;
	Uint32			fog_color;
};

struct	s_sdl
{
	SDL_Window		*window;
	SDL_Surface		*surface;
	SDL_Renderer	*render;
	SDL_Texture		*texture;
};

struct	s_game
{
	float			dx;
	float			dy;
	int				fire;
	t_vector		velocity;
	float			acceleration;
	int				ground;
	int				falling;
	int				moving;
	int				ducking;
	int				flying; //new feature
	int				quit;
	int				pause;
	int				hp_level;
	int				damage;
	SDL_Event		event;
	float			eye_height;
	Uint32			dt;
};

struct	s_option
{
	int				difficult;
	int				music_volume_level;
	int				effects_volume_level;
};

struct	s_rend_sector
{
	Uint32			num;
	int				sx1;
	int				sx2;
	int				ztop1;
	int				ztop2;
	int				zbot1;
	int				zbot2;
};

struct	s_ceil_cal
{
	Uint32	color;
	float	map_x;
	float	map_y;
	float	denomi;
	float	x_multi;
	float	deriv_map_x;
	float	deriv_map_y;
	int		scaled_map_x;
	int		scaled_map_y;
	int		x_text;
	int		y_text;
	int		screen_y;
	float	dummy;
	float	doomy;
	t_sector	*sect;
	t_plane	rotated;
	t_vector	random_vector;
	SDL_Surface	*surr;
};

struct	s_floor_cal
{
	Uint32	color;
	float	map_x;
	float	map_y;
	float	denomi;
	int		x_text;
	int		y_text;
	int		screen_y;
	float	dummy;
	float	doomy;
	float	x_multi;
	t_sector	*sect;
	t_plane	rotated;
	t_vector	random_vector;
	SDL_Surface	*surr;
};

struct	s_render
{
	float			width_slice;
	int				count_slice;

	t_ceil_cal		ceil_cal;
	t_floor_cal		floor_cal;
	t_rend_sector	now;
	t_rend_sector	*queue;
	t_rend_sector	*tail;
	t_rend_sector	*head;
	int				*rendered_sectors;
	int				*ztop;
	int				*zbottom;
	t_sector		*sect;
	t_vertex		t1;
	t_vertex		t2;
	t_vertex		v1;
	t_vertex		v2;
	float			w0;
	float			w1;
	float			w0_bot;
	float			w1_bot;
	float			w0_top;
	float			w1_top;

	float			len;
	float			d_alpha;
	float			angle_z;
	float			dummy_var;
	float			d_dummy_var_x;
	float			d_doomy_var_x;
	float			another_percent;
	Uint32			color;
	t_vertex		mc1;
	t_vertex		mc2;
	t_vertex		current;
	t_vertex		i1;
	t_vertex		i2;
	float			kt;
	float			kza;
	float			kzb;
	float			nkza;
	float			nkzb;	
	int				t1_1_line;
	int				t1_2_line;
	int				t2_1_line;
	int				t2_2_line;
	int				max_sector_rendered;
	float			pcos;
	float			psin;
	float			begin_x;
	float			end_x;
	float			x1;
	float			x2;
	int				z1;
	int				z2;
	float			xscale1;
	float			xscale2;
	float			zscale1;
	float			zscale2;
	float			zceil1;
	float			zfloor1;
	float			nzceil1;
	float			nzfloor1;
	float			zceil2;
	float			zfloor2;
	float			nzceil2;
	float			nzfloor2;
	int				z1a;
	int				z1b;
	int				z2a;
	int				z2b;
	int				nz1a;
	int				nz1b;
	int				nz2a;
	int				nz2b;
	//new things
	float			p_x;
	float			p_y;
	float			p_z;
	Uint32			*pix;
	t_line			line;
	t_plane			cplane;
	t_plane			fplane;
	t_plane			ncplane;
	t_plane			nfplane;
	char			neighbor;
	t_texture		*texture;
	t_map			*map;
};

struct	s_ui
{
	SDL_Rect		*minimap_rect;
	SDL_Surface		*minimap_surf;
	SDL_Surface		*message;
	Uint32			prevTime;
	Uint32			currTime;
	Uint32			start;
	char			masage[8];
	char			*text0;
	float			fps;
	int				fire;
	int				gun_num;
	int				start_saw;
	int				idle;
	int				ammo_1;	
};

struct	s_menu
{
};

struct	s_font
{
	SDL_Rect		text_rect;
	SDL_Color		text_color;
	TTF_Font		*text_font;
};

enum font {

	FPS_FONT = 0,
	HP_FONT = 1,
	AMMO_FONT = 2,
};

struct s_texture
{
	t_font			*fonts;
	t_sprite_list	*sprites;
	SDL_Surface		**wall_tex;
	SDL_Surface		**sky_box;
	SDL_Surface		*pause;
	SDL_Surface		*visor;
	SDL_Surface		**hp;
	SDL_Surface		**gun1;
	SDL_Surface		**gun2;
	SDL_Surface		**dude;
	SDL_Rect		dude_r;
	SDL_Rect		gun1_r;
	SDL_Rect		gun21_r;
	SDL_Rect		gun22_r;
	SDL_Rect		cross_r;
	SDL_Rect		hp_r;
	SDL_Rect		armor_r;
	SDL_Rect		ammo_r;
	int				dude_l;
	int				visor_l;
	int				gun1_l;
	int				gun2_l;
	int				armor_l;
	int				len;
	int				c_sprt;
};

struct s_skybox
{
	t_doom			*doom;
	int				win_x;
	int				end_x;
	int				text_x;
	int				win_y;
	int				start_text_y;
	int				text_y;
	float			pos_angle;
	int				pos_max;
	Uint32			*pix;
};

/* EDITOR */
struct s_vertex_int
{
	int x;
	int y;
};

struct	s_interface
{
	int tmp_x1;
	int tmp_y1;
	int tmp_x2;
	int tmp_y2;
	t_vertex_int	arr_vertex_map_coor[9999];
	t_vertex 		arr_vertex_real_coor[9999];
	t_sector		sectors[2000];
	int nbr_vertex;
	int nbr_sectors;
	int iterator_num_vertex;
	int is_drawing_interface;
	int start_new_sector;
};


struct	s_images
{
	SDL_Surface		*image;
	double			*im_x;
	double			*im_y;
	int				exist;
};

struct	s_buttons
{
	int				sec_draw;
	int				add_buttons;
	int				chng_text;
	int				ind_action;
};

struct s_brezen
{
	int		x1;
	int		x2;
	int		y1;
	int		y2;
	double d;
	double starty;
	double startx;
	double d1;
	double d2;
	double iterator;
	int dy;
	int dx;
	int color;
};

struct s_fline // for line
{
	int		num_line1; // like a number of vertex
	int		num_line2; // like a number of vertex for second case  == -1
	int		sec1;
	int		sec2;  // if line only in in one sector == -1 
};

struct	s_editor
{
	t_brezen		brezen;
	t_interface		interface;
	// t_sector 	saver[9999999];
	t_images		images[9999]; // consist of different images for editor
	t_images		sector[9999];
	t_font			font;
	int				ind_img; // number of image
	int				img_press; // press on image
	int 			is_drawing;
	int				zoom;
	int				but1_press;
	int				is_sector;
	int				ind_text; // started from 5 
	t_buttons		press;
	int				save_del;
	int				fl_or_ceil;
	int				is_portal; // 0 no; 1 yes
	t_fline			fline;
};
/****/
struct	s_sound
{
	Mix_Music		*music[3];
	Mix_Chunk		*steps;
	Mix_Chunk		*run;
	Mix_Chunk		*jump;
	Mix_Chunk		**gun1;
	Mix_Chunk		*win;
	Mix_Chunk		**gun2;
	Mix_Chunk		*fly;
	Mix_Chunk		*hurt;
	int				n;
};

struct	s_thread
{
	pthread_t	thrd;
	Uint32		id;
	int			finished;

	float		alpha;
	float		d_alpha; //hm
	float		end_x;
	float		begin_x;
	float		doomy_var_x;
	float		dummy_var_x;
	float		d_doomy_var_x; //hm
	float		d_dummy_var_x; //hm
	int			x_text;
	int			x_text_upper;
	int			x_text_lower;
	int			win_x;
	int			win_y;
	float		y;
	int			za;
	int			zb;
	int			c_za;
	int			c_zb;
	t_render	*r;
	int			nza;
	int			nzb;
	int			c_nza;
	int			c_nzb;
	t_floor_cal	fc;
	t_ceil_cal	cc;
	int			wall_end;
	float		d_betta;
	float		betta;
	float		float_y_text;
	float		d_y_text;
	Uint32		color;		
};

typedef struct s_changes	t_changes;
typedef int (*bots_move)(t_doom *, t_sprite *);



struct	s_changes
{
	bots_move	moves[COUNT_OF_MOVES];
};

struct	s_doom
{
	t_thread		threads[NUM_OF_THRD];
	t_sprite_render		sr;
	t_render		render;
	t_ui			ui;
	t_sdl			sdl;
	t_option		options;
	t_map			map;
	t_game			game;
	t_player		player;
	t_texture		texture;
	t_skybox		sky[4];
	t_editor		editor;
	t_sound			sound;
	t_changes		changes;
};

//friendly user stuff
int			print_usage(void);
int			error_message(char *message);

//UI
int			prepare_to_draw_ui(t_doom *doom);
void		draw_fps(t_doom *d, int fps);


//parser & initial
int			read_file(t_doom *doom, char *file_name);
int			init_sdl(t_sdl *sdl, t_option *options);


//game loop
void		player_events(t_doom *d);
void		game_events(t_doom *d);
int			game_loop(t_doom doom);
int			*intset(int *b, int c, size_t len);


//render
int			draw_screen(t_doom *d);
int			user_interface(t_doom *doom);
int			draw_minimap(t_doom *d);
void		render_floor_line(int start, int end, t_render *r, t_thread *t);
void		render_ceil_line(int start, int end, t_render *r, t_thread *t);
void		reversed_textline_draw(int y1, int y2, t_render *r, t_thread *t);
void		textline_draw(int y1, int y2, t_render *r, t_thread *t);
void		upper_textline(int y1, int y2, t_render *r, t_thread *t);
void		lower_textline(int y1, int y2, t_render *r, t_thread *t);
Uint32			get_fog_color(Uint32 color, Uint32 fog_color, float y);
//threads
int			find_count_and_width_of_slice(t_render *r);
int			fill_the_params(t_render *r, t_thread *t);
void		*start_the_work(void *data);

//some math stuff
float		get_z(t_plane plane, float x, float y);
int			sign(float x);
int			rotate_vector_xy(t_vector *a, float psin, float pcos);
int			get_normal_to_plane(t_vector *v, t_plane *p);
t_vertex	intersect(t_vertex d1, t_vertex d2, t_vertex d3, t_vertex d4);
int			project_vector2d(float *ax, float *ay, float bx, float by);
int			rotate_vertex_xy(t_vertex *a, float psin, float pcos);
t_plane		rotate_plane_xy(t_plane *plane, float psin, float pcos);
float		fpercent(float start, float end, float current);
float		v2dlenght(float vx, float vy);
t_vertex	find_x_from_screen_coords(float xw, t_vertex start, t_vertex end, t_render *r);
t_vertex	get_line_param(float x1, float y1, float x2, float y2);
int			reverse_bits(int b);
float		line_len(t_vertex start, t_vertex end);
Uint32		get_color_value(Uint32 start, Uint32 end, float perc);
int			line_point_int(int start, int end, int p);
Uint32		get_color_value_int(Uint32 start, Uint32 end, int perc);
float		find_angle_2pi(float sin, float cos);
/*
**interface.c
*/
void			draw_ui(t_doom *d);
void			gun_anim(t_doom *d);
/*
**texturelaod.c
*/
void		prepare_to_rendering(t_render *r, t_doom d);
/*
**skybox.c
*/
void			draw_skybox(t_doom d);
int				prepare_to_sky(t_doom *d);
void			*sky_threads(void *data);
SDL_Surface		*load_tex(char *path, t_sdl *sdl);
int				load_all(t_texture *t, t_sdl *sdl, t_doom *d);
int				load_ui(t_texture *texture, t_sdl *sdl, t_doom *d);
void			resize_surf(int w, int h, SDL_Surface** surf, t_doom *d);
Uint32			pix_from_text(SDL_Surface *texture, int x, int y);
/*
**sprites.c && load.c
*/
int				translate_and_rotate_sprites(t_sprite	*arr_spr, int len, t_player	p);
int				sprite_sort(t_sprite *arr_spr, int len);
void			load_sprites(t_texture *texture, t_sdl *sdl);
t_sprite_list	*split_image_to_sprites(SDL_Surface *surr, int w, int h);
int				*copy_static_arr(int *arr, const int len);
int				game_mod(char *file_name);
void			move_mobs(t_doom *d);
int				first_own_moves(t_doom *d, t_sprite *spr);
int				mirror_own_moves(t_doom *d, t_sprite *spr);
int				init_moves(t_doom *d);
/*
**sounds.c  
*/
Mix_Chunk		*load_sound(char *path);
Mix_Music		*load_music(char *path);
void			move_sound(t_sound *sound);
void			load_sounds(t_sound *sound);
void			play_music(t_sound *sound, int n);
void			switch_music(t_sound *sound, SDL_Event ev);

/* EDITOR */
void		change_text(t_doom *doom, SDL_Event *event);
int			ft_map_editor(t_doom *doom, char *name);
int			ft_create_window(t_doom *doom, char *name);
int			ft_read_map_edit(t_doom *doom, int fd);
int			ft_start_edit(t_doom *doom, int fd, char *name); // refresh
int			ft_write_changes_to_file(t_doom *doom, int fd);
int			write_changes_to_file(t_map map, int fd, t_player mplayer);
void		ft_check_key(t_doom *doom, SDL_Event *event);
void		ft_render_editor(t_doom *doom);
void		ft_render_interface(t_doom *doom);
void		ft_draw_pixel(t_doom *doom, int x, int y, int color);
void		ft_render_other(t_doom *doom);
void		ft_mouse_move_edit(t_doom *doom, SDL_Event *event);
void		ft_mouse_release_edit(t_doom *doom, SDL_Event *event);
void		ft_render_previous(t_doom *doom);
void		ft_draw_axis(t_doom *doom);
void		ft_prepare_editor(t_doom *doom);
int			ft_prepare_to_write(t_doom *doom);
int			ft_specify_coor(int nbr);
void		ft_refresh_photo(t_doom *doom, SDL_Event *event);
void		key_floor_ceil(t_doom *doom, SDL_Event *event);
void		info_ceil_floor(t_doom *doom);
// brezen in editor
void		ft_line(t_doom *doom);void	ft_mouse_press_edit(t_doom *doom, SDL_Event *event);
/***/

#endif
