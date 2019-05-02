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
# define SPEED_ROTATION 0.03f
# define SPEED_ROTATION_Z 0.05f
# define MAX_Z_ANGLE 5
# define MOVE_SPEED 0.2f
# define SIT_EYE_HEIGHT 3
# define EYE_HEIGHT 6
# define HEAD_HEIGHT 1
# define KNEE_HEIGHT 2
# define BIG_VALUE 9e9

# define MINIMAP_WIDTH 240
# define MINIMAP_HEIGHT	160

# define NEAR_Y	1e-3f
# define FAR_Y	5
# define NEAR_X 1e-4f
# define FAR_X	20
# define HFOV (0.5 * WIN_WIDTH)	//horizontal field of view (radians?)
# define VFOV (0.2 * WIN_HEIGHT)	//vertical field of view (radians?)

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

typedef struct s_doom	t_doom;

typedef struct s_sdl	t_sdl;
typedef struct s_option	t_option;

typedef struct s_map	t_map;
typedef struct s_vertex	t_vertex;
typedef struct s_sector	t_sector;
typedef struct s_player	t_player;
typedef struct s_line	t_line;
typedef struct s_game	t_game;
typedef struct s_vector	t_vector;
typedef struct s_render	t_render;
typedef struct s_plane	t_plane;
typedef struct s_ui		t_ui;

struct	s_plane
{
	float a;
	float b;
	float c;
	float h;
};

struct	s_vector
{
	float		x;
	float		y;
	float		z;
};

struct	s_vertex
{
	float		x;
	float		y;
};

struct	s_player
{
	t_vector	coord; //earlier was t_vertex could cause some troubles
	Uint32		sector;
	float		angle;
	float		anglesin; 
	float		anglecos;
	float		angle_z; // angle of player z view
};

struct	s_line
{
	t_vertex	vert[2];
	SDL_Surface	*bot;
	SDL_Surface	*mid;
	SDL_Surface	*top;
};

struct	s_sector
{	
	Uint32		num;
	Uint32		num_vert;
	t_line		*lines; //same numeration as vert
	t_vertex	*vert;
	char		*neighbors;
	Uint32		floor_z; //should be replaced with equation of surface
	Uint32		ceil_z; //should be replaced with equation of surface
	t_plane		ceil_plane;
	t_plane		floor_plane;
};

struct	s_map
{
	Uint32		num_vert;
	t_vertex	*vertex; //delete this doesnt useful
	Uint32		num_sect;
	t_sector	*sectors;
};


struct	s_sdl
{
	SDL_Window	*window;
	SDL_Surface	*surface;
};

struct	s_game
{
	float		dx;
	float		dy;
	t_vector	velocity;
	float		acceleration;
	int			ground;
	int			falling;
	int			moving;
	int			ducking;
	int			quit;
	SDL_Event	event;
	float		eye_height;
};

struct	s_option
{
	int			difficult;
	int			music_volume_level;
	int			effects_volume_level;
};

typedef struct	s_rend_sector
{
	Uint32	num;
	int		sx1;
	int		sx2;
}				t_rend_sector;

struct	s_render
{
	t_rend_sector	now;
	int				ztop[WIN_WIDTH];
	int				zbottom[WIN_WIDTH];
	t_sector		*sect;
	t_vertex		t1;
	t_vertex		t2;
	t_vertex		v1;
	t_vertex		v2;

	float			vx1;
	float			pcos;
	float			psin;
	float			vy1;
	float			vx2;
	float			vy2;
	float			tx1;
	float			ty1;
	float			tx2;
	float			ty2;
	int				begin_x;
	int				end_x;
	float			y;
	int				za;
	int				zb;
	int				nza;
	int				nzb;
	int				x1;
	int				x2;
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
	Uint32			*pix;
	t_line			line;
	Uint32		last_frame;
	Uint32		this_frame;
};

struct	s_ui
{
	SDL_Rect	*minimap_rect;
	SDL_Surface	*minimap_surf;
};

struct	s_doom
{
	t_ui		ui;
	t_sdl		sdl;
	t_option	options;
	t_map		map;
	t_game		game;
	t_player	player;
	
};

//friendly user stuff
int			print_usage(void);
int			error_message(char *message);

//UI
int		prepare_to_draw_ui(t_doom *doom);


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

#endif
