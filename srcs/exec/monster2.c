/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:51:59 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/15 16:51:59 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	animate_and_render_monsters(t_mlx_data *data)
{
	long long	current_time;
	t_texture	*current_tex;
	int			i;

	i = 0;
	sort_monsters(data);
	while (i < data->parsing->monster_count)
	{
		if (!data->monster[i].is_alive)
		{
			i++;
			continue ;
		}
		current_time = get_time_in_ms();
		if ((current_time / 300) % 2 == 0)
			current_tex = &data->monster[i].texture[0];
		else
			current_tex = &data->monster[i].texture[1];
		data->monster[i].current_tex = current_tex;
		render_single_monster(data, &data->monster[i]);
		i++;
	}
}

void	rsm2(t_mlx_data *data, t_monster *monster, t_render_monster m)
{
	m.draw_start_y = -m.sprite_dim / 2 + WIN_H / 2;
	if (m.draw_start_y < 0)
		m.draw_start_y = 0;
	m.draw_end_y = m.sprite_dim / 2 + WIN_H / 2;
	if (m.draw_end_y >= WIN_H)
		m.draw_end_y = WIN_H - 1;
	m.draw_start_x = -m.sprite_dim / 2 + m.sprite_screen_x;
	if (m.draw_start_x < 0)
		m.draw_start_x = 0;
	m.draw_end_x = m.sprite_dim / 2 + m.sprite_screen_x;
	if (m.draw_end_x >= WIN_W)
		m.draw_end_x = WIN_W - 1;
	m.stripe = m.draw_start_x;
	while (m.stripe < m.draw_end_x)
	{
		m.tex_x = (int)(256 * (m.stripe - (-m.sprite_dim / 2
						+ m.sprite_screen_x))
				* monster->current_tex->width / m.sprite_dim) / 256;
		if (m.tex_x < 0)
			m.tex_x = 0;
		if (m.transform_y > 0 && m.stripe >= 0 && m.stripe < WIN_W)
			draw_monster_stripe(data, monster, m);
		m.stripe++;
	}
}

void	render_single_monster(t_mlx_data *data, t_monster *monster)
{
	t_render_monster	m;

	m.sprite_x = monster->pos.x - data->player.pos.x;
	m.sprite_y = monster->pos.y - data->player.pos.y;
	m.dir_x = cos(data->player.dir);
	m.dir_y = sin(data->player.dir);
	m.plane_x = -m.dir_y * 0.66;
	m.plane_y = m.dir_x * 0.66;
	m.inv_det = 1.0 / (m.plane_x * m.dir_y - m.dir_x * m.plane_y);
	m.transform_x = m.inv_det * (m.dir_y * m.sprite_x - m.dir_x * m.sprite_y);
	m.transform_y = m.inv_det * (-m.plane_y * m.sprite_x
			+ m.plane_x * m.sprite_y);
	if (m.transform_y <= 0.1)
		return ;
	m.sprite_screen_x = (int)((WIN_W / 2)
			* (1 + m.transform_x / m.transform_y));
	m.sprite_dim = abs((int)(WIN_H / m.transform_y));
	rsm2(data, monster, m);
}

void	find_next_xy(t_mlx_data *data, double *next_x, double *next_y, int i)
{
	if (data->monster[i].keys.w)
	{
		*next_x += cos(data->monster[i].dir) * data->monster[i].move_speed;
		*next_y += sin(data->monster[i].dir) * data->monster[i].move_speed;
	}
	if (data->monster[i].keys.s)
	{
		*next_x -= cos(data->monster[i].dir) * data->monster[i].move_speed;
		*next_y -= sin(data->monster[i].dir) * data->monster[i].move_speed;
	}
	if (data->monster[i].keys.a)
	{
		*next_x += cos(data->monster[i].dir - M_PI_2)
			* data->monster[i].move_speed;
		*next_y += sin(data->monster[i].dir - M_PI_2)
			* data->monster[i].move_speed;
	}
	if (data->monster[i].keys.d)
	{
		*next_x += cos(data->monster[i].dir + M_PI_2)
			* data->monster[i].move_speed;
		*next_y += sin(data->monster[i].dir + M_PI_2)
			* data->monster[i].move_speed;
	}
}

void	update_monster_position(t_mlx_data *data)
{
	double	next_x;
	double	next_y;
	double	buffer;
	int		i;

	i = 0;
	while (i < data->parsing->monster_count)
	{
		next_x = data->monster[i].pos.x;
		next_y = data->monster[i].pos.y;
		find_next_xy(data, &next_x, &next_y, i);
		if (next_x > data->monster[i].pos.x)
			buffer = 0.5;
		else
			buffer = -0.5;
		if (!is_wall(data, next_x + buffer, data->monster[i].pos.y))
			data->monster[i].pos.x = next_x;
		if (next_y > data->monster[i].pos.y)
			buffer = 0.5;
		else
			buffer = -0.5;
		if (!is_wall(data, data->monster[i].pos.x, next_y + buffer))
			data->monster[i].pos.y = next_y;
		i++;
	}
}
