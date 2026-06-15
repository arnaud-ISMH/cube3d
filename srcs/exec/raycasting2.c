/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 17:19:08 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/15 17:19:08 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	get_ray_vect(t_mlx_data *data, t_raycast *ray, int i)
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

	camera_x = 2.0 * i / (double)WIN_W - 1.0;
	dir_x = cos(data->player.dir);
	dir_y = sin(data->player.dir);
	plane_x = -dir_y * 0.66;
	plane_y = dir_x * 0.66;
	ray->ray_dir_x = dir_x + plane_x * camera_x;
	ray->ray_dir_y = dir_y + plane_y * camera_x;
	ray->map_x = (int)data->player.pos.x;
	ray->map_y = (int)data->player.pos.y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
}

void	draw_rays_minimap(t_mlx_data *data, t_raycast ray)
{
	double	ray_length_2d;
	int		k;
	int		r_x;
	int		r_y;

	if (ray.side == 0)
		ray_length_2d = (ray.side_dist_x - ray.delta_dist_x);
	else
		ray_length_2d = (ray.side_dist_y - ray.delta_dist_y);
	k = 0;
	while (k < (int)(ray_length_2d * data->map.scale))
	{
		r_x = (int)(data->player.pos.x * data->map.scale)
			+ (int)(ray.ray_dir_x * k);
		r_y = (int)(data->player.pos.y * data->map.scale)
			+ (int)(ray.ray_dir_y * k);
		put_pixel(&data->img, r_x, r_y, 0x555555);
		k++;
	}
}

void	init_dda(t_mlx_data *data, t_raycast *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.pos.x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player.pos.x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.pos.y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player.pos.y)
			* ray->delta_dist_y;
	}
}

void	dda_loop(t_mlx_data *data, t_raycast *ray)
{
	ray->side = 0;
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= data->map.width
			|| ray->map_y < 0 || ray->map_y >= data->map.height)
			break ;
		if (data->map.grid[ray->map_y][ray->map_x] == '1')
			break ;
	}
}

void	fish_eye_correction(t_raycast *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	if (ray->perp_wall_dist <= 0)
		ray->perp_wall_dist = 0.01;
}
