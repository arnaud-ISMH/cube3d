/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:13:52 by adeflers          #+#    #+#             */
/*   Updated: 2026/02/01 00:13:52 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	put_pixel(t_image *img, int x, int y, unsigned int color)
{
	int	offset;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return (0);
	offset = (y * img->size_line) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->img_data)) = color;
	return (1);
}

void	trigger_eat_effect(t_mlx_data *data)
{
	data->flash_start_time = get_time_in_ms();
	data->is_flashing = true;
	data->score += 1;
}

void	eat_animation(t_mlx_data *data)
{
	long long	current_time;
	long long	elapsed;
	int			i;
	int			j;

	current_time = get_time_in_ms();
	elapsed = current_time - data->flash_start_time;
	if (!data->is_flashing)
		return ;
	if (elapsed >= 200)
	{
		data->is_flashing = false;
		return ;
	}
	if ((elapsed >= 0 && elapsed < 50) || (elapsed >= 100 && elapsed < 150))
	{
		i = -1;
		while (++i < WIN_W)
		{
			j = -1;
			while (++j < WIN_H)
				if (!(i <= WIN_W / 4 && j <= WIN_H / 4))
					put_pixel(&data->img, i, j, 0xFF0000);
		}
	}
}

void	draw_mm_range_atk(t_mlx_data *data)
{
	int	radius;
	int	center_x;
	int	center_y;
	int	angle;

	radius = 10;
	center_x = (int)(data->player.pos.x * data->map.scale);
	center_y = (int)(data->player.pos.y * data->map.scale);
	angle = 0;
	while (angle < 360)
	{
		put_pixel(&data->img,
			center_x + (int)(radius * cos(angle * M_PI / 180.0)),
			center_y + (int)(radius * sin(angle * M_PI / 180.0)),
			0xFF0000);
		angle += 5;
	}
}

int	eat_monster(t_mlx_data *data)
{
	int		i;
	double	distance;

	draw_mm_range_atk(data);
	i = 0;
	while (i < data->parsing->monster_count)
	{
		if (data->monster[i].is_alive)
		{
			distance = sqrt(pow(data->player.pos.x - data->monster[i].pos.x, 2)
					+ pow(data->player.pos.y - data->monster[i].pos.y, 2));
			if (distance < 1.0)
			{
				data->monster[i].is_alive = false;
				trigger_eat_effect(data);
				return (1);
			}
		}
		i++;
	}
	return (0);
}
