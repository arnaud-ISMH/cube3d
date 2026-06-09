/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 23:32:17 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/08 15:01:39 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include <stdbool.h>

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
}		t_texture;


typedef struct s_player
{
	t_coord	pos;
	float	direction;
	double	move_speed;
	t_keys	keys;
}		t_player;

typedef struct s_monster
{
	t_coord		pos;
	float		direction;
	double		move_speed;
	t_keys		keys;
	t_texture	*texture;
	t_texture	*current_tex;
}		t_monster;


typedef struct s_map
{
	int		width;
	int		height;
	char	**grid;
	int		scale;
}		t_map;

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
	int				screen_x; // Coordonnée X à l'écran pour dessiner la colonne verticale
	int				y_pixel; // Coordonnée Y actuelle à l'écran pour dessiner la colonne verticale
	unsigned int	color; // Couleur du pixel à dessiner (après avoir pioché dans la texture)
}		t_raycast;

typedef struct s_mlx_data
{
	void		*mlx;
	void		*win;
	t_image		img;
	t_keys		keys;
	t_player	player;
	t_monster	monster;
	t_map		map;
	double		z_buffer[1800];
	t_texture	texture_north;
	t_texture	texture_south;
	t_texture	texture_east;
	t_texture	texture_west;
	t_texture	texture_monster;
}		t_mlx_data;

#endif
