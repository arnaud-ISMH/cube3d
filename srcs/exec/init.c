/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:14:54 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/08 16:45:32 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	load_texture(t_mlx_data *data, t_texture *texture, char *path)
{
	texture->img_ptr = mlx_xpm_file_to_image(data->mlx, path, &texture->width,
			&texture->height);
	if (!texture->img_ptr || texture->width <= 0 || texture->height <= 0)
		return (1);
	texture->img_data = mlx_get_data_addr(texture->img_ptr, &texture->bpp,
			&texture->size_line, &texture->endian);
	return (0);
}

int	init_textures(t_mlx_data *data)
{
	int	i;

	if (load_texture(data, &data->texture_north, data->parsing->no))
		return (1);
	if (load_texture(data, &data->texture_south, data->parsing->so))
		return (1);
	if (load_texture(data, &data->texture_east, data->parsing->ea))
		return (1);
	if (load_texture(data, &data->texture_west, data->parsing->we))
		return (1);
	i = 0;
	while (i < data->parsing->monster_count)
	{
		if (load_texture(data, &data->monster[i].texture[0], data->parsing->t1))
			return (1);
		if (load_texture(data, &data->monster[i].texture[1], data->parsing->t2))
			return (1);
		i++;
	}
	if (load_texture(data, &data->texture_door, "textures/door.xpm"))
		return (1);
	return (0);
}

void	display_score(t_mlx_data *data)
{
	char	*score_str;
	char	*count_str;

	score_str = ft_itoa(data->score);
	count_str = ft_itoa(data->parsing->monster_count);
	mlx_string_put(data->mlx, data->win, WIN_W - 150, 50, 0xFFFFFF, "Score: ");
	mlx_string_put(data->mlx, data->win, WIN_W - 80, 50, 0xFFFFFF, score_str);
	free(score_str);
	mlx_string_put(data->mlx, data->win, WIN_W - 60, 50, 0xFFFFFF, "/");
	mlx_string_put(data->mlx, data->win, WIN_W - 40, 50, 0xFFFFFF, count_str);
	free(count_str);
	if (data->parsing->monster_count > 0
		&& data->score == data->parsing->monster_count)
		mlx_string_put(data->mlx, data->win, WIN_W - 100, 70,
			0x00FF00, "YOU WIN!");
}

int	redraw(t_mlx_data *data)
{
	char	*score_str;
	char	*count_str;

	score_str = ft_itoa(data->score);
	if (!score_str)
		return (1);
	count_str = ft_itoa(data->parsing->monster_count);
	if (!count_str)
		return (free(score_str), 1);
	ft_bzero(data->img.img_data, WIN_H * data->img.size_line);
	draw_floor_ceiling(data, data->parsing->f, data->parsing->c);
	update_player_position(data);
	update_monster_position(data);
	draw_map(data);
	draw_player(data, 0xFFFF00);
	draw_minimap_borders(data);
	raycasting(data);
	draw_monster(data, 0xFF0000);
	eat_animation(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
	display_score(data);
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
