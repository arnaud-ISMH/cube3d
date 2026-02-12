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
}

void	clamping(t_mlx_data *data)
{
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
	return (1);
}

void	youhou(t_mlx_data *data)
{
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
}

#include <math.h>

void raycasting(t_mlx_data *data)
{
    int rays = 500; // nombre de rayons
    float fov = M_PI / 2; // 60°
    float dir = 200; // direction joueur

    float start = dir - fov / 2;
    float step = fov / rays;

    for (int r = 0; r < rays; r++)
    {
       float angle = start + r * step;
        float dx = cos(angle);
        float dy = sin(angle);

        float x = data->square.origin.x;
        float y = data->square.origin.y;

        // avance pixel par pixel
        for (int i = 0; i < 300; i++)
        {
            x += dx;
            y += dy;

            if (x < data->bordures.origin.x || x > data->bordures.origin.x + data->bordures.large ||
                y < data->bordures.origin.y || y > data->bordures.origin.y + data->bordures.haut)
                break;

            put_pixel(&data->img, (int)x, (int)y, ORANGE);
        }
    }
}

/* void	raycasting(t_mlx_data *data) */
/* { */
/* 	int	i; */
/**/
/* 	i = 0; */
/* 	while (i + data->square.origin.y < data->bordures.haut + data->bordures.origin.y) */
/* 	{ */
/* 		put_pixel(&data->img, data->square.origin.x, data->square.origin.y + i, ORANGE); */
/* 		i++; */
/* 	} */
/**/
/* 	i = 0; */
/* 	while (i + data->square.origin.x < data->bordures.large + data->bordures.origin.x) */
/* 	{ */
/* 		put_pixel(&data->img, data->square.origin.x + i, data->square.origin.y, VERT); */
/* 		i++; */
/* 	} */
/**/
/* 	i = 0; */
/* 	while (data->square.origin.y - i > data->bordures.origin.y) */
/* 	{ */
/* 		put_pixel(&data->img, data->square.origin.x, data->square.origin.y - i, BLEU); */
/* 		i++; */
/* 	} */
/**/
/* 	i = 0; */
/* 	while (data->square.origin.x - i > data->bordures.origin.x) */
/* 	{ */
/* 		put_pixel(&data->img, data->square.origin.x - i, data->square.origin.y, ROUGE); */
/* 		i++; */
/* 	} */
/* } */

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
