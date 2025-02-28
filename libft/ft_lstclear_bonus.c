/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:54:11 by mbousset          #+#    #+#             */
/*   Updated: 2024/11/04 10:37:00 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lst_node;
	t_list	*temp_node;

	if (!lst || !del || !*lst)
		return ;
	lst_node = *lst;
	while (lst_node)
	{
		temp_node = lst_node;
		del(lst_node->content);
		lst_node = lst_node->next;
		free(temp_node);
	}
	*lst = NULL;
}

/*
#include <stdio.h>
void	print_list(t_list *lst)
{
	while (lst)
	{
		printf(" %s  ->  ", (char *)lst->content);
		lst = lst -> next;
	}
	printf("NULL\n");
}
void del(void *x)
{
	free(x);
}
int	main(int ac , char **av)
{
	int i = 1;
	t_list	*head = NULL;
	t_list	*new_node;
	while (i < ac)
	{
		char	*conten_copy = ft_strdup(av[i]);
		new_node = ft_lstnew(conten_copy);
		ft_lstadd_back(&head, new_node);
		i++;
	}
	print_list(head);
	
	printf("##############################\n");

	ft_lstclear(&head , NULL);
	if (!head)
	{
		printf("NULL");
		return 1;
	}
	printf("after clearing : \n");
	print_list(head);
	return 0;
}
*/