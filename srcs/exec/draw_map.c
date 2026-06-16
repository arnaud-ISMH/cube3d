/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 16:56:18 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/10 14:19:19 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	init_map(t_mlx_data *data)
{
	int	scale_x;
	int	scale_y;

	data->map = data->parsing->map;
	scale_x = (WIN_W / 4) / data->map.width;
	scale_y = (WIN_H / 4) / data->map.height;
	if (scale_x < scale_y)
		data->map.scale = scale_x;
	else
		data->map.scale = scale_y;
	if (data->map.scale <= 0)
		data->map.scale = 1;
	return (0);
}

void	draw_map(t_mlx_data *data)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map.grid[y][x] == '1')
				minimap_wall(data, x, y);
			else
				minimap_floor(data, x, y);
			i = -1;
			while (++i < data->parsing->door_count)
				if (x == data->parsing->door[i].x
					&& y == data->parsing->door[i].y)
					minimap_door(data, x, y, data->parsing->door[i].open);
			x++;
		}
		y++;
	}
}

int	is_wall(t_mlx_data *data, double x, double y)
{
	int	map_x;
	int	map_y;
	int	i;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= data->map.height || map_x < 0
		|| map_x >= data->map.width)
		return (1);
	if (data->map.grid[map_y][map_x] == '1')
		return (1);
	i = -1;
	while (++i < data->parsing->door_count)
		if (map_x == data->parsing->door[i].x
			&& map_y == data->parsing->door[i].y
			&& !data->parsing->door[i].open)
			return (1);
	return (0);
}
