/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 09:35:11 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/08 15:01:22 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "structs.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
#include <sys/time.h>
# include "../srcs/parsing/parsing.h"

int			close_win(t_mlx_data *data);
int			redraw(t_mlx_data *data);
t_mlx_data	minilibx_process(void);
long long	get_time_in_ms(void);

int			put_pixel(t_image *img, int x, int y, unsigned int color);
int			key_press(int keysym, t_mlx_data *data);
int			key_release(int keysym, t_mlx_data *data);

void		draw_player(t_mlx_data *data, unsigned int color);
void		init_player(t_mlx_data *data);
void		update_player_position(t_mlx_data *data);
int			mouse_move(int x, int y, t_mlx_data *data);

void		init_monster(t_mlx_data *data);
void		draw_monster(t_mlx_data *data, unsigned int color);
void		draw_monster_stripe(t_mlx_data *data, t_monster *monster, int stripe, int tex_x, double transform_y, int sprite_dim, int draw_start_y, int draw_end_y);
void		render_single_monster(t_mlx_data *data, t_monster *monster);
int			init_monster_tex(t_mlx_data *data);
void		update_monster_position(t_mlx_data *data);
void		animate_and_render_monsters(t_mlx_data *data);

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
