/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:46:20 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/08 16:46:20 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	init_monster(t_mlx_data *data)
{
	int	i;

	data->monster = malloc(sizeof(t_monster) * data->parsing->monster_count);
	if (!data->monster)
		return (1);
	i = 0;
	while (i < data->parsing->monster_count)
	{
		data->monster[i].pos.x = data->parsing->monster[i].pos.x + 0.5;
		data->monster[i].pos.y = data->parsing->monster[i].pos.y + 0.5;
		data->monster[i].dir = 0.0f;
		data->monster[i].move_speed = 0.01;
		data->monster[i].keys.w = false;
		data->monster[i].keys.a = false;
		data->monster[i].keys.s = false;
		data->monster[i].keys.d = false;
		data->monster[i].keys.left = false;
		data->monster[i].keys.right = false;
		data->monster[i].is_alive = true;
		i++;
	}
	return (0);
}

void	draw_monster(t_mlx_data *data, unsigned int color)
{
	int	monster_index;
	int	i;
	int	j;
	int	p_x;
	int	p_y;

	monster_index = 0;
	while (monster_index < data->parsing->monster_count)
	{
		if (data->monster[monster_index].is_alive)
		{
			p_x = (int)(data->monster[monster_index].pos.x * data->map.scale);
			p_y = (int)(data->monster[monster_index].pos.y * data->map.scale);
			i = -4;
			while (++i <= 3)
			{
				j = -4;
				while (++j <= 3)
					put_pixel(&data->img, p_x + i, p_y + j, color);
			}
		}
		monster_index++;
	}
}

void	calculate_monsters_distance(t_mlx_data *data)
{
	int	i;

	i = 0;
	while (i < data->parsing->monster_count)
	{
		data->monster[i].distance = ((data->player.pos.x
					- data->monster[i].pos.x) * (data->player.pos.x
					- data->monster[i].pos.x)) + ((data->player.pos.y
					- data->monster[i].pos.y) * (data->player.pos.y
					- data->monster[i].pos.y));
		i++;
	}
}

void	sort_monsters(t_mlx_data *data)
{
	int			i;
	int			j;
	t_monster	tmp;

	calculate_monsters_distance(data);
	i = 0;
	while (i < data->parsing->monster_count - 1)
	{
		j = 0;
		while (j < data->parsing->monster_count - i - 1)
		{
			if (data->monster[j].distance < data->monster[j + 1].distance)
			{
				tmp = data->monster[j];
				data->monster[j] = data->monster[j + 1];
				data->monster[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	draw_monster_stripe(t_mlx_data *data,
						t_monster *monster, t_render_monster m)
{
	int				y;
	int				tex_y;
	int				d;
	unsigned int	color;
	int				tex_offset;

	y = m.draw_start_y;
	while (y < m.draw_end_y)
	{
		if (m.stripe > WIN_W / 4 || y > WIN_H / 4)
		{
			d = (y) * 256 - WIN_H * 128 + m.sprite_dim * 128;
			tex_y = ((d * monster->current_tex->height) / m.sprite_dim) / 256;
			if (tex_y < 0)
				tex_y = 0;
			tex_offset = (tex_y * monster->current_tex->size_line)
				+ (m.tex_x * (monster->current_tex->bpp / 8));
			color = *(unsigned int *)(monster->current_tex->img_data
					+ tex_offset);
			if (color != 0x00FF00 && m.transform_y < data->z_buffer[m.stripe])
				put_pixel(&data->img, m.stripe, y, color);
		}
		y++;
	}
}
