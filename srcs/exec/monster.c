/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:46:20 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/08 16:46:20 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	init_monster(t_mlx_data *data)
{
	data->monster.pos.x = 5.5;
	data->monster.pos.y = 9.5;
	data->monster.direction = 0.0f;
	data->monster.move_speed = 0.02; // Vitesse adaptée à la grille 1x1
	data->monster.keys.w = false;
	data->monster.keys.a = false;
	data->monster.keys.s = false;
	data->monster.keys.d = false;
	data->monster.keys.left = false;
	data->monster.keys.right = false;
	data->monster.texture = &data->texture_monster;
}

void	draw_monster(t_mlx_data *data, unsigned int color)
{
	int	i;
	int	j;

	// Conversion coordonnées virtuelles -> pixels écran pour le dessin
	int p_x = (int)(data->monster.pos.x * data->map.scale);
	int p_y = (int)(data->monster.pos.y * data->map.scale);

	i = -3;
	while (i <= 3)
	{
		j = -3;
		while (j <= 3)
		{
			put_pixel(&data->img, p_x + i, p_y + j, color);
			j++;
		}
		i++;
	}
}

void    draw_monster_stripe(t_mlx_data *data, t_monster *monster, int stripe, int tex_x, double transform_y, int sprite_dim, int draw_start_y, int draw_end_y)
{
    int y;
    int tex_y;
    int d;
    unsigned int color;
    int tex_offset;

    y = draw_start_y;
    while (y < draw_end_y)
    {
        // Ne pas dessiner par-dessus la minimap
        if (stripe <= WIN_W / 4 && y <= WIN_H / 4)
        {
            y++;
            continue ;
        }

        // Règle de trois pour trouver le pixel Y sur la texture du monstre
        d = (y) * 256 - WIN_H * 128 + sprite_dim * 128;
        tex_y = ((d * monster->texture->height) / sprite_dim) / 256;
        if (tex_y < 0) tex_y = 0;

        // On pioche le pixel dans la texture du monstre
        tex_offset = (tex_y * monster->texture->size_line) + (tex_x * (monster->texture->bpp / 8));
        color = *(unsigned int *)(monster->texture->img_data + tex_offset);

        // TRÈS IMPORTANT : On ne dessine pas si la couleur est invisible (ex: noir 0x000000 ou une couleur transparente)
        // Et on vérifie le Z-BUFFER pour voir si le monstre n'est pas caché derrière un mur !
        if (color != 0x000000 && transform_y < data->z_buffer[stripe])
        {
            put_pixel(&data->img, stripe, y, color);
        }
        y++;
    }
}

void    render_single_monster(t_mlx_data *data, t_monster *monster)
{
    // 1. Calcul de la position relative du monstre par rapport au joueur
    double sprite_x = monster->pos.x - data->player.pos.x;
    double sprite_y = monster->pos.y - data->player.pos.y;

    // Récupération des vecteurs de la caméra (les mêmes que dans ton raycasting)
    double dir_x = cos(data->player.direction);
    double dir_y = sin(data->player.direction);
    double plane_x = -dir_y * 0.66;
    double plane_y = dir_x * 0.66;

    // Formule d'inversion de matrice pour projeter le monstre dans l'espace caméra
    double inv_det = 1.0 / (plane_x * dir_y - dir_x * plane_y);
    double transform_x = inv_det * (dir_y * sprite_x - dir_x * sprite_y);
    double transform_y = inv_det * (-plane_y * sprite_x + plane_x * sprite_y); // C'est la profondeur (distance)

    // Si le monstre est derrière le joueur, on ne calcul pas pour rien
    if (transform_y <= 0.1)
        return ;

    // 2. Calcul du centre horizontal du monstre sur l'écran (en pixels)
    int sprite_screen_x = (int)((WIN_W / 2) * (1 + transform_x / transform_y));

    // 3. Calcul de la taille du monstre à l'écran (hauteur et largeur, supposé carré)
    int sprite_dim = abs((int)(WIN_H / transform_y));

    // Calcul des pixels limites pour le dessin vertical
    int draw_start_y = -sprite_dim / 2 + WIN_H / 2;
    if (draw_start_y < 0) draw_start_y = 0;
    int draw_end_y = sprite_dim / 2 + WIN_H / 2;
    if (draw_end_y >= WIN_H) draw_end_y = WIN_H - 1;

    // Calcul des pixels limites pour le dessin horizontal
    int draw_start_x = -sprite_dim / 2 + sprite_screen_x;
    if (draw_start_x < 0) draw_start_x = 0;
    int draw_end_x = sprite_dim / 2 + sprite_screen_x;
    if (draw_end_x >= WIN_W) draw_end_x = WIN_W - 1;

    // 4. Boucle sur chaque colonne verticale (stripe) du monstre à l'écran
    int stripe = draw_start_x;
    while (stripe < draw_end_x)
    {
        // Règle de trois pour trouver la colonne X correspondante sur la texture
        int tex_x = (int)(256 * (stripe - (-sprite_dim / 2 + sprite_screen_x)) * monster->texture->width / sprite_dim) / 256;
        if (tex_x < 0) tex_x = 0;

        // On dessine la ligne verticale si le monstre est devant le mur
        if (transform_y > 0 && stripe >= 0 && stripe < WIN_W)
        {
            draw_monster_stripe(data, monster, stripe, tex_x, transform_y, sprite_dim, draw_start_y, draw_end_y);
        }
        stripe++;
    }
}

void	update_monster_position(t_mlx_data *data)
{
	double	next_x;
	double	next_y;
	double	buffer;

	next_x = data->monster.pos.x;
	next_y = data->monster.pos.y;
	if (data->monster.keys.w)
	{
		next_x += cos(data->monster.direction) * data->monster.move_speed;
		next_y += sin(data->monster.direction) * data->monster.move_speed;
	}
	if (data->monster.keys.s)
	{
		next_x -= cos(data->monster.direction) * data->monster.move_speed;
		next_y -= sin(data->monster.direction) * data->monster.move_speed;
	}
	if (data->monster.keys.a)
	{
		next_x += cos(data->monster.direction - M_PI_2) * data->monster.move_speed;
		next_y += sin(data->monster.direction - M_PI_2) * data->monster.move_speed;
	}
	if (data->monster.keys.d)
	{
		next_x += cos(data->monster.direction + M_PI_2) * data->monster.move_speed;
		next_y += sin(data->monster.direction + M_PI_2) * data->monster.move_speed;
	}

	// Détection avec un petit buffer de recul (0.1 case) pour ne pas traverser les coins
	if (next_x > data->monster.pos.x)
		buffer = 0.1;
	else
		buffer = - 0.1;
	if (!is_wall(data, next_x + buffer, data->monster.pos.y))
		data->monster.pos.x = next_x;
	
	if (next_y > data->monster.pos.y)
		buffer = 0.1;
	else
		buffer = - 0.1;
	if (!is_wall(data, data->monster.pos.x, next_y + buffer))
		data->monster.pos.y = next_y;

	if (data->monster.keys.left)
	{
		data->monster.direction -= 0.04f;
		if (data->monster.direction < 0)
			data->monster.direction += 2 * M_PI;
	}
	if (data->monster.keys.right)
	{
		data->monster.direction += 0.04f;
		if (data->monster.direction >= 2 * M_PI)
			data->monster.direction -= 2 * M_PI;
	}
}


