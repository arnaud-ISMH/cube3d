/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:05:47 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/11 13:03:09 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

void	printerr(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
}

void	free_parsing(t_parsing *parsing)
{
	if (!parsing)
		return ;
	free(parsing->no);
	free(parsing->so);
	free(parsing->we);
	free(parsing->ea);
	free(parsing->t1);
	free(parsing->t2);
	if (parsing->map.grid)
		freefree(parsing->map.grid);
	free(parsing->monster);
	free(parsing->door);
	free(parsing);
}

char	**freefree(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}


int	open_fd(char *arg)
{
	int	fd;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
	{
		printerr("Cannot open file\n");
		// free_parsing(parsing); //pr linstant pas besoin mais secu
		exit(1);		
	}
	return (fd);
}