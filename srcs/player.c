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
	// On fait spawner le joueur au milieu de la case (1, 1) par exemple
	// (Vérifie que c'est bien un '0' dans ta map !)
	data->player.pos.x = 1.5;
	data->player.pos.y = 1.5;
	data->player.direction = 0.0f;
	data->player.move_speed = 0.02; // Vitesse adaptée à la grille 1x1
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
	int scale;

	// On recalcule le scale uniquement pour l'affichage 2D
	if (data->map.width > data->map.height)
		scale = (WIN_W / 2 / data->map.width);
	else
		scale = (WIN_H / data->map.height);

	// Conversion coordonnées virtuelles -> pixels écran pour le dessin
	int p_x = (int)(data->player.pos.x * scale);
	int p_y = (int)(data->player.pos.y * scale);

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
	k = 0;
	while (k <= 15)
	{
		put_pixel(&data->img, p_x + (int)(cos(data->player.direction) * k),
			p_y + (int)(sin(data->player.direction) * k), 0xFF0000);
		k++;
	}
}

int	is_wall(t_mlx_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= data->map.height || map_x < 0 || map_x >= data->map.width)
		return (1);
	if (data->map.grid[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	update_player_position(t_mlx_data *data)
{
	double	next_x;
	double	next_y;
	double	buffer;

	next_x = data->player.pos.x;
	next_y = data->player.pos.y;
	if (data->player.keys.w)
	{
		next_x += cos(data->player.direction) * data->player.move_speed;
		next_y += sin(data->player.direction) * data->player.move_speed;
	}
	if (data->player.keys.s)
	{
		next_x -= cos(data->player.direction) * data->player.move_speed;
		next_y -= sin(data->player.direction) * data->player.move_speed;
	}
	if (data->player.keys.a)
	{
		next_x += cos(data->player.direction - M_PI_2) * data->player.move_speed;
		next_y += sin(data->player.direction - M_PI_2) * data->player.move_speed;
	}
	if (data->player.keys.d)
	{
		next_x += cos(data->player.direction + M_PI_2) * data->player.move_speed;
		next_y += sin(data->player.direction + M_PI_2) * data->player.move_speed;
	}

	// Détection avec un petit buffer de recul (0.1 case) pour ne pas traverser les coins
	buffer = (next_x > data->player.pos.x) ? 0.1 : -0.1;
	if (!is_wall(data, next_x + buffer, data->player.pos.y))
		data->player.pos.x = next_x;
	
	buffer = (next_y > data->player.pos.y) ? 0.1 : -0.1;
	if (!is_wall(data, data->player.pos.x, next_y + buffer))
		data->player.pos.y = next_y;

	if (data->player.keys.left)
	{
		data->player.direction -= 0.04f;
		if (data->player.direction < 0)
			data->player.direction += 2 * M_PI;
	}
	if (data->player.keys.right)
	{
		data->player.direction += 0.04f;
		if (data->player.direction >= 2 * M_PI)
			data->player.direction -= 2 * M_PI;
	}
}
