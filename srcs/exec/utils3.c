/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 17:53:49 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/15 17:53:49 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	moove_monster(t_mlx_data *data)
{
	int	i;

	i = 0;
	while (i < data->parsing->monster_count)
	{
		if ((int)data->player.pos.x % 10 < 5)
			data->monster[i].keys.w = true;
		else
			data->monster[i].keys.w = false;
		if ((int)data->player.pos.x % 10 >= 5)
			data->monster[i].keys.s = true;
		else
			data->monster[i].keys.s = false;
		if ((int)data->player.pos.y % 10 < 5)
			data->monster[i].keys.a = true;
		else
			data->monster[i].keys.a = false;
		if ((int)data->player.pos.y % 10 >= 5)
			data->monster[i].keys.d = true;
		else
			data->monster[i].keys.d = false;
		i++;
	}
}

int	key_press(int keysym, t_mlx_data *data)
{
	ft_printf("The %d key has been pressed\n\n", keysym);
	if (keysym == XK_Escape)
		close_win(data);
	if (keysym == XK_w)
		data->player.keys.w = true;
	if (keysym == XK_a)
		data->player.keys.a = true;
	if (keysym == XK_s)
		data->player.keys.s = true;
	if (keysym == XK_d)
		data->player.keys.d = true;
	if (keysym == XK_Left)
		data->player.keys.left = true;
	if (keysym == XK_Right)
		data->player.keys.right = true;
	moove_monster(data);
	if (keysym == XK_space)
		eat_monster(data);
	if (keysym == XK_e)
		open_door(data);
	return (0);
}

int	key_release(int keysym, t_mlx_data *data)
{
	ft_printf("The %d key has been release\n\n", keysym);
	if (keysym == XK_w)
		data->player.keys.w = false;
	if (keysym == XK_a)
		data->player.keys.a = false;
	if (keysym == XK_s)
		data->player.keys.s = false;
	if (keysym == XK_d)
		data->player.keys.d = false;
	if (keysym == XK_Left)
		data->player.keys.left = false;
	if (keysym == XK_Right)
		data->player.keys.right = false;
	return (0);
}

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((long long)tv.tv_sec * 1000) + ((long long)tv.tv_usec / 1000));
}
