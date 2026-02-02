/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:14:54 by adeflers          #+#    #+#             */
/*   Updated: 2026/02/01 00:14:54 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube3d.h"

int	close_win(t_mlx_data *data)
{
	mlx_destroy_image(data->mlx, data->img.img_ptr);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
	exit (0);
}

int	redraw(t_mlx_data *data)
{
	ft_bzero(data->img.img_data, WIN_H * data->img.size_line);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
	return (0);
}

t_mlx_data	minilibx_process(void)
{
	t_mlx_data	data;

	data.mlx = mlx_init();
	if (!data.mlx)
		exit (1);
	data.win = mlx_new_window(data.mlx, WIN_W, WIN_H, "cube3D");
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
