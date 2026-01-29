/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 01:40:05 by adeflers          #+#    #+#             */
/*   Updated: 2025/05/06 05:50:03 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}
/*
t_list  *ft_lstnew(void *content)
{
        t_list  *new_lst;

        new_lst = malloc(sizeof(t_list));
        if (!new_lst)
                return (NULL);
        new_lst->content = content;
        new_lst->next = NULL;
        return (new_lst);
}

int     main()
{
        t_list  *lst;
        t_list  *add_back;

	int	test;
        int     test2;

        printf("&test1 : %p | &test2 : %p\n", &test, &test2);
        lst = ft_lstnew(&test);
        printf("BEFORE ADD :\n");
        printf("&t_liste : %p\n", lst);
        printf("&content : %p\n", lst->content);
        printf("&next : %p\n", lst->next);

        add_back = ft_lstnew(&test2);

        ft_lstadd_back(&lst, add_back);
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
