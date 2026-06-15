/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 23:32:17 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/11 13:50:57 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

typedef struct s_map
{
	int		width;
	int		height;
	char	**grid;
	int scale;
}		t_map;

typedef struct	s_color
{
	int r;
	int g;
	int b;
}	t_color;

typedef struct s_keys
{
	bool w;
	bool a;
	bool s;
	bool d;
	bool left;
	bool right;
}   t_keys;

typedef struct s_coord
{
	double	x;
	double	y;
}		t_coord;

typedef struct s_texture
{
	void	*img_ptr;
	char	*img_data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}        t_texture;

typedef struct s_door
{
    int     x;
    int     y;
    int     open;  // 0 fermée, 1 ouverte
}   t_door;

typedef struct s_monster
{
	t_coord		pos;
	float		dir;
	double		move_speed;
	t_keys		keys;
	t_texture	texture[2];
	t_texture	*current_tex;
	double		distance; // pour le tri des monstres du plus loin au plus proche du player
	bool		is_alive;
}		t_monster;

typedef struct	s_parsing
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			f;
	int			c;
	char		*t1;
	char		*t2;
	int 		player_x;
	int 		player_y;
	char 		player_orientation;
	t_map		map;
	t_door		*door;
	int			door_count;
	t_monster	*monster;
	int			monster_count;
}	t_parsing;

# ifndef WIN_W
#  define WIN_W 1800.0
# endif
# ifndef WIN_H
#  define WIN_H 1000.0
# endif


typedef struct s_image
{
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
}		t_image;

typedef struct s_player
{
	t_coord	pos;
	float	dir;
	double	move_speed;
	t_keys	keys;
}		t_player;

typedef struct s_raycast
{
	float			ray_dir_x;
	float			ray_dir_y;
	int				map_x;
	int				map_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				side;
	double			side_dist_x;
	double			side_dist_y;
	int				step_x;
	int				step_y;
	double			perp_wall_dist; // Distance perpendiculaire pour éviter l'effet fish-eye
	float			wall_height;
	int				draw_start;
	int				draw_end;
	t_texture		*tex; // Pointeur vers la texture à utiliser pour ce mur
	double			wall_x; // Position exacte de l'impact sur le mur (0.0 à 1.0)
	int				tex_x; // Coordonnée X sur la texture
	int				tex_y; // Coordonnée Y sur la texture
	double			tex_step; // Combien de pixels de texture on avance pour 1 pixel écran
	double			tex_pos; // Position de départ de la texture pour l'interpolation verticale
	int				tex_offset; // offset memoire pour piocher la bonne couleur dans la texture
	int			 	screen_x; // Coordonnée X à l'écran pour dessiner la colonne verticale
	int				y_pixel; // Coordonnée Y actuelle à l'écran pour dessiner la colonne verticale
	unsigned int    color; // Couleur du pixel à dessiner (après avoir pioché dans la texture)
}        t_raycast;

typedef struct s_render_monster
{
    double	sprite_x;
    double	sprite_y;
    double	dir_x;
    double	dir_y;
    double	plane_x;
    double	plane_y;
    double	inv_det;
    double	transform_x;
    double	transform_y;
    int		sprite_screen_x;
    float	sprite_dim;
    int		draw_start_y;
    int		draw_end_y;
    int		draw_start_x;
    int		draw_end_x;
    int		stripe;
	int		tex_x;
}		t_render_monster;

typedef struct s_mlx_data
{
	void		*mlx;
	void		*win;
	t_image		img;
	t_keys		keys;
	t_player	player;
	t_monster	*monster;
	t_map		map;
	t_parsing	*parsing;
	t_raycast	*raycast;
	double		z_buffer[(int)WIN_W];
	t_texture	texture_north;
	t_texture	texture_south;
	t_texture	texture_west;
	t_texture	texture_east;
	// t_texture	texture_monster;
	t_texture	texture_door;
	long long	flash_start_time;
	bool		is_flashing;
	int			score;
}		t_mlx_data;

#endif
