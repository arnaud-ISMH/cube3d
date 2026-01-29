/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 09:34:10 by adeflers          #+#    #+#             */
/*   Updated: 2026/01/29 09:34:10 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	close_win(t_mlx_data *data)
{
	mlx_destroy_image(data->mlx, data->img.img_ptr);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
	exit (0);
}

void	clamping(t_mlx_data *data)
{
	if ((data->point.x + data->cube_size) >= WIN_W)
		data->point.x = WIN_W - data->cube_size - 1;
	if (data->point.x < 0)
		data->point.x = 0;
	if ((data->point.y + data->cube_size) >= WIN_H)
		data->point.y = WIN_H - data->cube_size - 1;
	if (data->point.y < 0)
		data->point.y = 0;
}

int	draw_pixel_group(t_mlx_data *data)
{
	int	i;
	int	j;

	ft_bzero(data->img.img_data, WIN_H * data->img.size_line);
	i = 0;
	clamping(data);
	while (i < data->cube_size)
	{
		j = 0;
		while (j < data->cube_size)
		{
			put_pixel(&data->img, data->point.x + i, data->point.y + j, 0xFFFFFF);
			j++;
		}
		i++;
	}
	return (1);
}

void	youhou(t_mlx_data *data)
{
	float	speed;

	speed = 1.5;
	draw_pixel_group(data);
	if (data->point.x == (WIN_W - data->cube_size - 1) || data->point.x == 0)
	{
		data->point.x_flag*=-1;
		data->point.x+=(data->point.x_flag * (speed + 1));
	}
	if (data->point.y == (WIN_H - data->cube_size - 1) || data->point.y == 0)
	{
		data->point.y_flag*=-1;
		data->point.y+=(data->point.y_flag * (speed + 1));
	}
	if (data->point.x_flag >= 0)
		data->point.x+=speed;
	else 
		data->point.x-=speed;
	if (data->point.y_flag >= 0)
		data->point.y+=speed;
	else
		data->point.y-=speed;
	printf("x : %f\n", data->point.x);
	printf("x_flag : %d\n", data->point.x_flag);
	printf("y : %f\n", data->point.y);
	printf("y_flag : %d\n", data->point.y_flag);
}

int	redraw(t_mlx_data *data)
{
	/* ft_bzero(data->img.img_data, WIN_H * data->img.size_line); */
	if (data->youhou_flag > 0)
		youhou(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
	return (0);
}

t_mlx_data	minilibx_process(void)
{
	t_mlx_data	data;

	data.mlx = mlx_init();
	if (!data.mlx)
		exit (1);
	data.win = mlx_new_window(data.mlx, WIN_W, WIN_H, "cube3d");
	if (!data.win)
	{
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		exit (1);
	}
	data.img.img_ptr = mlx_new_image(data.mlx, WIN_W, WIN_H);
	if (!data.img.img_ptr)
	{
		mlx_destroy_window(data.mlx, data.win);
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		exit (1);
	}
	data.img.img_data = mlx_get_data_addr(data.img.img_ptr, &data.img.bpp,
			&data.img.size_line, &data.img.endian);
	return (data);
}

int	handle_input(int keysym, t_mlx_data *data)
{
	ft_printf("The %d key has been pressed\n\n", keysym);
	if (keysym == XK_Return)
		data->youhou_flag*=-1;
	if (keysym == XK_Left)
	{
		data->point.x-=10;
		data->youhou_flag = -1;
		draw_pixel_group(data);
	}
	if (keysym == XK_Right)
	{
		data->point.x+=10;
		clamping(data);
		data->youhou_flag = -1;
		draw_pixel_group(data);
	}
	if (keysym == XK_Up)
	{
		data->point.y-=10;
		data->youhou_flag = -1;
		draw_pixel_group(data);
	}
	if (keysym == XK_Down)
	{
		data->point.y+=10;
		clamping(data);
		data->youhou_flag = -1;
		draw_pixel_group(data);
	}
	if (keysym == XK_Escape)
		close_win(data);
	return (0);
}

int	put_pixel(t_image *img, int x, int y, unsigned int color)
{
	int	offset;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return (0);
	offset = (y * img->size_line) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->img_data)) = color;
	return (1);
}


int	main(int ac, char **av)
{
	t_mlx_data	*data;

	(void)av;
	if (ac != 2)
		return (1);
	data = malloc(sizeof(t_mlx_data));
	if (!data)
		return (1);
	*data = minilibx_process();
	data->point.x = 0;
	data->point.x_flag = 1;
	data->point.y = 0;
	data->point.y_flag = 1;
	data->youhou_flag = -1;
	data->cube_size = 90;
	mlx_hook(data->win, 17, 0, close_win, data);
	mlx_hook(data->win, 2, 1, handle_input, data);
	mlx_loop_hook(data->mlx, redraw, data);
	mlx_loop(data->mlx);
	return (0);
}
