/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 16:56:18 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/02 16:56:18 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	init_map(t_mlx_data *data)
{
	data->map.width = 8;
	data->map.height = 12;
	data->map.grid = malloc(sizeof(char *) * data->map.height);
	if (!data->map.grid)
		return (1);
	if (data->map.width >= data->map.height)
		data->map.scale = (WIN_W / 4 / data->map.width);
	else
		data->map.scale = (WIN_H / 4 / data->map.height);
	data->map.grid[0] = "11111111";
	data->map.grid[1] = "10100001";
	data->map.grid[2] = "10101001";
	data->map.grid[3] = "10000001";
	data->map.grid[4] = "10101101";
	data->map.grid[5] = "10001101";
	data->map.grid[6] = "10000001";
	data->map.grid[7] = "10000001";
	data->map.grid[8] = "10000001";
	data->map.grid[9] = "10000001";
	data->map.grid[10] = "10000001";
	data->map.grid[11] = "11111111";
	return (0);
}

void	draw_map(t_mlx_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map.grid[y][x] == '1')
			{
				int i = 0;
				while (i < data->map.scale)
				{
					int j = 0;
					while (j < data->map.scale)
					{
						put_pixel(&data->img, (x * data->map.scale) + j, (y * data->map.scale) + i, 0x0000FF);
						j++;
					}
					i++;
				}
			}
			else
			{
				int i = 0;
				while (i < data->map.scale)
				{
					int j = 0;
					while (j < data->map.scale)
					{
						put_pixel(&data->img, (x * data->map.scale) + j, (y * data->map.scale) + i, 0x444444);
						j++;
					}
					i++;
				}
			}
			x++;
		}
		y++;
	}
}

void	draw_minimap_borders(t_mlx_data *data)
{
	int x;
	int y;

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

void	draw_floor_ceiling(t_mlx_data *data, unsigned int f_color, unsigned int c_color)
{
	int x;
	int y;

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
