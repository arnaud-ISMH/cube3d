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
	data->map.grid[0] = "11111111";
	data->map.grid[1] = "10100001";
	data->map.grid[2] = "10100001";
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

void	cut_screen_in_half(t_mlx_data *data)
{
	int x;
	int y;

	x = WIN_W / 2;
	y = 0;
	while (y < WIN_H)
	{
		put_pixel(&data->img, x, y, 0xFFAAAA);
		y++;
	}
}

void	draw_map(t_mlx_data *data)
{
	int x;
	int y;
	int scale;

	cut_screen_in_half(data);

	scale = (data->map.width > data->map.height) ? (WIN_W / 2 / data->map.width) : (WIN_H / data->map.height);
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map.grid[y][x] == '1')
			{
				int i = 0;
				while (i < scale)
				{
					int j = 0;
					while (j < scale)
					{
						put_pixel(&data->img, (x * scale) + j, (y * scale) + i, 0x0000FF);
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

