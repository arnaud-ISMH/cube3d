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

#include "includes/cube3d.h"

int	main(int ac, char **av)
{
	t_mlx_data	*data;

	(void)av;
	(void)ac;
	data = malloc(sizeof(t_mlx_data));
	if (!data)
		return (1);
	*data = minilibx_process();
	data->count_frame = 0;
	init_square(data); // fun
	init_board(data); // fun
	init_obstacle1(data); // fun
	init_obstacle2(data); // fun
	/* draw_pixel_group(data); // fun */
	mlx_hook(data->win, 17, 0, close_win, data);
	mlx_hook(data->win, 2, 1, handle_input, data);
	mlx_loop_hook(data->mlx, redraw, data);
	mlx_loop(data->mlx);
	return (0);
}
