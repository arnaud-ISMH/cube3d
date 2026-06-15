/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:13:52 by adeflers          #+#    #+#             */
/*   Updated: 2026/02/01 00:13:52 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	put_pixel(t_image *img, int x, int y, unsigned int color)
{
	int	offset;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return (0);
	offset = (y * img->size_line) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->img_data)) = color;
	return (1);
}

void    trigger_eat_effect(t_mlx_data *data)
{
    data->flash_start_time = get_time_in_ms();
    data->is_flashing = true;
}

void    eat_animation(t_mlx_data *data)
{
    long long current_time = get_time_in_ms();
    long long elapsed = current_time - data->flash_start_time;

    if (!data->is_flashing)
        return ;
    if (elapsed >= 200)
    {
        data->is_flashing = false;
        return ;
    }
    if ((elapsed >= 0 && elapsed < 50) || (elapsed >= 100 && elapsed < 150))
    {
        int i = 0;
        while (i < WIN_W)
        {
            int j = 0;
            while (j < WIN_H)
            {
                if (!(i <= WIN_W / 4 && j <= WIN_H / 4))
                    put_pixel(&data->img, i, j, 0xFF0000);
                j++;
            }
            i++;
        }
    }
}

int eat_monster(t_mlx_data *data)
{
	int i = 0;
	while (i < data->parsing->monster_count)
	{
		if (data->monster[i].is_alive)
		{
			double distance = sqrt(pow(data->player.pos.x - data->monster[i].pos.x, 2) + pow(data->player.pos.y - data->monster[i].pos.y, 2));
			if (distance < 1.0) // Si le monstre est à moins d'une case du joueur
			{
				data->monster[i].is_alive = false; // Le monstre est "mangé"
				ft_printf("Monster at (%.2f, %.2f) has been eaten!\n", data->monster[i].pos.x, data->monster[i].pos.y);
				trigger_eat_effect(data); // Déclencher l'effet de flash si le monstre est mangé
				return (1); // On arrête après avoir mangé un monstre
			}
		}
		i++;
	}
    int radius = 10;
    int center_x = (int)(data->player.pos.x * data->map.scale);
    int center_y = (int)(data->player.pos.y * data->map.scale);
    for (int angle = 0; angle < 360; angle += 5)
    {
        int x = center_x + (int)(radius * cos(angle * M_PI / 180.0));
        int y = center_y + (int)(radius * sin(angle * M_PI / 180.0));
        put_pixel(&data->img, x, y, 0xFF0000);
    }


	return (0); // Aucun monstre mangé
}

int	key_press(int keysym, t_mlx_data *data)
{
	ft_printf("The %d key has been pressed\n\n", keysym); // Debug
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
	int i = 0;
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
	if (keysym == XK_space)
	{
		eat_monster(data);
	}
	return (0);
}

int	key_release(int keysym, t_mlx_data *data)
{
	ft_printf("The %d key has been release\n\n", keysym); // Debug
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
	// (secondes * 1000) + (microsecondes / 1000)
	return (((long long)tv.tv_sec * 1000) + ((long long)tv.tv_usec / 1000));
}
