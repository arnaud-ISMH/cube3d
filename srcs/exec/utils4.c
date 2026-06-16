/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 15:23:26 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/16 15:23:26 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	mlx_mouse_hide_clean(t_mlx_data *data)
{
	Display	*display;
	Window	window;

	display = *(Display **)data->mlx;
	window = *(Window *)data->win;
	XFixesHideCursor(display, window);
	XFlush(display);
}

void	mlx_mouse_show_clean(t_mlx_data *data)
{
	Display	*display;
	Window	window;

	display = *(Display **)data->mlx;
	window = *(Window *)data->win;
	XFixesShowCursor(display, window);
	XFlush(display);
}
