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
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	if (data->map.grid)
		free(data->map.grid);
	if (data->parsing)
		free_parsing(data->parsing);
	free(data->mlx);
	free(data);
	exit (0);
}

int	load_texture(t_mlx_data *data, t_texture *texture, char *path)
{
	texture->img_ptr = mlx_xpm_file_to_image(data->mlx, path, &texture->width, &texture->height);
	if (!texture->img_ptr || texture->width <= 0 || texture->height <= 0)
		return (1);
	texture->img_data = mlx_get_data_addr(texture->img_ptr, &texture->bpp,
			&texture->size_line, &texture->endian);
	return (0);
}

int	init_textures(t_mlx_data *data)
{
	if (load_texture(data, &data->texture_north, data->parsing->no))
		return (1);
	if (load_texture(data, &data->texture_south, data->parsing->so))
		return (1);
	if (load_texture(data, &data->texture_east, data->parsing->ea))
		return (1);
	if (load_texture(data, &data->texture_west, data->parsing->we))
		return (1);
	if (load_texture(data, &data->monster.texture[0], data->parsing->t1))
		return (1);
	if (load_texture(data, &data->monster.texture[1], data->parsing->t2))
		return (1);

	/* if (load_texture(data, &data->texture_north, "textures/north.xpm")) //changer en data->parsing->no; */
	/* 	return (1); */
	/* if (load_texture(data, &data->texture_south, "textures/south.xpm"))//changer en data->parsing->so; */
	/* 	return (1); */
	/* if (load_texture(data, &data->texture_east, "textures/east.xpm"))//changer en data->parsing->ea; */
	/* 	return (1); */
	/* if (load_texture(data, &data->texture_west, "textures/west.xpm"))//changer en data->parsing->we; */
	/* 	return (1); */

	// 1. Chargement des murs avec les chemins récupérés par le parsing
	/* if (load_texture(data, &data->texture_north, data->parsing->no)) */
	/* 	return (1); */
	/* if (load_texture(data, &data->texture_south, data->parsing->so)) */
	/* 	return (1); */
	/* if (load_texture(data, &data->texture_west, data->parsing->we)) */
	/* 	return (1); */
	/* if (load_texture(data, &data->texture_east, data->parsing->ea)) */
	/* 	return (1); */

	// 2. Chargement de la texture du monstre (chemin en dur pour le moment ou data->parsing->t1)
	/* if (data->parsing->t1) */
	/* { */
	/* 	if (load_texture(data, &data->texture_monster, data->parsing->t1)) */
	/* 		return (1); */
	/* } */
    
    // ON UTILISE LES TEXTURES GLOBALEMENT DÉCLARÉES DANS DATA
    /* if (load_texture(data, &data->texture_monster, "textures/broly.xpm")) */
    /*     return (1); */

    return (0);
}

int	redraw(t_mlx_data *data)
{
	ft_bzero(data->img.img_data, WIN_H * data->img.size_line);
	draw_floor_ceiling(data, data->parsing->f, data->parsing->c);
	update_player_position(data);
	update_monster_position(data);
	draw_map(data);
	draw_player(data, 0xFFFF00);
	draw_minimap_borders(data);
	raycasting(data);
	draw_monster(data, 0xFF0000);
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
