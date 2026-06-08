/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:44:44 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/02 14:44:44 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	init_player(t_mlx_data *data)
{
	data->player.x = WIN_W / 4;
	data->player.y = WIN_H / 4;
	data->player.direction = 0.0f;
	data->player.move_speed = 2;
	data->player.keys.w = false;
	data->player.keys.a = false;
	data->player.keys.s = false;
	data->player.keys.d = false;
	data->player.keys.left = false;
	data->player.keys.right = false;
}

void	draw_player(t_mlx_data *data, unsigned int color)
{
	int	i;
	int	j;
	int k;

	i = -5;
	while (i <= 5)
	{
		j = -5;
		while (j <= 5)
		{
			put_pixel(&data->img, data->player.x + i, data->player.y + j, color);
			j++;
		}
		i++;
	}
	k = 0;
	while (k <= 15)
	{
		put_pixel(&data->img, data->player.x + (int)(cos(data->player.direction) * k),
			data->player.y + (int)(sin(data->player.direction) * k), 0xFF0000);
		k++;
	}
}

void	update_player_position(t_mlx_data *data)
{
	if (data->player.keys.w)
	{
		data->player.x += (int)(cos(data->player.direction) * data->player.move_speed);
		data->player.y += (int)(sin(data->player.direction) * data->player.move_speed);
	}
	if (data->player.keys.s)
	{
		data->player.x -= (int)(cos(data->player.direction) * data->player.move_speed);
		data->player.y -= (int)(sin(data->player.direction) * data->player.move_speed);
	}
	if (data->player.keys.a)
	{
		data->player.x += (int)(cos(data->player.direction - M_PI_2) * data->player.move_speed);
		data->player.y += (int)(sin(data->player.direction - M_PI_2) * data->player.move_speed);
	}
	if (data->player.keys.d)
	{
		data->player.x += (int)(cos(data->player.direction + M_PI_2) * data->player.move_speed);
		data->player.y += (int)(sin(data->player.direction + M_PI_2) * data->player.move_speed);
	}
	if (data->player.keys.left)
	{
		data->player.direction -= 0.05f;
		if (data->player.direction < 0)
			data->player.direction += 2 * M_PI;
	}
	if (data->player.keys.right)
	{
		data->player.direction += 0.05f;
		if (data->player.direction >= 2 * M_PI)
			data->player.direction -= 2 * M_PI;
	}
}
