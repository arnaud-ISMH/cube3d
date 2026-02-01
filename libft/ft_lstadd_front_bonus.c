/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 00:20:13 by adeflers          #+#    #+#             */
/*   Updated: 2025/05/06 05:12:15 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new_elem)
{
	new_elem->next = *lst;
	*lst = new_elem;
}
/*
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

int	main()
{
	t_list	*lst;
	t_list	*add_front;
	int	test;
	int	test2;

	printf("&test1 : %p | &test2 : %p\n", &test, &test2);
	lst = ft_lstnew(&test);
	printf("BEFORE ADD :\n");
	printf("&t_liste : %p\n", lst);
	printf("&content : %p\n", lst->content);
	printf("&next : %p\n", lst->next);

	add_front = ft_lstnew(&test2);

	ft_lstadd_front_bonus(&lst, add_front);
	printf("AFTER ADD :\n");
	printf("&t_liste : %p\n", lst);
	printf("&content : %p\n", lst->content);
	printf("&next : %p\n", lst->next);
	printf("&next->content : %p\n", lst->next->content);
	printf("&next->next : %p\n", lst->next->next);

	free(lst->next);
	return (0);
}
*/
