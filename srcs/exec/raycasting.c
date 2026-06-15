/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:56:51 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/08 17:35:55 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	choose_tex(t_mlx_data *data, t_raycast *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			ray->tex = &data->texture_west;
		else
			ray->tex = &data->texture_east;
		ray->wall_x = data->player.pos.y + ray->perp_wall_dist
			* ray->ray_dir_y;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			ray->tex = &data->texture_north;
		else
			ray->tex = &data->texture_south;
		ray->wall_x = data->player.pos.x + ray->perp_wall_dist
			* ray->ray_dir_x;
	}
}

void	draw_tex_on_wall(t_mlx_data *data, t_raycast *ray, int i)
{
	ray->screen_x = i;
	ray->y_pixel = ray->draw_start;
	while (ray->y_pixel < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos % ray->tex->height;
		if (ray->tex_y < 0)
			ray->tex_y = 0;
		ray->tex_pos += ray->tex_step;
		if (ray->screen_x <= WIN_W / 4 && ray->y_pixel <= WIN_H / 4)
		{
			ray->y_pixel++;
			continue ;
		}
		ray->tex_offset = (ray->tex_y * ray->tex->size_line)
			+ (ray->tex_x * (ray->tex->bpp / 8));
		ray->color = *(unsigned int *)(ray->tex->img_data + ray->tex_offset);
		put_pixel(&data->img, ray->screen_x, ray->y_pixel, ray->color);
		ray->y_pixel++;
	}
}

void	render_3d(t_mlx_data *data, t_raycast *ray, int i)
{
	ray->wall_height = (int)(WIN_H / ray->perp_wall_dist);
	ray->draw_start = (WIN_H / 2) - (ray->wall_height / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (WIN_H / 2) + (ray->wall_height / 2);
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
	choose_tex(data, ray);
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)ray->tex->width);
	ray->tex_step = 1.0 * ray->tex->height / ray->wall_height;
	ray->tex_pos = (ray->draw_start - WIN_H / 2 + ray->wall_height / 2)
		* ray->tex_step;
	draw_tex_on_wall(data, ray, i);
}

void	raycasting(t_mlx_data *data)
{
	int			i;
	t_raycast	ray;

	i = 0;
	while (i < WIN_W)
	{
		get_ray_vect(data, &ray, i);
		init_dda(data, &ray);
		dda_loop(data, &ray);
		fish_eye_correction(&ray);
		data->z_buffer[i] = ray.perp_wall_dist;
		render_3d(data, &ray, i);
		draw_rays_minimap(data, ray);
		i++;
	}
	animate_and_render_monsters(data);
}
