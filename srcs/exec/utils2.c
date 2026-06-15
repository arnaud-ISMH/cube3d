/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:17:24 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/15 16:17:24 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	free_monster_tex(t_mlx_data *data)
{
	int	i;

	i = 0;
	while (i < data->parsing->monster_count)
	{
		if (data->monster[i].texture[0].img_ptr)
			mlx_destroy_image(data->mlx, data->monster[i].texture[0].img_ptr);
		if (data->monster[i].texture[1].img_ptr)
			mlx_destroy_image(data->mlx, data->monster[i].texture[1].img_ptr);
		i++;
	}
}

int	close_win(t_mlx_data *data)
{
	mlx_destroy_image(data->mlx, data->img.img_ptr);
	if (data->texture_north.img_ptr)
		mlx_destroy_image(data->mlx, data->texture_north.img_ptr);
	if (data->texture_south.img_ptr)
		mlx_destroy_image(data->mlx, data->texture_south.img_ptr);
	if (data->texture_east.img_ptr)
		mlx_destroy_image(data->mlx, data->texture_east.img_ptr);
	if (data->texture_west.img_ptr)
		mlx_destroy_image(data->mlx, data->texture_west.img_ptr);
	if (data->texture_door.img_ptr)
		mlx_destroy_image(data->mlx, data->texture_door.img_ptr);
	free_monster_tex(data);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	if (data->monster)
		free(data->monster);
	if (data->parsing)
		free_parsing(data->parsing);
	free(data->mlx);
	free(data);
	exit (0);
}

int	mouse_move(int x, int y, t_mlx_data *data)
{
	int		center_x;
	int		delta_x;
	double	sensitivity;

	(void)y;
	center_x = WIN_W / 2;
	if (x == center_x)
		return (0);
	sensitivity = 0.002;
	delta_x = x - center_x;
	data->player.dir += delta_x * sensitivity;
	if (data->player.dir < 0)
		data->player.dir += 2 * M_PI;
	else if (data->player.dir >= 2 * M_PI)
		data->player.dir -= 2 * M_PI;
	mlx_mouse_move(data->mlx, data->win, WIN_W / 2, WIN_H / 2);
	return (0);
}

int	is_wall(t_mlx_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= data->map.height || map_x < 0
		|| map_x >= data->map.width)
		return (1);
	if (data->map.grid[map_y][map_x] == '1')
		return (1);
	return (0);
}
