/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 09:35:11 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/16 14:46:32 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "structs.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

// DRAW MAP
void		draw_map(t_mlx_data *data);
int			init_map(t_mlx_data *data);
int			is_wall(t_mlx_data *data, double x, double y);

// INIT
int			init_textures(t_mlx_data *data);
int			load_texture(t_mlx_data *data, t_texture *texture, char *path);
void		display_score(t_mlx_data *data);
int			redraw(t_mlx_data *data);
t_mlx_data	minilibx_process(void);

// MINIMAP
void		minimap_wall(t_mlx_data *data, int x, int y);
void		minimap_floor(t_mlx_data *data, int x, int y);
void		minimap_door(t_mlx_data *data, int x, int y, int open);
void		draw_floor_ceiling(t_mlx_data *data, unsigned int f_color,
				unsigned int c_color);
void		draw_minimap_borders(t_mlx_data *data);

// MONSTER
int			init_monster(t_mlx_data *data);
void		draw_monster(t_mlx_data *data, unsigned int color);
void		calculate_monsters_distance(t_mlx_data *data);
void		sort_monsters(t_mlx_data *data);
void		draw_monster_stripe(t_mlx_data *data, t_monster *monster,
				t_render_monster m);

// MONSTER2
void		animate_and_render_monsters(t_mlx_data *data);
void		render_single_monster(t_mlx_data *data, t_monster *monster);
void		rsm2(t_mlx_data *data, t_monster *monster, t_render_monster m);
void		find_next_xy(t_mlx_data *data, double *next_x, double *next_y,
				int i);
void		update_monster_position(t_mlx_data *data);

// PLAYER
void		init_player(t_mlx_data *data);
void		draw_player(t_mlx_data *data, unsigned int color);
void		find_nxy(t_mlx_data *data, double *next_x, double *next_y);
void		change_oritentation(t_mlx_data *data);
void		update_player_position(t_mlx_data *data);

// RAYCASTING
void		choose_tex(t_mlx_data *data, t_raycast *ray);
void		draw_tex_on_wall(t_mlx_data *data, t_raycast *ray, int i);
void		render_3d(t_mlx_data *data, t_raycast *ray, int i);
void		raycasting(t_mlx_data *data);

// RAYCASTING2
void		get_ray_vect(t_mlx_data *data, t_raycast *ray, int i);
void		draw_rays_minimap(t_mlx_data *data, t_raycast ray);
void		init_dda(t_mlx_data *data, t_raycast *ray);
void		dda_loop(t_mlx_data *data, t_raycast *ray);
void		fish_eye_correction(t_raycast *ray);

// UTILS
int			put_pixel(t_image *img, int x, int y, unsigned int color);
void		trigger_eat_effect(t_mlx_data *data);
void		eat_animation(t_mlx_data *data);
void		draw_mm_range_atk(t_mlx_data *data);
int			eat_monster(t_mlx_data *data);

// UTILS2
void		free_monster_tex(t_mlx_data *data);
int			close_win(t_mlx_data *data);
int			mouse_move(int x, int y, t_mlx_data *data);
int			open_door(t_mlx_data *data);
int			detect_closed_door(t_mlx_data *data, t_raycast *ray);

// UTILS3
void		moove_monster(t_mlx_data *data);
int			key_press(int keysym, t_mlx_data *data);
int			key_release(int keysym, t_mlx_data *data);
long long	get_time_in_ms(void);

/*PARSING*/
int			read_file(char *arg, t_parsing *parsing);
int			is_identifier_free(t_parsing *parsing, char c);

/*CHECKCUB*/
int			check_color(t_parsing *parsing, char *line, char color);
int			check_texture(t_parsing *parsing, char *line, char texture);
int			check_map(t_parsing *parsing, int fd, char *line);

/*GRID*/
void		fill_map(t_parsing *parsing, t_list *map_list);
int			flood_fill(t_map *map, int x, int y);

/*MAP*/
int			ft_forbidden(char c);
int			parse_map(t_parsing *parsing);
int			set_player(t_parsing *parsing, int x, int y, char c);
int			parse_chara(t_parsing *parsing, int x, int y);

/*UTILS*/
int			max(int a, int b);
void		printerr(char *msg);
void		free_parsing(t_parsing *parsing);
char		**freefree(char **split);
int			open_fd(char *arg);

/*UTILS2*/
void		strip(char *s);
int			ft_isnumber(char *line);
int			good_color(char *line);
int			rgb2hex(int r, int g, int b);
int	close_win_early(t_mlx_data *data); //exec

/*INIT*/
t_parsing	*init_parsing(void);
t_parsing	*check_args(int ac, char **av);

/*BONUS*/
void		count_entities(t_parsing *parsing, int *ndoors, int *nmonsters);
int			check_door(t_parsing *parsing, int x, int y);
int			texture_monster(t_parsing *parsing, char *line, char texture);

#endif
