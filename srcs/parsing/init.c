/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:13:08 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/11 15:51:03 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

t_parsing	*init_parsing(void)
{
	t_parsing	*parsing;

	parsing = malloc(sizeof(t_parsing));
	if (!parsing)
		return (NULL);
	parsing->no = NULL;
	parsing->so = NULL;
	parsing->we = NULL;
	parsing->ea = NULL;
	parsing->f = -1;
	parsing->c = -1;
	parsing->map.grid = NULL;
	parsing->map.width = 0;
	parsing->map.height = 0;
	parsing->door = NULL;
	parsing->door_count = 0;
	parsing->monster = NULL;
	parsing->monster_count = 0;
	return (parsing);
}

t_parsing	*check_args(int ac, char **av)
{
	int			ext;
	t_parsing	*parsing;

	ext = ft_strlen(av[1]) - 4;
	if (ac != 2 || ft_strncmp(av[1] + ext, ".cub", 4) != 0
		|| access(av[1], R_OK) == -1)
	{
		printerr("Bad argument\n");
		exit(1);
	}
	parsing = init_parsing();
	if (!read_file(av[1], parsing))
		exit(1);
	return (parsing);
}
