/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:03:23 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/15 16:03:23 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	minimap_wall(t_mlx_data *data, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.scale)
	{
		j = 0;
		while (j < data->map.scale)
		{
			put_pixel(&data->img, (x * data->map.scale) + j,
				(y * data->map.scale) + i, 0x0000FF);
			j++;
		}
		i++;
	}
}

void	minimap_door(t_mlx_data *data, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.scale)
	{
		j = 0;
		while (j < data->map.scale)
		{
			put_pixel(&data->img, (x * data->map.scale) + j,
				(y * data->map.scale) + i, 0xFF00FF);
			j++;
		}
		i++;
	}
}

void	minimap_floor(t_mlx_data *data, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.scale)
	{
		j = 0;
		while (j < data->map.scale)
		{
			put_pixel(&data->img, (x * data->map.scale) + j,
				(y * data->map.scale) + i, 0x444444);
			j++;
		}
		i++;
	}
}

void	draw_minimap_borders(t_mlx_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y <= WIN_H / 4)
	{
		put_pixel(&data->img, WIN_W / 4, y, 0xFFFFFF);
		y++;
	}
	x = 0;
	while (x <= WIN_W / 4)
	{
		put_pixel(&data->img, x, WIN_H / 4, 0xFFFFFF);
		x++;
	}
}

void	draw_floor_ceiling(t_mlx_data *data, unsigned int f_color,
						unsigned int c_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H / 2)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(&data->img, x, y, c_color);
			x++;
		}
		y++;
	}
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(&data->img, x, y, f_color);
			x++;
		}
		y++;
	}
}
