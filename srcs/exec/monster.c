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

int	init_monster(t_mlx_data *data)
{
	/* data->monster.pos.x = 25.5; */
	/* data->monster.pos.y = 9.5; */
	data->monster = malloc(sizeof(t_monster) * data->parsing->monster_count);
	if (!data->monster)
		return (1);
	int i = 0;
	while (i < data->parsing->monster_count)
	{
		data->monster[i].pos.x = data->parsing->monster[i].pos.x + 0.5;
		data->monster[i].pos.y = data->parsing->monster[i].pos.y + 0.5;
		data->monster[i].direction = 0.0f;
		data->monster[i].move_speed = 0.01; // Vitesse adaptée à la grille 1x1
		data->monster[i].keys.w = false;
		data->monster[i].keys.a = false;
		data->monster[i].keys.s = false;
		data->monster[i].keys.d = false;
		data->monster[i].keys.left = false;
		data->monster[i].keys.right = false;
		i++;
	}
	/* data->monster.texture = data->texture_monster; */
	return (0);
}

void	draw_monster(t_mlx_data *data, unsigned int color)
{
	int	monster_index = 0;
	while (monster_index < data->parsing->monster_count)
	{
		int	i;
		int	j;

		// Conversion coordonnées virtuelles -> pixels écran pour le dessin
		int p_x = (int)(data->monster[monster_index].pos.x * data->map.scale);
		int p_y = (int)(data->monster[monster_index].pos.y * data->map.scale);

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
		monster_index++;
	}
}

// Calcule la distance de Pythagore au carré (pas besoin de la racine carrée sqrt, 
// ça économise des calculs pour le processeur et ça suffit pour comparer qui est le plus loin)
void    calculate_monsters_distance(t_mlx_data *data)
{
    int i;

    i = 0;
    while (i < data->parsing->monster_count)
    {
        data->monster[i].distance = 
            ((data->player.pos.x - data->monster[i].pos.x) * (data->player.pos.x - data->monster[i].pos.x)) +
            ((data->player.pos.y - data->monster[i].pos.y) * (data->player.pos.y - data->monster[i].pos.y));
        i++;
    }
}

// Trie le tableau de monstres du plus loin (grande distance) au plus proche (petite distance)
void    sort_monsters(t_mlx_data *data)
{
    int         i;
    int         j;
    t_monster   tmp;

    calculate_monsters_distance(data);
    i = 0;
    while (i < data->parsing->monster_count - 1)
    {
        j = 0;
        while (j < data->parsing->monster_count - i - 1)
        {
            // Si le monstre actuel est PLUS PROCHE que le suivant, on les échange
            // pour pousser les monstres les plus LOINS au début du tableau
            if (data->monster[j].distance < data->monster[j + 1].distance)
            {
                tmp = data->monster[j];
                data->monster[j] = data->monster[j + 1];
                data->monster[j + 1] = tmp;
            }
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
        tex_y = ((d * monster->current_tex->height) / sprite_dim) / 256;
        if (tex_y < 0) tex_y = 0;

        // On pioche le pixel dans la texture du monstre
        tex_offset = (tex_y * monster->current_tex->size_line) + (tex_x * (monster->current_tex->bpp / 8));
        color = *(unsigned int *)(monster->current_tex->img_data + tex_offset);

        // TRÈS IMPORTANT : On ne dessine pas si la couleur est invisible (ex: noir 0x000000 ou une couleur transparente)
        // Et on vérifie le Z-BUFFER pour voir si le monstre n'est pas caché derrière un mur !
        if (color != 0x000000 && transform_y < data->z_buffer[stripe])
        {
            put_pixel(&data->img, stripe, y, color);
        }
        y++;
    }
}

void	animate_and_render_monsters(t_mlx_data *data)
{
	long long	current_time;
	t_texture	*current_tex;
	int			i = 0;

	sort_monsters(data); // Trier les monstres du plus loin au plus proche pour le rendu (painter's algorithm)

	while (i < data->parsing->monster_count)
	{
		// 1. On prend "l'heure" actuelle en millisecondes
		current_time = get_time_in_ms();

		// 2. On divise le temps par 300 (la vitesse de l'anim) 
		// et on fait "% 2" pour obtenir soit 0, soit 1.
		if ((current_time / 300) % 2 == 0)
			current_tex = &data->monster[i].texture[0];
		else
			current_tex = &data->monster[i].texture[1];

		// 3. On applique cette texture à nos monstres avant de les dessiner
		/* int			i; */
		/* i = 0; */
		/* while (i < data->nb_monsters) */
		/* { */
		/* 	data->monster[i].texture = current_tex; */
		/* 	render_single_monster(data, &data->monster[i]); */
		/* 	i++; */
		/* } */
		data->monster[i].current_tex = current_tex;
		render_single_monster(data, &data->monster[i]);
		i++;
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
        int tex_x = (int)(256 * (stripe - (-sprite_dim / 2 + sprite_screen_x)) * monster->current_tex->width / sprite_dim) / 256;
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
	int i = 0;

	while (i < data->parsing->monster_count)
	{
		next_x = data->monster[i].pos.x;
		next_y = data->monster[i].pos.y;
		if (data->monster[i].keys.w)
		{
			next_x += cos(data->monster[i].direction) * data->monster[i].move_speed;
			next_y += sin(data->monster[i].direction) * data->monster[i].move_speed;
		}
		if (data->monster[i].keys.s)
		{
			next_x -= cos(data->monster[i].direction) * data->monster[i].move_speed;
			next_y -= sin(data->monster[i].direction) * data->monster[i].move_speed;
		}
		if (data->monster[i].keys.a)
		{
			next_x += cos(data->monster[i].direction - M_PI_2) * data->monster[i].move_speed;
			next_y += sin(data->monster[i].direction - M_PI_2) * data->monster[i].move_speed;
		}
		if (data->monster[i].keys.d)
		{
			next_x += cos(data->monster[i].direction + M_PI_2) * data->monster[i].move_speed;
			next_y += sin(data->monster[i].direction + M_PI_2) * data->monster[i].move_speed;
		}

		// Détection avec un petit buffer de recul (0.5 case) pour ne pas traverser les coins
		if (next_x > data->monster[i].pos.x)
			buffer = 0.5;
		else
			buffer = - 0.5;
		if (!is_wall(data, next_x + buffer, data->monster[i].pos.y))
			data->monster[i].pos.x = next_x;
		
		if (next_y > data->monster[i].pos.y)
			buffer = 0.5;
		else
			buffer = - 0.5;
		if (!is_wall(data, data->monster[i].pos.x, next_y + buffer))
			data->monster[i].pos.y = next_y;

		if (data->monster[i].keys.left)
		{
			data->monster[i].direction -= 0.04f;
			if (data->monster[i].direction < 0)
				data->monster[i].direction += 2 * M_PI;
		}
		if (data->monster[i].keys.right)
		{
			data->monster[i].direction += 0.04f;
			if (data->monster[i].direction >= 2 * M_PI)
				data->monster[i].direction -= 2 * M_PI;
		}
		i++;
	}
}
