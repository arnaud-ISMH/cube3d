/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 01:14:56 by adeflers          #+#    #+#             */
/*   Updated: 2025/05/06 05:12:27 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
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

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

int	main()
{
	int	test;
	t_list	*lst;
	t_list	*add_front1 = ft_lstnew(&test);
	t_list	*add_front2 = ft_lstnew(&test);

	lst = ft_lstnew(&test);

	ft_lstadd_front(&lst, add_front1);
	ft_lstadd_front(&lst, add_front2);
	printf("%p\n", &lst);
	printf("%p\n", &lst->next);
	printf("%p\n", &lst->next->next);
	printf("%p\n", &lst->next->next->next);
	printf("%p\n", &lst->next->next->next->next);

	printf("\n>>%p\n", ft_lstlast_bonus(lst));

	return (0);
}
*/
