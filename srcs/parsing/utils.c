/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:05:47 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/04 13:05:54 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

void	printerr(char *msg)
{
	write(2, msg, ft_strlen(msg));
}