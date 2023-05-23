/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 09:45:58 by jprofit           #+#    #+#             */
/*   Updated: 2022/12/12 13:53:13 by jprofit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_strlen(src);
	i = 0;
	j = 0;
	while (dstsize > 1)
	{
		if (src[i] == '\0')
			break ;
		dst[i++] = src[j++];
		dstsize--;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	return (len);
}
