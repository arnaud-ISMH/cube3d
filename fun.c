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

void	init_square(t_mlx_data *data)
{
	data->square.origin.x = (WIN_W - SIZE) / 2;
	data->square.origin.x_flag = 1;
	data->square.origin.y = (WIN_H - SIZE) / 2;
	data->square.origin.y_flag = 1;
	data->square.youhou_flag = -1;
	data->square.size = SIZE;
	data->square.color = COLOR;
	data->square.speed = SPEED;
}

void	clamping(t_mlx_data *data)
{
	if ((data->square.origin.x + data->square.size) >= WIN_W)
		data->square.origin.x = WIN_W - data->square.size - 1;
	if (data->square.origin.x < 0)
		data->square.origin.x = 0;
	if ((data->square.origin.y + data->square.size) >= WIN_H)
		data->square.origin.y = WIN_H - data->square.size - 1;
	if (data->square.origin.y < 0)
		data->square.origin.y = 0;
}

int	draw_pixel_group(t_mlx_data *data)
{
	int	i;
	int	j;

	i = 0;
	clamping(data);
	while (i < data->square.size)
	{
		j = 0;
		while (j < data->square.size)
		{
			put_pixel(&data->img, data->square.origin.x + i,
				data->square.origin.y + j, data->square.color);
			j++;
		}
		i++;
	}
	return (1);
}

void	youhou(t_mlx_data *data)
{
	if (data->square.origin.x == (WIN_W - data->square.size - 1)
			|| data->square.origin.x == 0)
		data->square.origin.x_flag*=-1;
	if (data->square.origin.y == (WIN_H - data->square.size - 1)
			|| data->square.origin.y == 0)
		data->square.origin.y_flag*=-1;
	if (data->square.origin.x_flag >= 0)
		data->square.origin.x+=(data->square.speed / 10);
	else 
		data->square.origin.x-=(data->square.speed / 10);
	if (data->square.origin.y_flag >= 0)
		data->square.origin.y+=(data->square.speed / 10);
	else
		data->square.origin.y-=(data->square.speed / 10);
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
		data->square.youhou_flag*=-1;

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
