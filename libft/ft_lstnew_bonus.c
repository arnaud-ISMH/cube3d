/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 00:17:05 by adeflers          #+#    #+#             */
/*   Updated: 2025/05/06 05:12:34 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_lst;

	new_lst = malloc(sizeof(t_list));
	if (!new_lst)
		return (NULL);
	new_lst->content = content;
	new_lst->next = NULL;
	return (new_lst);
}
/*
int	main()
{
	t_list	*new;
	int	test = 10;

	new = ft_lstnew_bonus(&test);
	printf("%p\n", new->content);
	printf("%p\n", new->next);
	printf("%p\n",&test);
	free(new);
	return (0);
}
*/
