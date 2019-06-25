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
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <SDL_mixer.h>
# include <errno.h>
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

# define MAX_SPRITES_COUNT	128

# define HFOV (WIN_WIDTH / 2)
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

# define Fix(a)  				((a) * (1LL<<8))
# define UnFix(a) 				((a) / (float)(1LL<<8))
# define FixMult(a, b) 			((int32_t)(((int64_t)(a) * (b)) >> 8))
# define FixDiv(a, b) 			((int32_t)(((int64_t)(a) << 8) / (b)))

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
typedef struct s_plane		t_plane;
typedef struct s_ui			t_ui;
typedef struct	s_rend_sector	t_rend_sector;

typedef struct s_texture	t_texture;
typedef struct s_skybox		t_skybox;
typedef struct s_sprite		t_sprite;
typedef struct	s_sprite_render	t_sprite_render;
typedef struct	s_sprite_list	t_sprite_list;
typedef	struct	s_painting		t_painting;

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
	int 			full;
	int				bot;
	int				top;
};

struct	s_sector
{	
	Uint32			num;
	Uint32			num_vert;
	t_line			*lines; //same numeration as vert
	t_vertex		*vert;
	char			*neighbors;
	Uint32			floor_z; //should be replaced with equation of surface
	Uint32			ceil_z; //should be replaced with equation of surface
	t_plane			ceil_plane;
	t_plane			floor_plane;
};

struct	s_sprite
{
	int		text_no;
	t_vector	coord;
	int		w;
	int		h;
	int		sector_no;
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

	int				clmp_top;
	int				clmp_bot;

	int				t1_1_line;
	int				t1_2_line;
	int				t2_1_line;
	int				t2_2_line;

	t_vertex		i1;
	t_vertex		i2;

	int				i;
	t_rend_sector	*now;
	int				c_sprt;
	int				begin_x;
	int				end_x;
	float			y;
	int				za;
	int				zb;
	int				nza;
	int				nzb;
	float			x1;
	float			x2;
	int				z1;
	int				z2;
	int				z1a;
	int				z1b;
	int				z2a;
	int				z2b;
	int				c_za;
	int				c_zb;
	int				win_x;
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
	t_vector		velocity;
	float			acceleration;
	int				ground;
	int				falling;
	int				moving;
	int				ducking;
	int				quit;
	int				pause;
	SDL_Event		event;
	float			eye_height;
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

struct	s_render
{
	t_rend_sector	now;
	t_rend_sector	queue[MAX_SECTORS_RENDERED];
	t_rend_sector	*tail;
	t_rend_sector	*head;
	int				*rendered_sectors;
	int				ztop[WIN_WIDTH];
	int				zbottom[WIN_WIDTH];
	t_sector		*sect;
	t_vertex		t1;
	t_vertex		t2;
	t_vertex		v1;
	t_vertex		v2;

	t_vertex		mc;
	t_vertex		i1;
	t_vertex		i2;

	int				t1_1_line;
	int				t1_2_line;
	int				t2_1_line;
	int				t2_2_line;
	int				max_sector_rendered;
	// float			vx1;
	float			pcos;
	float			psin;
	// float			vy1;
	// float			vx2;
	// float			vy2;
	// float			tx2;
	// float			ty2;
	int				begin_x;
	int				end_x;
	float			y;
	int				za;
	int				zb;
	int				nza;
	int				nzb;
	float			x1;
	float			x2;
	int				z1;
	int				z2;
	float			xscale1;
	float			xscale2;
	float			zscale1;
	float			zscale2;
	float			zceil;
	float			zfloor;
	float			nzceil;
	float			nzfloor;
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
	float			exact_begin;
	//added after merge
	int				c_za;
 	int				c_zb;
	int				win_x; // new == x;
 	int				win_y; // new == y;
	int				wall_num; // new uses to give 
	float tx1;
    float tx2;
	float tz1;
    float tz2;
	float lp_x;
	int				fog_distance;
 	double			fog_perc;
	double			floor_x;
	double			floor_y;
	//till this
	Uint32			*pix;
	t_line			line;
	Uint32			last_frame;
	Uint32			this_frame;
	t_plane			cplane;
	t_plane			fplane;
	t_plane			ncplane;
	t_plane			nfplane;
	char			neighbor;
};

struct	s_ui
{
	SDL_Rect		*minimap_rect;
	SDL_Surface		*minimap_surf;
};

struct s_texture
{
	SDL_Surface		**wall_tex;
	SDL_Surface		**sky_box;
	SDL_Surface		*pause;
	t_sprite_list	*sprites;
	int				c_sprt;
	unsigned int	x_text;
	int				y_text;
	double			x_point;
	double			y_point;
	int				color;
	int				wall_end;
	int				x_split;
	int				y_split;
};

struct s_skybox
{
	int				win_x;
	int				text_x;
	int				win_y;
	int				text_y;
	int				pos_angle;
	int				pos_max;
};

struct	s_doom
{
	t_render		render;
	t_ui			ui;
	t_sdl			sdl;
	t_option		options;
	t_map			map;
	t_game			game;
	t_player		player;
	t_texture		texture;
	t_skybox		sky;
	SDL_DisplayMode win_size;
	t_sprite_render	spriter; //draw all things
};

//friendly user stuff
int			print_usage(void);
int			error_message(char *message);

//UI
int			prepare_to_draw_ui(t_doom *doom);


//parser & initial
int			read_file(t_doom *doom, char *file_name);
int			init_sdl(t_sdl *sdl, t_option *options);


//game loop
void		player_events(t_doom *d);
void		game_events(t_doom *d);
int			game_loop(t_doom doom);


//render
int			draw_screen(t_doom doom);
int			user_interface(t_doom *doom);
int			draw_minimap(t_doom *d);

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

/*
**texturelaod.c
*/
void		wall_tex(t_texture *texture, t_sdl *sdl);
SDL_Surface	*load_tex(char *path, t_sdl *sdl);
void		pix_to_surf(t_render *r, int x, int y, int color);
Uint32		pix_from_text(SDL_Surface *texture, int x, int y);
int			stop(char *str); // for testing
int			color_mix(Uint32 start, Uint32 end, float per);
/*
**main_render.c
*/
void		textline_draw(int y1, int y2, t_render *r, t_texture *t, t_doom d,float lp_x);
void		wall_side(t_render *r, t_doom d);
void		prepare_to_rendering(t_render *r, t_doom d);
void		display_core(SDL_Renderer *render, SDL_Texture *texture, SDL_Surface *surface);
void		floorline_draw(int x, int y, int new_col, int old_col, t_doom d);
/*
**skybox.c
*/
void		draw_skybox(t_render *r, t_doom d);
void		draw_sky_line(t_render *r, t_doom d);

/*
**sprites.c && load.c
*/
int		translate_and_rotate_sprites(t_sprite	*arr_spr, int len, t_player	p);
int			sprite_sort(t_sprite *arr_spr, int len);
void	load_sprites(t_texture *texture, t_sdl *sdl, char *path);
t_sprite_list	*split_image_to_sprites(SDL_Surface *surr, int w, int h);
int			*copy_static_arr(int *arr, const int len);

#endif
