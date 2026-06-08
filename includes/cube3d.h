/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 09:35:11 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/08 17:35:50 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "parsing.h"
# include "structs.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef WIN_W
#  define WIN_W 1800.0
# endif
# ifndef WIN_H
#  define WIN_H 1000.0
# endif

int			close_win(t_mlx_data *data);
int			redraw(t_mlx_data *data);
t_mlx_data	minilibx_process(void);

int			put_pixel(t_image *img, int x, int y, unsigned int color);
int			key_press(int keysym, t_mlx_data *data);
int			key_release(int keysym, t_mlx_data *data);

void		draw_player(t_mlx_data *data, unsigned int color);
void		init_player(t_mlx_data *data);
void		update_player_position(t_mlx_data *data);
int			mouse_move(int x, int y, t_mlx_data *data);

void		draw_map(t_mlx_data *data);
int			init_map(t_mlx_data *data);
int			is_wall(t_mlx_data *data, double x, double y);
void		draw_floor_ceiling(t_mlx_data *data, unsigned int f_color, unsigned int c_color);
void		draw_minimap_borders(t_mlx_data *data);

void		raycasting(t_mlx_data *data);
void		get_ray_vect(t_mlx_data *data, t_raycast *ray, int i);
void		init_dda(t_mlx_data *data, t_raycast *ray);
void		dda_loop(t_mlx_data *data, t_raycast *ray);
void		fish_eye_correction(t_raycast *ray);
void		render_3D(t_mlx_data * data, t_raycast *ray, int i);
void		draw_rays_minimap(t_mlx_data *data, t_raycast ray);
void		choose_tex(t_mlx_data *data, t_raycast *ray);
void		draw_tex_on_wall(t_mlx_data *data, t_raycast *ray, int i);

int			init_textures(t_mlx_data *data);
int			load_texture(t_mlx_data *data, t_texture *texture, char *path);

#endif
