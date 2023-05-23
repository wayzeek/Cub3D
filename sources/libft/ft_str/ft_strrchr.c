/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:35:22 by jprofit           #+#    #+#             */
/*   Updated: 2022/12/12 13:53:23 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	size;
	char	*str;
	char	*temp;

	size = ft_strlen(s);
	str = (char *)s;
	temp = NULL;
	while (size + 1 > 0)
	{
		size--;
		if (*str == (char)c)
			temp = str;
		str++;
	}
	return (temp);
}
