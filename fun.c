/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:01:31 by adeflers          #+#    #+#             */
/*   Updated: 2026/02/01 00:01:31 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube3d.h"

void	init_obstacle1(t_mlx_data *data)
{
	data->obstacle1.origin.x = (WIN_W - SIZE) / 4;
	data->obstacle1.origin.x_flag = 1;
	data->obstacle1.origin.y = (WIN_H - SIZE) / 4;
	data->obstacle1.origin.y_flag = 1;
	data->obstacle1.youhou_flag = -1;
	data->obstacle1.haut = SIZE;
	data->obstacle1.large = SIZE;
	data->obstacle1.color = VERT;
	data->obstacle1.speed = SPEED;
	data->obstacle1.dir = 200;
	data->obstacle1.ray = 1;
}

void	init_obstacle2(t_mlx_data *data)
{
	data->obstacle2.origin.x = (WIN_W - SIZE) / 3;
	data->obstacle2.origin.x_flag = 1;
	data->obstacle2.origin.y = (WIN_H - SIZE) / 2;
	data->obstacle2.origin.y_flag = 1;
	data->obstacle2.youhou_flag = -1;
	data->obstacle2.haut = SIZE;
	data->obstacle2.large = SIZE;
	data->obstacle2.color = ROUGE;
	data->obstacle2.speed = SPEED;
	data->obstacle2.dir = 200;
	data->obstacle2.ray = 1;
}

void	init_board(t_mlx_data *data)
{
	data->bordures.origin.x = BORDURE_SIZE;
	data->bordures.origin.x_flag = 1;
	data->bordures.origin.y = BORDURE_SIZE;
	data->bordures.origin.y_flag = 1;
	data->bordures.youhou_flag = -1;
	data->bordures.large = WIN_W - (BORDURE_SIZE * 2) - 1;
	data->bordures.haut = WIN_H - (BORDURE_SIZE * 2) - 1;
	data->bordures.color = COLOR;
	data->bordures.speed = SPEED;
}

void	init_square(t_mlx_data *data)
{
	data->square.origin.x = (WIN_W - SIZE) / 2;
	data->square.origin.x_flag = 1;
	data->square.origin.y = (WIN_H - SIZE) / 2;
	data->square.origin.y_flag = 1;
	data->square.youhou_flag = -1;
	data->square.haut = SIZE;
	data->square.large = SIZE;
	data->square.color = COLOR;
	data->square.speed = SPEED;
	data->square.dir = 200;
	data->square.ray = 1;
}

void	clamping(t_mlx_data *data)
{
	// colisions avec les bordures
	if ((data->square.origin.x + data->square.large) >= data->bordures.origin.x + data->bordures.large)
		data->square.origin.x = data->bordures.origin.x + data->bordures.large - data->square.large - 1;
	if (data->square.origin.x < data->bordures.origin.x)
		data->square.origin.x = data->bordures.origin.x;
	if ((data->square.origin.y + data->square.haut) >= data->bordures.origin.y + data->bordures.haut)
		data->square.origin.y = data->bordures.origin.y + data->bordures.haut - data->square.haut - 1;
	if (data->square.origin.y < data->bordures.origin.y)
		data->square.origin.y = data->bordures.origin.y;
}

int	draw_pixel_group(t_mlx_data *data)
{
	int	i;
	int	j;

	// draw cube
	i = 0;
	clamping(data);
	while (i < data->square.large)
	{
		j = 0;
		while (j < data->square.haut)
		{
			put_pixel(&data->img, data->square.origin.x + i,
				data->square.origin.y + j, data->square.color);
			j++;
		}
		i++;
	}
	// draw bordures
	i = 0;
	while (i < data->bordures.large)
	{
		put_pixel(&data->img, data->bordures.origin.x + i,
			data->bordures.origin.y, data->bordures.color);
		put_pixel(&data->img, data->bordures.origin.x + i,
			data->bordures.origin.y + data->bordures.haut, data->bordures.color);
		j = 0;
		while (j < data->bordures.haut)
		{
			put_pixel(&data->img, data->bordures.origin.x,
				data->bordures.origin.y + j, data->bordures.color);
			put_pixel(&data->img, data->bordures.origin.x + data->bordures.large,
				data->bordures.origin.y + j, data->bordures.color);
			j++;
		}
		i++;
	}
	// draw obstacle 1
	i = 0;
	while (i < data->obstacle1.large)
	{
		j = 0;
		while (j < data->obstacle1.haut)
		{
			put_pixel(&data->img, data->obstacle1.origin.x + i,
				data->obstacle1.origin.y + j, data->obstacle1.color);
			j++;
		}
		i++;
	}
	// draw obstacle 2
	i = 0;
	while (i < data->obstacle2.large)
	{
		j = 0;
		while (j < data->obstacle2.haut)		{
			put_pixel(&data->img, data->obstacle2.origin.x + i,
				data->obstacle2.origin.y + j, data->obstacle2.color);
			j++;
		}
		i++;
	}
	return (0);
}

void	youhou(t_mlx_data *data)
{
	/* rebond du carre sur les bordures */
	if (data->square.origin.x == (data->bordures.origin.x + data->bordures.large - data->square.large - 1)
			|| data->square.origin.x == data->bordures.origin.x)
		data->square.origin.x_flag*=-1;
	if (data->square.origin.y == (data->bordures.origin.y + data->bordures.haut - data->square.haut - 1)
			|| data->square.origin.y == data->bordures.origin.y)
		data->square.origin.y_flag*=-1;
	if (data->square.origin.x_flag >= 0)
		data->square.origin.x+=(data->square.speed / 10);
	else 
		data->square.origin.x-=(data->square.speed / 10);
	if (data->square.origin.y_flag >= 0)
		data->square.origin.y+=(data->square.speed / 10);
	else
		data->square.origin.y-=(data->square.speed / 10);

	/* rebond du carre sur les obstacles */
	if ((data->square.origin.x + data->square.large) >= data->obstacle1.origin.x
			&& data->square.origin.x <= (data->obstacle1.origin.x + data->obstacle1.large)
			&& (data->square.origin.y + data->square.haut) >= data->obstacle1.origin.y
			&& data->square.origin.y <= (data->obstacle1.origin.y + data->obstacle1.haut))
		data->square.origin.x_flag*=-1;
	if ((data->square.origin.y + data->square.haut) >= data->obstacle1.origin.y
			&& data->square.origin.y <= (data->obstacle1.origin.y + data->obstacle1.haut)
			&& (data->square.origin.x + data->square.large) >= data->obstacle1.origin.x
			&& data->square.origin.x <= (data->obstacle1.origin.x + data->obstacle1.large))
		data->square.origin.y_flag*=-1;
	if ((data->square.origin.x + data->square.large) >= data->obstacle2.origin.x
			&& data->square.origin.x <= (data->obstacle2.origin.x + data->obstacle2.large)
			&& (data->square.origin.y + data->square.haut) >= data->obstacle2.origin.y
			&& data->square.origin.y <= (data->obstacle2.origin.y + data->obstacle2.haut))
		data->square.origin.x_flag*=-1;
	if ((data->square.origin.y + data->square.haut) >= data->obstacle2.origin.y
			&& data->square.origin.y <= (data->obstacle2.origin.y + data->obstacle2.haut)
			&& (data->square.origin.x + data->square.large) >= data->obstacle2.origin.x
			&& data->square.origin.x <= (data->obstacle2.origin.x + data->obstacle2.large))
		data->square.origin.y_flag*=-1;

}

void	raycasting(t_mlx_data *data)
{
	int		rays;
	int		i;
	float	fov;
	float	start;
	float	step;

	rays = 300;
	fov = M_PI / 2;
	start = data->square.dir - fov / 2;
	step = fov / rays;
	i = 0;
	while (i < rays)
	{
		float angle = start + i * step;
		float dx = cos(angle);
		float dy = sin(angle);
		float x = data->square.origin.x;
		float y = data->square.origin.y;

		int j = 0;
		while (j < WIN_W)
		{
			x+=dx;
			y+=dy;
			// colision des rayons avec les bordures
			if (x < data->bordures.origin.x || 
				x > data->bordures.origin.x + data->bordures.large ||
				y < data->bordures.origin.y ||
				y > data->bordures.origin.y + data->bordures.haut)
				break;
			// colision des rayons avec l'obstacle 1
			if (x >= data->obstacle1.origin.x && x <= data->obstacle1.origin.x + data->obstacle1.large &&
				y >= data->obstacle1.origin.y && y <= data->obstacle1.origin.y + data->obstacle1.haut)
				break;
			j++;
			// colision des rayons avec l'obstacle 2
			if (x >= data->obstacle2.origin.x && x <= data->obstacle2.origin.x + data->obstacle2.large &&
				y >= data->obstacle2.origin.y && y <= data->obstacle2.origin.y + data->obstacle2.haut)
				break;
			put_pixel(&data->img, (int)x, (int)y, ORANGE);
		}
		i++;
	}
}

void	handle_input_fun(int keysym, t_mlx_data *data)
{
	/* reinitialiser le carre */
	if (keysym == 32) // spacebar
		init_square(data);

	/* gerer la vitesse */
	if (keysym == XK_Tab)
		data->square.speed*= 1.5;
	if (keysym == XK_BackSpace)
		data->square.speed/= 1.5;

	/* youhou auto deplacement on/off */
	if (keysym == XK_Return)
	{
		data->square.youhou_flag*=-1;
		data->square.ray = -1;
	}

	/* raycast on/off */
	if (keysym == 114) // r
	{
		data->square.ray*=-1;
		/* data->square.youhou_flag = -1; */
	}

	/* change direction */
	if (keysym == 101)
		data->square.dir += 0.1;
	if (keysym == 113)
		data->square.dir -= 0.1;

	/* deplacement manuel */
	if (keysym == XK_Left)
	{
		data->square.origin.x-=data->square.speed;
		data->square.youhou_flag = -1;
	}
	if (keysym == XK_Right)
	{
		data->square.origin.x+=data->square.speed;
		data->square.youhou_flag = -1;
	}
	if (keysym == XK_Up)
	{
		data->square.origin.y-=data->square.speed;
		data->square.youhou_flag = -1;
	}
	if (keysym == XK_Down)
	{
		data->square.origin.y+=data->square.speed;
		data->square.youhou_flag = -1;
	}
}
