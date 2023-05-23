/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:17:44 by jprofit           #+#    #+#             */
/*   Updated: 2022/12/12 13:52:15 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*addr;

	if (!lst || !(*lst) || !(del))
		return ;
	tmp = *lst;
	while (tmp)
	{
		addr = tmp-> next;
		ft_lstdelone(tmp, (del));
		tmp = addr;
	}
	*lst = NULL;
}
