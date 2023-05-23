/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:20:54 by jprofit           #+#    #+#             */
/*   Updated: 2022/12/12 13:52:22 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static t_list	*ft_lstnew_del(void *content, void (*del)(void *))
{
	t_list	*tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
	{
		(del)(content);
		return (NULL);
	}
	tmp->content = content;
	tmp->next = NULL;
	return (tmp);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*cpy;
	t_list	*head;

	if (!lst || !(f) || !(del))
		return (NULL);
	cpy = ft_lstnew_del((f)(lst->content), (del));
	if (!cpy)
		return (NULL);
	lst = lst->next;
	head = cpy;
	while (lst)
	{
		cpy->next = ft_lstnew_del((f)(lst->content), (del));
		if (!cpy->next)
		{
			ft_lstclear(&head, (del));
			return (NULL);
		}
		cpy = cpy->next;
		lst = lst->next;
	}
	return (head);
}
