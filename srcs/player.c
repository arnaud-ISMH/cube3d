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
	data->player.pos.x = 1.5;
	data->player.pos.y = 5.5;
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

	// Conversion coordonnées virtuelles -> pixels écran pour le dessin
	int p_x = (int)(data->player.pos.x * data->map.scale);
	int p_y = (int)(data->player.pos.y * data->map.scale);

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
	if (next_x > data->player.pos.x)
		buffer = 0.1;
	else
		buffer = - 0.1;
	if (!is_wall(data, next_x + buffer, data->player.pos.y))
		data->player.pos.x = next_x;
	
	if (next_y > data->player.pos.y)
		buffer = 0.1;
	else
		buffer = - 0.1;
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

int	mouse_move(int x, int y, t_mlx_data *data)
{
	int		center_x;
	int		delta_x;
	double	sensitivity;

	(void)y; // On ignore l'axe Y pour l'instant (pas de regard haut/bas)
	
	center_x = WIN_W / 2;
	if (x == center_x)
		return (0);

	// Sensibilité de la souris (plus le chiffre est petit, plus la rotation est lente/précise)
	sensitivity = 0.002;

	// Calcul de la distance parcourue depuis le centre
	delta_x = x - center_x;

	data->player.direction += delta_x * sensitivity;

	if (data->player.direction < 0)
		data->player.direction += 2 * M_PI;
	else if (data->player.direction >= 2 * M_PI)
		data->player.direction -= 2 * M_PI;

	mlx_mouse_move(data->mlx, data->win, WIN_W / 2, WIN_H / 2);

	return (0);
}
