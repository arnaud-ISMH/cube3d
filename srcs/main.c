/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 09:34:10 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/09 14:14:36 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	main(int ac, char **av)
{
	t_mlx_data	*data;

	if (ac != 2)
		return (1);
	data = malloc(sizeof(t_mlx_data));
	if (!data)
		return (1);
	*data = minilibx_process();
	data->parsing = check_args(ac, av);
	ft_printf("nb de portes : %d\nnb de monstres : %d\n", data->parsing->door_count, data->parsing->monster_count); // Debug
	init_player(data);
	if (init_monster(data))
		return (close_win(data), 1);
	int i = 0;
	while (i < data->parsing->monster_count)
	{
		ft_printf("monster pos : x = %f, y = %f\n", data->monster[i].pos.x, data->monster[i].pos.y); // Debug
		i++;
	}
	if (init_map(data))
		return (close_win(data), 1);
	if (init_textures(data))
		return (close_win(data), 1);
	mlx_hook(data->win, 17, 0, (int (*)())(void *)close_win, data);
	mlx_hook(data->win, 2, 1L<<0, (int (*)())(void *)key_press, data);
	mlx_hook(data->win, 3, 1L<<1, (int (*)())(void *)key_release, data);
	/* mlx_hook(data->win, 6, 1L<<6, (int (*)())(void *)mouse_move, data); */
	/* mlx_mouse_hide(data->mlx, data->win); */
	/* mlx_mouse_move(data->mlx, data->win, WIN_W / 2, WIN_H / 2); */
	mlx_loop_hook(data->mlx, (int (*)())(void *)redraw, data);
	mlx_loop(data->mlx);
	return (0);
}
