/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:44:44 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/09 13:40:27 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	init_player(t_mlx_data *data)
{
	data->player.pos.x = data->parsing->player_x + 0.5;
	data->player.pos.y = data->parsing->player_y + 0.5;
	data->player.move_speed = 0.05;
	if (data->parsing->player_orientation == 'N')
		data->player.dir = 3.0 * M_PI / 2.0;
	else if (data->parsing->player_orientation == 'S')
		data->player.dir = M_PI / 2.0;
	else if (data->parsing->player_orientation == 'E')
		data->player.dir = 0.0;
	else if (data->parsing->player_orientation == 'W')
		data->player.dir = M_PI;
	ft_bzero(&data->player.keys, sizeof(t_keys));
	data->flash_start_time = 0;
	data->is_flashing = false;
}

void	draw_player(t_mlx_data *data, unsigned int color)
{
	int	i;
	int	j;
	int	p_x;
	int	p_y;

	p_x = (int)(data->player.pos.x * data->map.scale);
	p_y = (int)(data->player.pos.y * data->map.scale);
	i = -3;
	while (i <= 3)
	{
		j = -3;
		while (j <= 3)
		{
			put_pixel(&data->img, p_x + i, p_y + j, color);
			j++;
		}
		i++;
	}
}

void	find_nxy(t_mlx_data *data, double *next_x, double *next_y)
{
	if (data->player.keys.w)
	{
		*next_x += cos(data->player.dir) * data->player.move_speed;
		*next_y += sin(data->player.dir) * data->player.move_speed;
	}
	if (data->player.keys.s)
	{
		*next_x -= cos(data->player.dir) * data->player.move_speed;
		*next_y -= sin(data->player.dir) * data->player.move_speed;
	}
	if (data->player.keys.a)
	{
		*next_x += cos(data->player.dir - M_PI_2) * data->player.move_speed;
		*next_y += sin(data->player.dir - M_PI_2) * data->player.move_speed;
	}
	if (data->player.keys.d)
	{
		*next_x += cos(data->player.dir + M_PI_2) * data->player.move_speed;
		*next_y += sin(data->player.dir + M_PI_2) * data->player.move_speed;
	}
}

void	change_oritentation(t_mlx_data *data)
{
	if (data->player.keys.left)
	{
		data->player.dir -= 0.04f;
		if (data->player.dir < 0)
			data->player.dir += 2 * M_PI;
	}
	if (data->player.keys.right)
	{
		data->player.dir += 0.04f;
		if (data->player.dir >= 2 * M_PI)
			data->player.dir -= 2 * M_PI;
	}
}

void	update_player_position(t_mlx_data *data)
{
	double	next_x;
	double	next_y;
	double	buffer;

	next_x = data->player.pos.x;
	next_y = data->player.pos.y;
	find_nxy(data, &next_x, &next_y);
	if (next_x > data->player.pos.x)
		buffer = 0.1;
	else
		buffer = -0.1;
	if (!is_wall(data, next_x + buffer, data->player.pos.y))
		data->player.pos.x = next_x;
	if (next_y > data->player.pos.y)
		buffer = 0.1;
	else
		buffer = -0.1;
	if (!is_wall(data, data->player.pos.x, next_y + buffer))
		data->player.pos.y = next_y;
	change_oritentation(data);
}
