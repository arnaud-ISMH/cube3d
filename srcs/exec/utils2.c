/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:17:24 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/15 16:17:24 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	free_monster_tex(t_mlx_data *data)
{
	int	i;

	i = 0;
	while (i < data->parsing->monster_count)
	{
		if (data->monster[i].texture[0].img_ptr)
			mlx_destroy_image(data->mlx, data->monster[i].texture[0].img_ptr);
		if (data->monster[i].texture[1].img_ptr)
			mlx_destroy_image(data->mlx, data->monster[i].texture[1].img_ptr);
		i++;
	}
}

int	close_win(t_mlx_data *data)
{
	mlx_destroy_image(data->mlx, data->img.img_ptr);
	if (data->texture_north.img_ptr)
		mlx_destroy_image(data->mlx, data->texture_north.img_ptr);
	if (data->texture_south.img_ptr)
		mlx_destroy_image(data->mlx, data->texture_south.img_ptr);
	if (data->texture_east.img_ptr)
		mlx_destroy_image(data->mlx, data->texture_east.img_ptr);
	if (data->texture_west.img_ptr)
		mlx_destroy_image(data->mlx, data->texture_west.img_ptr);
	if (data->texture_door.img_ptr)
		mlx_destroy_image(data->mlx, data->texture_door.img_ptr);
	free_monster_tex(data);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	if (data->monster)
		free(data->monster);
	if (data->parsing)
		free_parsing(data->parsing);
	free(data->mlx);
	free(data);
	exit (0);
}

int	mouse_move(int x, int y, t_mlx_data *data)
{
	int		center_x;
	int		delta_x;
	double	sensitivity;

	(void)y;
	center_x = WIN_W / 2;
	if (x == center_x)
		return (0);
	sensitivity = 0.002;
	delta_x = x - center_x;
	data->player.dir += delta_x * sensitivity;
	if (data->player.dir < 0)
		data->player.dir += 2 * M_PI;
	else if (data->player.dir >= 2 * M_PI)
		data->player.dir -= 2 * M_PI;
	mlx_mouse_move(data->mlx, data->win, WIN_W / 2, WIN_H / 2);
	return (0);
}

int	open_door(t_mlx_data *data)
{
	int		i;
	double	distance;

	i = 0;
	while (i < data->parsing->door_count)
	{
		distance = sqrt(pow(data->player.pos.x
					- (data->parsing->door[i].x + 0.5), 2)
				+ pow(data->player.pos.y
					- (data->parsing->door[i].y + 0.5), 2));
		if (distance < 1.0 && distance > 0.5)
		{
			data->parsing->door[i].open = !data->parsing->door[i].open;
			return (1);
		}
		i++;
	}
	return (0);
}

int	detect_closed_door(t_mlx_data *data, t_raycast *ray)
{
	int	i;

	i = -1;
	while (++i < data->parsing->door_count)
	{
		if (ray->map_x == data->parsing->door[i].x
			&& ray->map_y == data->parsing->door[i].y
			&& !data->parsing->door[i].open)
		{
			ray->hit_door = 1;
			return (1);
		}
	}
	return (0);
}
