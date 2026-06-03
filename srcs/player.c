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
	data->player.pos.x = WIN_W / 4;
	data->player.pos.y = WIN_H / 4;
	data->player.direction = 0.0f;
	data->player.move_speed = 2;
	data->player.keys.w = false;
	data->player.keys.a = false;
	data->player.keys.s = false;
	data->player.keys.d = false;
	data->player.keys.left = false;
	data->player.keys.right = false;
}

int	is_wall(t_mlx_data *data, int next_x, int next_y)
{
	int	scale;
	int	map_x;
	int	map_y;

	// On recalcule le scale exact comme dans ton draw_map.c
	if (data->map.width > data->map.height)
		scale = (WIN_W / 2 / data->map.width);
	else
		scale = (WIN_H / data->map.height);
	
	// Si le scale bug ou vaut 0, sécurité
	if (scale <= 0)
		return (1);

	// Conversion magique : Pixels écran -> Index de ton tableau char**
	map_x = next_x / scale;
	map_y = next_y / scale;

	// Sécurité pour ne pas segfault hors des limites de ta matrice
	/* if (map_y < 0 || map_y >= data->map_height || map_x < 0 || map_x >= data->map_width) */
	/* 	return (1); */

	// On vérifie le caractère dans ta grille
	if (data->map.grid[map_y][map_x] == '1')
		return (1); // C'est un mur !

	return (0); // Zone libre
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
			put_pixel(&data->img, data->player.pos.x + i, data->player.pos.y + j, color);
			j++;
		}
		i++;
	}
	k = 0;
	while (k <= 15)
	{
		put_pixel(&data->img, data->player.pos.x + (int)(cos(data->player.direction) * k),
			data->player.pos.y + (int)(sin(data->player.direction) * k), 0xFF0000);
		k++;
	}
}

/* void	update_player_position(t_mlx_data *data) */
/* { */
/* 	if (data->player.keys.w) */
/* 	{ */
/* 		data->player.pos.x += (int)(cos(data->player.direction) * data->player.move_speed); */
/* 		data->player.pos.y += (int)(sin(data->player.direction) * data->player.move_speed); */
/* 	} */
/* 	if (data->player.keys.s) */
/* 	{ */
/* 		data->player.pos.x -= (int)(cos(data->player.direction) * data->player.move_speed); */
/* 		data->player.pos.y -= (int)(sin(data->player.direction) * data->player.move_speed); */
/* 	} */
/* 	if (data->player.keys.a) */
/* 	{ */
/* 		data->player.pos.x += (int)(cos(data->player.direction - M_PI_2) * data->player.move_speed); */
/* 		data->player.pos.y += (int)(sin(data->player.direction - M_PI_2) * data->player.move_speed); */
/* 	} */
/* 	if (data->player.keys.d) */
/* 	{ */
/* 		data->player.pos.x += (int)(cos(data->player.direction + M_PI_2) * data->player.move_speed); */
/* 		data->player.pos.y += (int)(sin(data->player.direction + M_PI_2) * data->player.move_speed); */
/* 	} */
/* 	if (data->player.keys.left) */
/* 	{ */
/* 		data->player.direction -= 0.05f; */
/* 		if (data->player.direction < 0) */
/* 			data->player.direction += 2 * M_PI; */
/* 	} */
/* 	if (data->player.keys.right) */
/* 	{ */
/* 		data->player.direction += 0.05f; */
/* 		if (data->player.direction >= 2 * M_PI) */
/* 			data->player.direction -= 2 * M_PI; */
/* 	} */
/* } */

void	update_player_position(t_mlx_data *data)
{
	int	next_x;
	int	next_y;

	next_x = data->player.pos.x;
	next_y = data->player.pos.y;

	// 1. Calcul de la position potentielle selon les touches
	if (data->player.keys.w)
	{
		next_x += (int)(cos(data->player.direction) * data->player.move_speed);
		next_y += (int)(sin(data->player.direction) * data->player.move_speed);
	}
	if (data->player.keys.s)
	{
		next_x -= (int)(cos(data->player.direction) * data->player.move_speed);
		next_y -= (int)(sin(data->player.direction) * data->player.move_speed);
	}
	if (data->player.keys.a)
	{
		next_x += (int)(cos(data->player.direction - M_PI_2) * data->player.move_speed);
		next_y += (int)(sin(data->player.direction - M_PI_2) * data->player.move_speed);
	}
	if (data->player.keys.d)
	{
		next_x += (int)(cos(data->player.direction + M_PI_2) * data->player.move_speed);
		next_y += (int)(sin(data->player.direction + M_PI_2) * data->player.move_speed);
	}

	// 2. Application des collisions avec glissement (Axe par Axe)
	// On vérifie si bouger uniquement sur X est valide
	if (!is_wall(data, next_x, data->player.pos.y))
		data->player.pos.x = next_x;

	// On vérifie si bouger uniquement sur Y est valide
	if (!is_wall(data, data->player.pos.x, next_y))
		data->player.pos.y = next_y;

	// 3. Gestion de la rotation
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
