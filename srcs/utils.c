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

#include "../includes/cube3d.h"

int	put_pixel(t_image *img, int x, int y, unsigned int color)
{
	int	offset;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return (0);
	offset = (y * img->size_line) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->img_data)) = color;
	return (1);
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
